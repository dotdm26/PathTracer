A path tracer program developed in C++, based on the Ray Tracing in One Weekend guide by Peter Shirley: https://raytracing.github.io/books/RayTracingInOneWeekend.html

Originally a part of a bigger group project from Aalto University's C++ course (Sep - Dec 2023). All personal contribution was taken from the project and reuploaded here. 
The majority of the program was developed using pure C++, although the SFML library was used to draw and export the image.

![image](https://github.com/dotdm26/PathTracer/assets/56063151/bcfadf56-c2d2-4998-8a09-18612b147d13)

In this program, rays are used to calculate the intensity of the light on the pixel based on the distance between the object's hit pixel and the light source. A Monte-Carlo Integration procedure was used by sampling random points from the light source to shoot the rays from the hit pixel.
Rays are also used to draw an object's shadow on the ground by checking whether the ray shot from the pixel hit an object or not.
