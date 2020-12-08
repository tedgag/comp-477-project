# comp-477-project

Run and compile the program
----------------------------------------

- To run the program, simply run the .exe file in the comp477project/bin directory (note: don't move the .exe from the directory or it will not
 work, since it will not be able to reach the lib folder)
 
- To compile the program, follow the following instructions:
* The program was only compiled an tested on Windows 10, instrcutions may vary on other OSes
** The program needs at least Visual Studio and CMake to be compiled. Please check out this link to install CMake if it is not installed already:
https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160

1. In the root directory of the project, run cmake . and cmake --build .
2. Open the generated .sln file in visual studio
3. On the right, select comp477project as startup project
4. Launch the project (in release mode) by clicking on the Local Window Debugger button at the top
5. The pogram will build but will not run (known problem) from Visual Studio. Simply close the program and go where the .exe file was generated
(usually in comp477project/Release directory) and double click the .exe file
