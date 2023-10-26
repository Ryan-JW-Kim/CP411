# A1 Report

Author: Ryan Kim 

Date: Sept. 19 2023 

Check [readme.txt](readme.txt) for course work statement and self-evaluation. 
  
## Q1 Concepts of raster graphics (short answer)


### Q1.1 frame buffer
A memory block to allocated to store raster dots within a raster pattern. Generally stored in 2D matrix data structure.

The size of the frame buffer is determined by $\text{frame resolution} * \text{color depth}$


### Q1.2 pixel
A pixel is a single picture element within a row. A pixel only stores a color value and its location within a frame determines is position on the screen.

### Q1.3 color depth
Color depth refers to the number of bits used to store a pixels assigned color and therefore the *depth* of possible colors. 8 bits allows for rgb (red, green blue) to each store an integer value of from 0 to 256. Thus the color depth of an 8-bit pixel would be $256*256*256=16777216$ possible colors for a single pixel.


### Q1.4 resolution
The number of scan lines and number of pixels for each scan line. Represented in common terms as $\text{scan lines} * \text{pixels}$ for example a resolution of 1920x1080 refers to 1920 scan lines (rows) and 1080 pixels (cells per row)


## Q2 Concepts of raster display (short answer)


### Q2.1 scan line
A row of pixels within a raster pattern. Note that when *scanning* the first scan line would be completely scanned before the next would begin. There are alternative ways of scanning lines but they may induce flickering.

### Q2.2 refreshment & refresh rate
Refresh rate refers to the number of frames rendered within a given time span. Generally we measure frames per second. Refresh rate is supported by the performance of the video controller, the size of the frame buffer, and the speed at which new frames can be generated.

### Q2.3 frame
A frame is a single image made up of many scan lines, which each contain many pixels per line. The completed frame (a set of scan lines) is stored as a 2D matrix within the frame buffer.



## Q3 Roles of CPU and GPU in CG (short answer)


### Q3.1 CPU roles
The CPU performs computations for model generation.


### Q3.2 GPU roles
The GPU performs computations to convert model objects into framebuffer frames using techniques such as rasterization.



## Q4 C/C++ OpenGL programming environment (lab practice)


### Q4.1 C/C++ OpenGL installation 
Complete? Yes 

If Yes, insert a screen shot image to show the completion.

![Cube demo](images/cube.png){width=50%}
![Teapot demo, note the clean lighting](images/teapot.png){width=50%}
![Teapot demo, note the choppy lighting as a result of removing GPU logic](images/teapot_no_gpu.png){width=50%}

If No,  Add a short description to describe the issues encountered.

### Q4.2 OpenGL C project 
Complete? Yes

If Yes, insert a screen shot image to show the completion.

![Screenshot of the blender demo found in examples](images/blender.png){width=50%}

If No,  Add a short description to describe the issues encountered.

### Q4.3 OpenGL C++ project 
Complete? Yes

If Yes, insert a screen shot image to show the completion.

![Screenshot of the GLUT test](images/glut_test.png){width=50%}

If No,  Add a short description to describe the issues encountered.



**References**

1. CP411 a1
2. Add your references if you used any. 
