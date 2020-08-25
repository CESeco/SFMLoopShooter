<p align="center">
  <img width="460" height="400" src="https://i.imgur.com/m0jmdjz.png">
  <hr/>
</p>
<h1 style="text-align:center">SFMLoopShooter</h1></center>

2nd semester computer engineering project ,Multiplayer shooter game: 

The concept is based upon this [video](https://www.youtube.com/watch?v=CBawCe6du3w) by Corridor Digital.

## Some Screenshots
![ServerClientChooseScreen](https://i.imgur.com/LYSSkfa.png)
![gameplay](https://i.imgur.com/vj8dr9M.png)

## Direct Download 
You can look at wiki and download from there
For windows it is straight forward.  

If you are on linux then you have to install SFML first using your package manager and you are good to run the program.
There is a script file for debian based operating system that will fulfill the dependencies automatically so if you are on debian just run ```run.sh``` file
    
        chmod +x run.sh
        ./run.sh

## To build from source 

### Requirements
- [CMake](https://cmake.org/download/)
- [SFML](https://www.sfml-dev.org/download.php)
  
  if you are on linux you can download the following package from the package manager
          
    on Debain based Distro 
     
          sudo apt install libsfml-dev cmake -y
          
    on Arch or arch based Distros
          
          sudo pacman -S libsfml-dev cmake
          
  
 ### Steps 
  
 - You can download the zip file or shallow clone the project.
 - After inside cd into the folder and run
 

Using CMake CLI

        mkdir build; cd build; cmake -G "Your Target Generator" ..
 look for how to choose generators ![here](https://cmake.org/cmake/help/v3.0/manual/cmake-generators.7.html) 
 
 Using Cmake GUI
 
        cmake-gui
        
If you are on windows then, CMake may not find path to sfml directory; you may explicitly define it by using -D option 

        cmake -DSFML_DIR=Your path here -G "Target generator" ..
        
 or use CMake GUI. everything seems easier there. 
 
 After generating the build files you can run respective makefiles and generate the executable. 
 After generating executable, if you are on windows you need to copy dll files from ``` YourSFMLDirectory\bin ``` to the executable folder.

 



