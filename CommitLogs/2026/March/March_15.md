# Commit 5 – March 15th 2026
**Time Spent:**  
March 10th - 4 hours  
March 12th - 3 hours  
March 13th - 4 hours  
### Goals
Reorganize my files for code maintainability as needed to implement functionality.  
Familarize myself with the error handling and formatting required for the .OBJ file type to implement an OBJ Parser.
### Accomplished
1. Wrote a mostly functioning OBJ file parser that handles vertex position, vertex colour, and normal data, while building data into a buffer fed to OpenGL.
   - This is stored in the "Mesh" class, attached to an "Object" class. Currently, this system works as expected and the mesh renders properly in the OpenGL viewport. However, I still need to confirm that the texture coordinates are being read correctly, because texture loading misbehaves.
2. Restructured header files according to feedback recieved from code review.
3. Error handling and organization for older functionality:
   - Reorganized Shader class for better error handling and maintainability.
   - Other minor error checks and general organization changes.
4. Implemented uniforms for transformation matrices to represent the model, view, and projection matrices.
### Reflections
1. Planning out a big system in one attempt is difficult.
   - Many header files were changed.
   - I took inspiration from how Blender structures classes for objects. Taking reference of how established systems are built is beneficial.
   - While I focused on one part at a time to keep things organized, it may be beneficial to implement a basic working example of the entire pipeline to ensure my implementations will work alongside future functionality.
2. I'm making a lot of changes per commit now, and I should push changes for every 6 hours of work or less.
### Next Steps
1. Abstract away more functionality to the Object class.
   - The goal is for the entire process to swap between object creation and rendering from simple "Create" and "Draw" functions for each object which reconfigure OpenGL as required.
   - Confirm texture coordinates are being parsed and handled correctly.
   - Organize uniforms as well as texture handling into the Object class.  
2. Clean up code antipatterns into seperate functions.
   - Implement more error handling.
   - Swap memory handling to smart pointers where it makes sense to do so.
   - Ensure memory is being cleaned up at all stages of runtime.