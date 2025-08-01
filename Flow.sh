cd .\build

#Generate make file
cmake ..

#Build the targets
make

#Update the documentation
make documentation

#Run the test code. In subfolder to prevent bundling with application
ctest --test-dir .\test

#Compile into an installer
cpack

#Return to parent dir
cd ..