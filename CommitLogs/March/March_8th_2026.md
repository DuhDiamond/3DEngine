# Commit 4 – March 8th 2026
**Time Spent:**  
March 7th - 2 hours  
March 8th - 5 hours
### Goals
Figure out how to encapsulate OpenGL's buffer management into a more modern object-oriented format, keeping things as modular and efficient as possible without unnecessary complexity.
### Accomplished
1. Created preliminary header file structure:
   - Planned out how an object's data will be loaded and instanced.
   - Possibility to extend future interfaces via inheritance and polymorphism.
### Reflections
1. Trying to adapt OpenGL's state-machine API into an object-oriented approach was trickier than expected.
   - In particular, planning out representation of object data in a modular format alongside IDs returned by OpenGL without instancing extra classes.
   - Also finding a way to re-use IDs for previously loaded assets.
2. It's likely that I will need to make many changes as I start implementing functionality, due to functionality and edge cases I haven't considered yet.
3. The main benefit to planning header files are to have an organized plan and direction to follow. Code can always be adjusted later.
### Next Steps
1. Work on implementing the header files.
   - I will likely start with the ObjLoader, as the loading script is an isolated part of the system.
2. Work through the implementation of the Object class from the bottom-up.