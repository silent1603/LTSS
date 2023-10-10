if [ "./bin/image.ppm" ] 
then
    rm -f ./bin/image.ppm
fi
touch ./bin/image.ppm
./bin/RayTracing >> ./bin/image.ppm