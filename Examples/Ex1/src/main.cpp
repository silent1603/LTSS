


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include <io.h>
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
	#include<unistd.h>
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS, tvOS, or watchOS Simulator
    #elif TARGET_OS_MACCATALYST
         // Mac's Catalyst (ports iOS API into Mac, like UIKit).
    #elif TARGET_OS_IPHONE
        // iOS, tvOS, or watchOS device
    #elif TARGET_OS_MAC
        // Other kinds of Apple platforms
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __ANDROID__
	#include<unistd.h>
    // Below __linux__ check should be enough to handle Android,
    // but something may be unique to Android.
#elif __linux__
	#include<unistd.h>
    // linux
#elif __unix__ // all unices not caught above
	#include<unistd.h>
    // Unix
#elif defined(_POSIX_VERSION)
	#include<unistd.h>
    // POSIX
#else
#   error "Unknown compiler"

#endif
#include<stdlib.h>
#include<iostream>
#include<chrono>

#include<omp.h>
#include<math.h>
//using namespace std;
//int main(void)
//{
//	int *A=new int[100000];
//	int *B=new int[100000];
//	
//	for(int i=0;i<100000;i++)
//	{
//		A[i]=rand();	
//	}
//
//    auto start = chrono::steady_clock::now();    
//    int nProcessors = omp_get_max_threads();
////    omp_set_num_threads(2);
//	#pragma omp parallel for
//	for(int j=0;j<10000;j++)
//	{
//		for(int i=0;i<1000000;i++)
//		{
//			B[i]=A[i]*sqrt(2);	
//		}
//	}	
//
//	auto end = chrono::steady_clock::now();
//	cout << "Elapsed time in microseconds: "
//        << chrono::duration_cast<chrono::microseconds>(end - start).count()
//        << " µs" << endl;
//    cout << "Num# Threads: " << nProcessors << endl;
//	start = chrono::steady_clock::now();    
////	#pragma omp parallel for
//	for(int j=0;j<10000;j++)
//	for(int i=0;i<1000000;i++)
//	{
//		B[i]=A[i]*sqrt(2);	
//	}	
//	end = chrono::steady_clock::now();
//	cout << "Elapsed time in microseconds: "
//        << chrono::duration_cast<chrono::microseconds>(end - start).count()
//        << " µs" << endl;
//	delete A;
//	delete B;
//	return 0;
//}

#include <omp.h>

void subdomain(float* x, int istart, int ipoints)
{
	int i;
	for (i = 0; i < ipoints; i++)
		x[istart + i] = 123.456;
}

void sub(float* x, int npoints)
{
	int iam, nt, ipoints, istart;

#pragma omp parallel default(shared) private(iam, nt, ipoints, istart)
	{
		iam = omp_get_thread_num();
		nt = omp_get_num_threads();
		ipoints = npoints / nt; /* size of partition */
		istart = iam * ipoints; /* starting array index */
		if (iam == nt - 1) /* last thread may do more */
			ipoints = npoints - istart;
		subdomain(x, istart, ipoints);
	}
}

int main()
{
	float array[10000];
	sub(array, 10000);
	return 0;
}
