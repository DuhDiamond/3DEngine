## [Commit 6] – 2026-03-22

**Time Spent:**
[4 hours] (March 16th)
[2 hours] (March 18th)
[2 hours] (March 20th)

### 🎯 Goals
-Figure out why texture coordinates aren't being displayed properly
-Clean up and organize/abstract away some of the Main.cpp code
- Abstract away more functionality to the Object class to minimize amount of function calls in Main.cpp

### 🛠 Accomplished
- Found cause of texture coordinates not being handled properly; although my .obj parser was handling it correctly, I had the incorrect stride (offset) set up in the API calls
- I ultimately found this out when deciding to try and debug behaviour by implementing some simple Phong lighting; I realized there was an issue when rotating the model caused lighting to rotate the "other" way, and it turns out normals data was also incorrectly set (position and vertexColours were being handled correctly)
- Implemented a default fallback grey (0.5, 0.5, 0.5) colour to be given to the buffer if a given .obj file has no vertex colours
- Started implementation on a Clock class for unifying scene deltaTime

### ⚠ Challenges
- It took a long time before I realized the API calls were misconfigured; I decided to implement some basic lighting and clean up various elements related to the Object and OBJMesh classes to isolate where the bug was. I wonder how many other unknown errors are in my project? Should look into more error-checking functionality to ensure any errors get properly discovered

### 🧠 Reflections
- Main.cpp and pre-render loop calls are starting to get quite messy; need to implement some type of handling for the scene

### 🚀 Next Steps
- Continue abstracting functionality to clean up Main.cpp pre-render loop function calls
- Swap memory handling to smart pointers where it makes sense to do so, and ensure memory is being properly cleaned up at all stages of runtime (overdue)
- Re-implement polymorphism for the Object class back to IMesh and IMaterial; I was previously having issues with unexpected return types
- See how to re-implement MeshLoader to instead serve as a scene manager for the VAO; can likely group all loaded Mesh instances to render more efficiently
- Finish implementing Clock class for unified time operations
- Implement Camera class to further clean up Main.cpp and scene handling
---