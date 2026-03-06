## [Commit 3] – 2026-03-05

**Time Spent:**
[1.5 hours] (February 17th)
[2 hours] (February 19th)
[4 hours] (March 5th)

### 🎯 Goals
- Complete "Hello Triangle" and "Shaders" chapter

### 🛠 Accomplished
- Worked through both chapters, and additionally set up seperate VBO (Vertex Buffer Objects) with multiple objects rendering various fragment shader effects with different setups at once to test my knowledge of what i've learnt so far. Set up a class for handling all the vertex/fragment shader loading, rather than needing to manually copy in a string each time.
### ⚠ Challenges
- Troubleshooting issues related to fragment shader compilation was very difficult. Often times when trying to implement something new, various older parts of the shader pipeline no longer work in sync and OpenGL simply throws errors, which I need to dissect to figure out what's going on.
- For now, implemented some basic perror() to tell me the origin of the error, but will likely need to read more into OpenGL's exception handling to set up systems to provide more information.

### 🧠 Reflections
- Starting to feel fairly comfortable with the basics of the shader pipeline and generally how OpenGL runs, given its unique state-machine implementation. Planning to start trying to implement some ideas of my own to handle later scene organization.

### 🚀 Next Steps
- Planning to go on a bit of a detour from what i've been following along thus far to try and organize my own structure for everything that's been covered so far; VBOs and EBOs, alongside the Shader class (alongside relevant methods) could likely be put into a single "Object" class which further can fit into a "Scene" object alongside a VAO iterating through all the object instances in the scene instance to render one-by-one.
- Implement an OBJ parser (similar to what i've done on my website, but a lot cleaner this time) so that I can load in external models
- Further on (perhaps two commits from now), look into swapping in the half-edge data structure, although it will take some time to figure out how to best integrate this, given OpenGL naturally has built-in support for directly handling buffers via the VBO and EBO setup (which does not lend itself as directly to this data structure format).
---