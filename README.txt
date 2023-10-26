# Software platform for CP411 Computer Graphics 

Author: HBF
Date: 2023-07-31

## What's about?

This package contains software and libraries for CP411 Computer Graphics programming and course work environment. It runs on Windows 10/11 with Intel/AMD/NVIDIA graphics card.

Software systems: 

1. MinGW GNU C/C++ 32bit compiler, and compatible OpenGL libraries (included)
2. Eclipse for C++, JRE is included for running Eclipse
3. Test examples of OpenGL and GLSL
4. Pandoc-2.2.3.2, a document format convert program for producing HTML reports

Folders:

cp411        : the root folder of the CP411 software platform 
  - eclipse  : the folder of Eclipse for C/C++
  - MinGW  : contains MinGW C/C++ 32bit compiler, and OpenGL, GLSL libraries.
  - examples  : contains two Eclipse projects of graphics examples.
	- Pandoc-2.2.3.2
	- workspace : will be used as default Eclipse workspace. 
	- assignments : contains folders of a1, ..., a5, project for assignments.

## How to install

You can simply extract this package to the C drive under C: directory (or an alternative directory). Then MinGW will be in directory  C:\cp411\MinGW, and so on. 

### Configure GNU C/C++ compiler

1. Add C:\cp411\MinGW\bin to user's environment Path variable
2. Add C:\cp411\MinGW\msys\1.0\bin to user's environment Path variable
3. Open a command line console (cmd), type and run command:

gcc --version

The output is like the following.

gcc (GCC) 4.6.2
Copyright (C) 2011 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE

Note that if you have other version of MinGW installed on your computer, remove their environment Path variable. 


### Test Eclipse C++ projects

1. Start Eclipse at C:\cp411\eclipse\eclipse.exe with workspace C:\cp411\workspace

2. Test Eclipse C++ by creating a C++ project helleworld: Eclipse  >  File  >  New  >  C++ Project  > type helloworld in project name box, select Project type: Executable > Hello World C++ Project, select Toolchains: MinGW GCC  > Next  >  Next  >  Finish. Compile and and run the helleworld project. Make sure you see the !!!Hello World!!! in the Eclipse console tab. 

3. Import provided opengl_test project. Eclipse: Import  >  Select: General  >  Existing Projects into Workspace  >  Next  >  Select archive file: Browse to the downloaded C:/cp411/examples/opengl_test.zip  Open  >  Finish. Compile/build and run opengl_test, make sure you see the rotation objects of FreeGLUT shapes.

4. Import provided glsl_demo project. Eclipse: Import  >  Select: General  >  Existing Projects into Workspace  >  Next  >  Select archieve file: Browse to C:/cp411/examples/glsl_demo.zip  Open  >  Finish. Compile/build and run glsl_demo, make sure you see a shining teapot.

### Configure Pandoc

Add C:/cp411/pandoc-2.2.3.2 to user’s environment Path variable.

Open a cmd console, type command: where pandoc

It should display: 

C:\cp411\pandoc-2.2.3.2\pandoc.exe


