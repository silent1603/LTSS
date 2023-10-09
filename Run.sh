if [ "./bin/image.ppm" ] 
then
    echo "image exists." 
else
    touch ./bin/image.ppm
fi
./bin/RayTracing >> ./bin/image.ppm