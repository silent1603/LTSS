#include <iostream>
#include <string>
#include <chrono>

#include "Rtweekend.h"
#include "color.h"
#include "Camera.h"
#include "Hittable_list.h"
#include "Material.h"
#include "Sphere.h"
#if _MSC_VER && !__INTEL_COMPILER
    #include <omp.h>
#else 
    #include "openmp/omp.h"
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int main() {
    
    bool isUsingThread = false;
    uint32_t numberThreadAvailable = omp_get_num_procs();
    std::string input;
    std::cout << "Use Mutli Thread(y,n) :" ;
    std::cin >> input;
    isUsingThread = (input.compare("y") == 0);

    int usedThread;
    std::cout << "Has " << numberThreadAvailable << " thread available, How Many Threads Do You Need : ";
    std::cin >> usedThread;
    omp_set_num_threads(usedThread);

    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;
    auto start = std::chrono::steady_clock::now();
    if(isUsingThread)
    {
        cam.renderParallel(world);
    }
    else
    {
        cam.render(world);
    }
    auto end = std::chrono::steady_clock::now();
    if(isUsingThread)
    {
        std::cout << "Total time using "<< usedThread <<"Thread ." ;
    }
    else
    {
        std::cout << "Total time with no thread ." ;
    }
    std::cout << "Elapsed time in microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " µs" << std::endl;
    return 0;
}