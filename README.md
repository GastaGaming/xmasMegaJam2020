# xmasMegaJam2020
Because Unity is the engine we deserve, but not the one we need right now. So we'll use Urho3D. Because Urho3D can take it. Because Urho3D is our engine.

##How to build:  
* [Build] (https://urho3d.github.io/documentation/HEAD/_building.html)
##How to use:  
* [Use] (https://urho3d.github.io/documentation/HEAD/_using_library.html)
##How to get started  
* [Main Loop] (https://urho3d.github.io/documentation/HEAD/_main_loop.html) 

#Windows & Visual Studio
1. Download from Urho3D from github.
   Create folder directly under C:, I made folder U. 
   This is done because some build methods can have issues with too long directory paths. 
   My build path is C:\U\Urho3D_HEAD I used git bash for downloading, but you can also download zip. 
   Git clone [https://github.com/urho3d/Urho3D.git 
   After this my Urho3D source files are located in C:\U\Urho3D_HEAD\Urho3D 
2. Download CMAKE
    I used CMAKE version 3.15.4 GUI for building Urho3D. [https://cmake.org/download/
    After downloading and Installing create a new folder Next to Urho3D_HEAD. I named mine Urho3D_Home. 
    [![Folder Structure](https://github.com/GastaGaming/xmasMegaJam2020/Documentation/img/Cmake_01.png)
3. Build Urho Library
   Open CMAKE GUI and set your source and binary destinations 
   [![CMAKE GUI](https://github.com/GastaGaming/xmasMegaJam2020/Documentation/img/Cmake_01.png)
   You can also set binaries path same as source, but I like to separate so I can easily delete binaries and start again 
   if there is need for it....
   After setting paths. Press configure... and select your IDE and press Finish
   [![CMAKE GUI](https://github.com/GastaGaming/xmasMegaJam2020/Documentation/img/Cmake_02.png)
   After that it should start configuring. In CMAKE GUI there’s stupid thing where you have to Press 
   Configure->Generate->Configure->Generate and finally after that It lets you press Open Project 
   It should look something like this...
   [![CMAKE GUI](https://github.com/GastaGaming/xmasMegaJam2020/Documentation/img/Cmake_03.png)
   I personally changed two settings, I enabled URHO3D_OPENGL and  URHO3D_WIN32_CONSOLE for debugging purposes 
   Open project button opens Visual Studio and in there change Debug to Release in top tool bar.
   [![VisualStudio GUI](https://github.com/GastaGaming/xmasMegaJam2020/Documentation/img/VisualStudio_01.png)
   Then right Click ALL_BUILD (VISUALIZE) in solution panel and select build. 
   After that visual studio should start build process. 
   This can take a while 5 – 25 min s depending on your computer’s CPU. 
   [![VisualStudio GUI](https://github.com/GastaGaming/xmasMegaJam2020/Documentation/img/VisualStudio_02.png)
   If build was successful you can find Release builds in 
   C:\U\Urho3D_Home\bin\ and test one of those exe files. 
4. Set your Urho3D enviroment


   
   
   
   
   ```
 