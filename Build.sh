if [ -d "./build" ] 
then
    echo "Directory build exists." 
else
    echo "Error: Directory build does not exists."
    echo "Create: Directory build does not exists."
    mkdir build
fi

cd ./build
cmake ..
cd ..