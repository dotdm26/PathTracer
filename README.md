A path tracer program developed in C++, based on the Ray Tracing in One Weekend guide by Peter Shirley: https://raytracing.github.io/books/RayTracingInOneWeekend.html

Originally a part of a bigger group project from Aalto University's C++ course (Sep - Dec 2023). All personal contribution was taken from the project and reuploaded here after making minor adjustments.
The majority of the program was developed using C++ & STL, although the SFML library was used to draw and export the image.

![image](https://github.com/dotdm26/PathTracer/assets/56063151/bcfadf56-c2d2-4998-8a09-18612b147d13)

In this program, rays are shot from the camera and perform several tasks depending on where they hit.

A ray colors the pixel based on the pixel's position, and adjusts the lighting based on the distance between the hit pixel and the light source. The latter procedure prompts multiple rays to be shot, this time from the hit pixel, towards random points within the light source based on the Monte-Carlo integration. The more rays that are intercepted by an object before they hit the light source, the darker the pixel will be.

Rays are also used to draw an object's shadow on the ground by checking whether the distance between the hit pixel and the center of the ground (represented by the giant green sphere at the bottom) is equivalent to the radius of the green sphere.

If a ray does not hit an object, it instead colours the background.
