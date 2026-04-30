## About

A work-in-progress 3D rendering engine built as a learning project to explore graphics programming, drawing from:
- [*learnopengl.com*](https://learnopengl.com/)
- University computer graphics coursework
- [*Ray Tracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- Long-term: [*Physically Based Rendering*](https://pbr-book.org/)
- ... and looking to see how I can expand upon these sources with my own ideas and experimentation.

Camera controls:
<video src="https://github.com/user-attachments/assets/57283446-5a6b-43bb-b602-14efaf5493b3"></video>

Specular highlights reacting to camera position:
<video src="https://github.com/user-attachments/assets/57283446-5a6b-43bb-b602-14efaf5493b3"></video>

Progress logs are in the [CommitLogs](https://github.com/DuhDiamond/3DEngine/tree/main/CommitLogs) folder. Additionally, since Commit 5, I have started adding videos to the CommitLogs folder as well, to show visual changes over time.

## Goals

The goal of this project is to develop an application where you can fly through a scene and place various externally imported 3D models in a rendered environment.
Essentially, a scene viewer where you can mix and match models, lights, and adjust every object property from an interactive user interface.

The project is split as follows:

### Scene and Object Representation
1. Implementing 3D Object data structures from scratch:
   - I want to learn more about building complex systems.
   - I'm implementing my own data structure representations to abstract away OpenGL API buffer calls through object-oriented programming functionality.
   - Implementing functionality to hold loaded data as general assets that can be mix-and-matched, such as one loaded mesh being initialized twice with different materials.
2. Object scene handling:
   - I want to learn more about data storage and retrieval. My next step is to pack these data structures into a system to efficiently handle the entire scene's instances in an organized structure.
### Renderer and Lighting
1. Setting up the pipeline for mixed rendering:
   - I want the mix-and-match systems to additionally carry over to the material types. I'm implementing various vertex shaders to represent different types of lighting, such as phong-shaded objects and physically-based-rendering ones through seperate vertex shaders, alongside their object/material types.
2. Implementing raytracing:
   - I'm working towards eventually implementing hybrid raytracing effects, for higher-fidelity rendering of things like glass.
### Interactive User Interface (Frontend)
1. Lastly, all of this will be accessible from a user interface.
   - It will let you load meshes of various filetypes, various texture formats, and mix-and-match them and place them in the scene alongside light objects. It will also let you adjust the properties of instanced objects.

## How to run:

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
8. Afterwards, a window should appear on your screen.
You can check out what should be currently visible according to the most recent .mp4 video file in the CommitLogs folder.

If you're having issues running the project, message me directly and I'll help you as best as I can!
