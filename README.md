# Rubik's Cube

Implementing a Rubik's Cube with OpenGL.

Here, I put together the OpenGL tutorial and game engine series to practice. Feel free to use this code however you want, although you shouldn't trust it too much... If you have any questions or ideas, please don't hesitate to contact me.

# Requirements

The [OpenGL tutorial](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/) specifies the following libraries as requirements:

``` bash
cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev
```
Furthermore, I use `gcc14 11.4.0` to compile the source code. A friend of mine ran into problems with `Clang`, and for now, I'm not looking into maintaining compatibility.

Finally, your graphics card must support OpenGL 4.6.

# Quick Start

1. Clone this repo:

```bash
git clone https://github.com/idiasdas/rubiks_cube.git
```

2. Initialize the submodules:

```bash
git submodule update --init
```

3. Configure CMake:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

4. Build the project:

```bash
cd build
make
```

5. Run tests:

```bash
cd build
ctest
```

6. Run executable

```bash
cd build
./rubiks_cube
```

> [!NOTE]
> You need to run the executable from within the build directory you specified in step 3. When you build this project, it saves the relative path from the chosen build directory to the `utils/` directory. This allows the program to load the shaders during runtime.

# External Software

This project uses:

- glad
- glfw
- glm

You can find all external software in **ext/**.

# Controls

Currently, this project renders a Rubik's cube that you can control and fly around. The mouse controls the camera. The following are the commands you can use:

|Keys|Action|
|-|-|
|Esc| Close program|
|W| Move forward|
|S| Move backward|
|A| Move left|
|D| Move right|
|Space| Move up|
|Right Ctrl | Move down|
|NumPad 2| Rotate bottom face clockwise|
|NumPad 8| Rotate top face clockwise|
|NumPad 4| Rotate left face clockwise|
|NumPad 6| Rotate right face clockwise|
|NumPad 5| Rotate front face clockwise|
|NumPad 0| Rotate back face clockwise|
|Left Shift + NumPad 0, 2, 4, 5, 6, 8 | Rotate face counterclockwise|
|R| Reset cube to initial state|

# Goals

- [x] Render Cube
- [x] Fly around
- [x] Move pieces
- [ ] Movement animation
- [ ] Animation queue
- [ ] Dynamic resize
- [ ] Event system
- [ ] Log system
- [ ] ImGui control and debug window
- [ ] Varying move animation speed
- [ ] GIF generator
- [ ] Solver
- [ ] Select cubes through camera's view vector
