## [Commit 4] – 2026-03-08

**Time Spent:**
[2 hours] (March 7th)
[5 hours] (March 8th)

### 🎯 Goals
-Figure out how to encapsulate OpenGL's buffer management into a more modern object-oriented format I can access, keeping things as modular and efficient as possible without too much added complexity

### 🛠 Accomplished
-Created preliminary header file structure and planned out how an object's data will be loaded and instanced, alongside with possibility to extend future interfaces via inheritance and polymorphism

### ⚠ Challenges
-Planning out the structure took a lot of time. Trying to adapt OpenGL's API functionality with the state-machine format into an object-oriented approach turned out to be even trickier than I initially expected, due to complexity with how to represent object data in a modular format alongside storing IDs returned by OpenGL efficiently, and without needing to instance too many classes or create unnecessary IDs for already-loaded mesh/texture assets.

### 🧠 Reflections
-It's likely that I will need to make many changes as I start implementing the header file functionality, due to unforeseen cases or other future functionality I haven't considered yet
-However, it's to be expected. The main benefit to planning header files are so that I have an organized plan and direction to follow in the meantime. Code can always be adjusted later!

### 🚀 Next Steps
-Work on implementing the header files; I will likely start with the ObjLoader, as writing the loading script is a relatively isolated part of the system, and then work through the implementation of the Object class from the bottom-up.
---