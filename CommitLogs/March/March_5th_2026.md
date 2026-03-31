# Commit 3 – March 5th 2026
**Time Spent:**  
February 17th - 1.5 hours  
February 19th - 2 hours  
March 5th - 4 hours
### Goals
Complete the "Hello Triangle" and "Shaders" chapters at LearnOpenGL.
### Accomplished
1. Worked through both chapters:
   - I additionally set up seperate VBO (Vertex Buffer Objects) alongside multiple objects rendering various different fragment shader effects at once to test my knowledge of what I've learnt so far.
   - Also set up a class for handling all the vertex/fragment shader loading, rather than needing to manually copy in a string each time.
### Reflections
1. Troubleshooting issues related to fragment shader compilation was very difficult.
   - Often when trying to implement something, various older parts of the shader pipeline no longer work in sync.
   - OpenGL simply throws errors that I need to dissect to figure out what's going on.
   - Implemented some perror() handling to tell me the origin of this error, but I should read into OpenGL-specific exception handling.
2. Starting to feel comfortable with the basics of the shader pipeline and OpenGL's state-machine representation.
3. Planning to start implementing some of my own ideas to handle future scene organization.
### Next Steps
1. Go on a detour to implement my own data structures for organizing everything:
   - VBOs and EBOs alongside the Shader class could likely be put into a single "Object" class, further encapsulated in a "Scene" object alongside a VAO iterating through all instances to render one-by-one.
   - Look into implementing the half-edge data structure. OpenGL's setup involves handling buffers for the VBO and EBO, which does not lend itself as naturally to this data structure.
2. Implement an OBJ parser to load in external models.