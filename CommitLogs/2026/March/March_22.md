# Commit 6 – March 22nd 2026
**Time Spent:**  
March 16th - 4 hours  
March 18th - 2 hours  
March 20th - 2 hours
### Goals
Figure out why texture coordinates aren't being displayed properly.  
Abstract away more functionality to the Object class to minimize amount of function calls in Main.cpp.  
### Accomplished
1. Found cause of texture coordinates not being handled properly:
   - Although my .OBJ parser was properly implemented, I had the incorrect stride set up in the API calls.
2. Implemented a default fallback grey (0.5, 0.5, 0.5) colour to be given to the buffer if a given .obj file has no vertex colours.
3. Started implementation on a Clock class for unifying scene deltaTime.
### Reflections
1. It took a long time to realize the API calls were misconfigured.
   - I found this out when trying to debug behaviour by implementing some simple Phong lighting.
   - I realized there was an issue when rotating the model caused lighting to rotate the "other" way, and it turns out normals data was also incorrectly set.
   - I should look into more error-checking functionality specific to shaders.
### Next Steps
1. Continue abstracting functionality away for Main.cpp function calls.
   - Implement scene handling for Main.cpp's pre-render loop calls.
   - Swap memory handling to smart pointers where relevant, and ensure memory is being cleaned up at all stages of runtime.  
2. Re-implement polymorphism for the Object class through IMesh and IMaterial.
   - I was previously having issues with unexpected return types.  
3. Re-implement MeshLoader to serve as a scene manager for the VAO.
   - I can likely group all loaded Mesh instances to render more efficiently.
4. Finish implementing next classes:
   - Clock class for unified scene time operations.
   - Camera class for relevant scene information.