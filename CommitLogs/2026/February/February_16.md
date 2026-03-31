# Commit 1 – February 16th 2026
**Time Spent:**  
February 14th - 4 hours  
February 16th - 3 hours
### Goals
Initialize the project structure and dependencies alongside goals and the logging system. Make the initial GitHub push.
### Accomplished
1. Compiled the CMake project with GLAD and GLFW and successfully displayed a basic window.
2. Created the project goals and log system, and made the initial push to GitHub.
### Reflections
1. LearnOpenGL assumes a Visual Studio/Windows setup. I use WSL alongside VSCode, which requires different library inclusion steps.
   - Faced multiple "#include" errors with GLAD.
   - GLFW refused to display a window (driver errors / missing file descriptor).
   - Tried compiling GLAD into a static library and including it in CMake through one step.
   - Next, tried a nested CMake setup inside the GLAD folder (CMake project within a CMake project) to compile it into a static library, which added complexity and didn't work either.
   - Got GLAD working by including it as a subdirectory, which was the only approach that worked reliably.
      - Still need to determine if this adds noticeable overhead.
      - Trying to keep consistency across GLAD and GLFW was unpractical. Installing GLFW directly as a Linux package was faster and avoided deeper issues.
4. VSCode's Remote SSH extension solved many WSL-related linter issues.
   - I should review how static libraries are structured and included in CMake.
### Next Steps
Continue LearnOpenGL to render my first triangle on screen in the "Hello Triangle" chapter.