Set-Location .\build

#Generate make file
cmake.exe ..

#Build the targets
make.exe

#Update the documentation
make.exe documentation

#Run the test code. In subfolder to prevent bundling with application
ctest.exe --test-dir .\test

#If tests pass
if ($LASTEXITCODE -ne 0) {
    #Compile into an installer
    cpack.exe

}

#Return to parent dir.
Set-Location ..