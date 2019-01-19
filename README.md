# An Full screen OpenCV / GtK application in C++ running on Raspberry PI

_C++_, _OpenCV_ and _Gtk_ are a nice triplet to build applications that run on a Raspberry PI, taking images from the camera, process them, display them and have an unlimited user interface. In this example I'm showing some design patterns that I find useful when implementing a computer vision application with a graphic user interface. In a prior example [gtk-opencv-simple](https://github.com/raspberry-cpp-tutorials/gtk-opencv-simple), I show a much simpler way to display images caputerd with the camera in a full screen window. I hope these two examples can help you through the boring problems you need to solve before reaching the place where you can have fun.

I'm using the following technical stack:

* **_Raspberry Pi_** - The ultimate goal is to launch the application on it.
* **_CMake_** - This is the needed ingredient to make your code buildable on most of the platforms. It also exports your project to  Xcode, VisualStudio, Eclipse and a long list of others, so you will be able to choose your preferred IDE.
* **_Mac OS X_, _Ubuntu_, _Windows_** - Where you can write and test your application.
* **_C++_** - _Python_ is fashionable, young, efficient and well supported by Raspberry folks. But I happen to like _C++_ more. If _Python_ is your thing, then stop reading.
* **_OpenCV_** - One very widely used open source (hence the Open) computer vision (hence the CV) library.
* **_Gtkmm_**, which is the _C++_ oriented port of _Gtk_ - Although _OpenCV_ lets you display images on screen, it is somewhat limited when interacting with the user. Being easily compatible, _Gtk / Gtkmm_ are a great complement to _OpenCV_ for building real user interfaces around computer vision applications.

# Used patterns
- Event Bus
- Inversion of Control
- Conditional modules (via cmake)

# The branches structure
In the [Wiki](https://github.com/raspberry-cpp-tutorials/gtk-opencv-patterns/wiki) articles I'm explaining the code quite in detail. To help the exposition order, I split the code into multiple steps:
- Step1 branch contains the code for step 1.
- Step2 branch contains step 2.
- Etc.
- Master branch contains the final code, all steps together.

# Cross-platform development environment
An important objective of this project is to be able to build and test it in your preferred desktop computer or notebook. _Raspberry Pi_ is meant to be an embedded system platform, and it is an amazing one. Still, it lacks the right keyboard, mouse, monitor or amount of memory required to be a comfortable as a development tool.

In short, the project is configured via _cmake_ which makes it compatible with _XCode_, _Code::Build_, _gcc_ and other development tools, and this is what you need to do from either a _Mac OS X Terminal_, a _Linux Terminal_ or a _MinGW Terminal_:

```Bash
cd ~/to/your/working/folder
git clone https://github.com/raspberry-cpp-tutorials/gtk-opencv-patterns.git
cd gtk-opencv-patterns.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../src
ctest --output-on-failure
```

To run the application:

```Bash
./app/rascapp
```

There are more detailed instructions to install a working development environment in the three major operative systems:

* [Installing Mac OS X development environment](https://github.com/raspberry-cpp-tutorials/gtk-opencv-simple/wiki/Mac-OS-X-development-environment)
* [Installing Windows development environment](https://github.com/raspberry-cpp-tutorials/gtk-opencv-simple/wiki/Windows-development-environment)
* [Installing Linux development environment](https://github.com/raspberry-cpp-tutorials/gtk-opencv-simple/wiki/Linux-development-environment)

Last but not least:

* [Installing the project on Raspberry PI](https://github.com/raspberry-cpp-tutorials/gtk-opencv-simple/wiki/Installing-on-Raspberry-PI)

# The project's folder structure

There are several great articles that discuss about the best folder structure for a project built with _CMake_:

 * [https://arne-mertz.de/2018/06/cmake-project-structure/](https://arne-mertz.de/2018/06/cmake-project-structure/): I like this one because it discusses how to integrate those header-only libraries, and uses _Catch_ as an example.
 * [https://rix0r.nl/blog/2015/08/13/cmake-guide/](https://rix0r.nl/blog/2015/08/13/cmake-guide/): I like this one because it shows in detail how to configure CMake and why, and also acknowledges the difference between library (which is easily unit tested) and application (which is the user interface, and not very easy to unit test).

The project has two modules:
- The application, containing the ``main`` routine, plus the Gtk widgets composing the user interface. The code of the application is not unit tested, therefore it should not contain complex routines, but merely call the library.
- The library, containing all complex elements. The library contains the complex image processing routines, which are unit tested using _Catch_.

This is the project's folder structure:

```
.gitignore        <-- Ignore xcode, codeb, build folders.
/src              <-- All sources are here
   CMakeList.txt  <--- The top CMake configuration file.
   /app           <----- Contains the executable application.
      /cpp        <-------- C++ source files for the application.
      /hpp        <-------- C++ header files for the application.
      /res        <-------- Resource files for the application.
   /lib           <----- Contains the library.
      /cpp        <-------- C++ source files for the appl.
      /hpp        <-------- C++ header files for the application.
      /tst        <-------- Unit test for the library classes.
         /res     <-------- Resources for unit tests.
/build            <-- Contains the temporary build files. 
                      Not under version control
/xcode            <-- Contains the XCode project.
                      Not under version control.
/codeb            <-- Contains the Code::Blocks project. 
                      Not under version control. 
```
