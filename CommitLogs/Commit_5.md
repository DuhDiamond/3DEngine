## [Commit 5] – 2026-03-15

**Time Spent:**
[4 hours] (March 10th)
[3 hours] (March 12th)
[4 hours] (March 13th)

### 🎯 Goals
- Reorganize Object, Mesh, etc. classes to be better organized from both the code readability/maintainability perspective and the functionality perspective
- Reorganize header files as applicable from external code review
- Familarize myself with proper error handling and file reading required for the .OBJ file type to implement a working file reader/parser

### 🛠 Accomplished
- Wrote a fully functioning* OBJ file parser that handles vertex positions, and optionally vertex colours, normals, and texture coordinates, and builds the data into a buffer that is fed to OpenGL; this is stored in the "Mesh" class, and then attached to an "Object" class alongside an optional Material class (yet to be implemented). Currently, this system works as expected and the mesh renders properly in the OpenGL viewport alongside the vertex colours and normals
*Still need to confirm that texture coordinates are being read correctly; more on this below
- Reorganized Shader class and functionality for better error handling and organization
- Largely restructured header files (especially for Object and Mesh classes) according to feedback recieved for organization
- Implemented some other minor error handling and general organization of older functionality (can't remember all the changes off the top of my head)
- Started looking into implementing texture loading (commented out the functionality in the fragment shader as I am still trying to troubleshoot an issue related to proper display of textures, I suspect texture coordinates are not being handled properly)
- Implemented uniforms for handling transformation matrices to represent model, view, and camera matrices respectively

### ⚠ Challenges
- I had to make a lot of changes from my original header structure; trying to plan out such a big system in one go is difficult, especially when unforeseen requirements appear. Consequently, I think it may be beneficial to

### 🧠 Reflections
- I found that taking reference from how established systems are built to structure my code design around for the classes was fairly beneficial; I took inspiration from how Blender (which as a program is naturally object-oriented) structured Object representation
- Keeping track of all the elements is fairly difficult; while my focus is to work on one part of a class at a time and ensure it fully works before moving on to avoid unnecessary backtracking and disorganization, sometimes it is beneficial to skip a bit forward and implement a basic working example of something that it is used for down-the-line to ensure what i'm building will actually work for my intended use case alongside said future functionality
- Lastly, I should start making more commits more often; at this stage i'm starting to make a lot of changes per each commit, and should try to commit for every ~6 hours of work

### 🚀 Next Steps
- Confirm texture coordinates are being parsed and handled correctly
- Organize the uniforms and texture handling into the Object class
- Clean up some other various code antipatterns into seperate functions, and implement more error handling
- Swap memory handling to smart pointers where it makes sense to do so, and ensure memory is being properly cleaned up at all stages of runtime
- Generally re-organize and abstract away more functionality to the Object class; the goal is that the entire rendering process can swap between object creation and rendering efficiently and easily from a simple "Create" function pre-render loop for each object, and a "Draw" function which reconfigures OpenGL's state as required to redraw each object each frame
---