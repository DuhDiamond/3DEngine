# 3D Engine

A work-in-progress 3D rendering engine built as a learning project to explore graphics programming.

Here are some steps if you'd like to run it yourself. I use Windows + WSL (Windows Subsystem for Linux, based on Debian Linux) in a Visual Studio Code environment, alongside with the Remote WSL extension to locally connect to my WSL instance for faster development.

1. Git clone the repository: In Linux/WSL, this can be done by running the following command in your terminal, from the folder you'd like to copy it into:
git clone git@github.com:DuhDiamond/3DEngine.git
2. Next, you will need to install several required dependencies. In Linux/WSL, you can run the following commands in your terminal (seperately) as one easy way to get them:
First, for GLFW:
sudo apt install libglfw3-dev
Second, for STB:
sudo apt install libstb-dev
3. Move into the project folder, "3DEngine":  (from the folder you ran git clone git@github.com:DuhDiamond/3DEngine.git ), you can do:
cd 3DEngine
4. Run the following command (in Linux/WSL) to build the project:
cmake -S . -B build
5. Run the following command (in Linux/WSL) to compile the project:
cmake --build build
6. Move into the build folder (in Linux/WSL) (where the project compiled):
cd 3DEngine
7. Run the project:
./3DEngine
8. Afterwards, a window should appear on your screen. Currently, you should see the following (link):
https://gyazo.com/c7851e9ef4e31fca7dcaab72aacae1ee
Since Commit 5, I have started adding videos to the CommitLogs folder as well, to show visual changes over time.

If you're having issues running the project, message me directly and i'll try to help you as best as I can!


## About
An attempt to build a basic 3D engine from scratch, drawing from:
- [*learnopengl.com*](https://learnopengl.com/)
- University computer graphics coursework
- [*Ray Tracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- Long-term: [*Physically Based Rendering*](https://pbr-book.org/)
... and looking to see how I can expand upon these sources with my own ideas and experimentation.

Progress logs are in the [CommitLogs](https://github.com/DuhDiamond/3DEngine/tree/main/CommitLogs) folder.

## Goals
Aiming to spend a few hours per week on this at minimum, to build a solid foundation in OpenGL and graphics fundamentals. Physically-based rendering is a longer-term stretch goal.