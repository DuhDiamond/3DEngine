# Commit 7 – April 30th 2026
**Time Spent:**  
April 26th - 1 hour
April 28th - 2 hours
April 29th - 3 hours
### Goals
Figure out the issue surrounding a "scrunched up" look around some parts of loaded diffuse textures, and continue working on fixing lighting interactions and implementing a camera system. Learn more about how to effectively troubleshoot shaders and the various options available to efficiently render groups of objects.
### Accomplished
1. Abstracted away/standardized some uniform calls to use shader functions in preparation for the camera class and rendering.
2. Fixed and added to the lighting implementation:
   - Each object is now lit properly according to its position and pointlight position
   - Added missing distance falloff for lights
   - Now properly interacts with the camera's position and orientation
   - Other minor fixes such as missing normalization for normal vectors interpolated through the fragment shader and the diffuse texture/vertex colours influencing the specular light colour
3. Implemented keyboard and camera controls for moving around the scene
4. Added destructor to free stored buffer memory used while building meshes
### Reflections
1. Discovered the issue for textures not displaying properly over UV seams:
   - Although the OBJ parser was reading in all the data, only one vertex was being used for UV seam edges
   - This caused the fragment shader to interpolate over UV shells, often resulting in a "scrunched up" look around UV seams.
   - This can be fixed by ensuring the mesh loader properly makes use of the multiple vertices read in at the same position coordinate, rather than defaulting to one (or ensuring all imported mesh geometry is split on UV seams ahead of time).
### Next Steps
1. New classes:
   - Move camera code into a camera class
   - Decide if I should keep a "Clock" class for unifying global time
      - Since the code required is very short, this may cause code to be overly coupled without providing much benefit, and may be simpler to handle directly in the render loop.
2. Fix the mesh loader not making use of duplicate vertices to solve the UV seams problem.
3. Look into the Scene class to store the camera and all loaded assets.