# Commit 8 – May 2 2026
**Time Spent:**  
May 1st - 3 hours
May 2nd - 3 hours
### Goals
Work towards implementing the next components into the object-oriented structure (Lights, Scene, Camera)
### Accomplished
1. Moved all camera code into a "Camera" class, set up in a way to ideally allow multiple cameras to be created and swapped between at runtime
   - Since OpenGL expects a global function/static method for mouse cursor handling, I currently use a lambda to encapsulate information from a pointer to an active camera; this will be moved to the Scene class
2. Initialized classes for AmbientLight, DirectionalLight, PointLight, and a common superclass (ILight)
3. Added more of the scene elements to the Scene class.
   - I will need to step back and figure out how best to handle this, given how much of the program's functionality will revolve around it, such as batch rendering, object iteration, and camera interactions
### Reflections
1. Since I am starting to assemble things "global" to scene management and rendering, I need to take a step back and re-evaluate my current rendering structure. In particular, there are two main issues at the moment:
   - Rendering is currently forcefully swapping all the states to match the object's states to ensure everything is set as needed; while this is convenient for the current object structure, this is not an optimal rendering architecture for performance
   - Requiring so many lines of code to get all of a single object's assets loaded and rendered in the scene is less user-friendly than it could be; ideally, this should be encapsulated into a single function call (and this will likely simplify the implementation of the user interface later)
### Next Steps
1. Take a step back and look into reorganizing render structure around one of the glMultiDrawElements calls (or whichever similar batch rendering draw call seems to be best for my use case). This will be harder to implement later, as the scene structure, or whichever class will handle batch rendering, should be oriented around the rendering architecture.
2. Continue implementing started classes from last time (Lights, Scene, Camera) once I figure out the optimal rendering structure to support it.