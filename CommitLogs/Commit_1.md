## [Commit 1] – 2026-02-16 (Log posted later)

**Time Spent:**
[4 hours] (February 14th)
[3 hours] (February 16th)

### 🎯 Goals
- Initialize project structure and dependencies
- Define project goals and logging system
- Make initial GitHub push

### 🛠 Accomplished
- Set up CMake project with GLAD and GLFW
- Successfully compiled and displayed a basic window
- Created project goals + log system
- Pushed initial commit to GitHub

### ⚠ Challenges
- LearnOpenGL assumes a Visual Studio/Windows setup; I use WSL + VSCode, which required different library inclusion steps.
- Faced multiple `#include` errors with GLAD.
- GLFW initially refused to display a window (driver errors / missing file descriptor).
- Tried compiling GLAD into a static library and including it in CMake in one step. Attempted a nested CMake setup inside the GLAD folder (CMake project within a CMake project) to first compile it into a static library, which added complexity and didn't work.
- Ultimately got GLAD working by including it as a subdirectory — the only approach that worked reliably. Need to determine further if this adds noticeable overhead.

### 🧠 Reflections
- Trying to keep everything “consistent” (same integration style for GLAD and GLFW) isn't always practical.
- Installing GLFW directly as a Linux package was faster and avoided deeper issues.
- VSCode Remote SSH reduced many WSL-related linter issues.
- I should review how static libraries are properly structured and included in CMake.

### 🚀 Next Steps
- Continue LearnOpenGL to render first triangle on screen ("Hello Triangle" chapter)

---