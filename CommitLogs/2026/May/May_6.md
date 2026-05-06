# Commit 8 – May 2 2026
**Time Spent:**  
May 3rd - 3 hours
May 4th - 4 hours
May 5th - 4 hours
### Goals
Fix the issue regarding duplicated vertices on OBJ meshes from last time
Research the various glMultiDraw-related calls to learn more about the pros and cons, how OpenGL handles draw calls, and find out the best setup for my scene structure and configuration for future goals
### Accomplished
1. Simplified the OBJ parser code and various parts of scene classes and functionality, catching various bugs and inconsistencies such as redundant binding calls, and swapped from dynamic arrays to simply calling .data() on original vector content
2. Implemented a hashmap approach to filter out duplicate vertices and build a new VBO and EBO for finalized mesh data
3. Implemented more parts of classes (IndirectRender) and various structs in preparation for glMultiDrawElementsIndirect()
4. Merged both fragment shaders into one, in preparation for the scene to be reorganized fundamentally from one main shader and VAO, as well as instanced rendering for glMultiDrawElementsIndirect()
### Reflections
1. Trying to implement functionality has been difficult because of too much data being handled around; I should focus on a working "bare minimum" approach for each fundamental component and building upwards, rather than continously expanding on one main scene element at a time.
2. To handle this issue, I should focus on:
   - Simplifying current code where possible
   - Simplfying functionality while keeping it expandable, rather than immediately focusing on implementing an interface for possible future functionality right away
   - Getting rid of unnecessary comments: some were useful while planning out functionality, but **ideally a maintainable system should be easily understood without too many comments required for someone to understand everything**
### Next Steps
1. Put in more error checking and edge case handling for functionality (mainly the obj building, loading, and initializing)
2. Continue simplifying current code in preparation for implementing GlMultiDrawElementsIndirect() cleanly
3. Look into implementationing more modern versions of currently implemented functionality to support the structure required for this, such as bindless textures to handle the planned modular scene format more cleanly