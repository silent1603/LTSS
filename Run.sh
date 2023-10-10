if [ "./bin/image.ppm" ] 
then
    rm -f ./bin/image.ppm
    touch ./bin/image.ppm
else
    touch ./bin/image.ppm
fi
./bin/RayTracing >> ./bin/image.ppm