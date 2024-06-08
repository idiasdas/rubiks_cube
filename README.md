# Rubik's Cube

Implementing a Rubik's Cube with OpenGL.

Here, I put together the OpenGL tutorial and game engine series to practice. Feel free to use this code however you want, although you shouldn't trust it too much... If you have any questions or ideas, please don't hesitate to contact me.

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

4. Build the project and run the executable:

```bash
cd build
make
./rubiks_cube
```

5. Run tests:

```bash
cd build
ctest
```

# External Software

This project uses:

- glad
- glfw
- glm

You can find all external software in **ext/**.

# Controls

Currently, this project renders a rubiks cube that you can control and fly around. The mouse controls the camera. The following are the commands you can use:

|Keys|Action|
|-|-|
|Esc| Close program|
|W| Move forward|
|S| Move backward|
|A| Move left|
|D| Move right|
|Space| Move up|
|Right Ctrl | Move down|
|NumPad 2| Rotate cube's down face clockwise|
|NumPad 8| Rotate cube's up face clockwise|
|NumPad 4| Rotate cube's left face clockwise|
|NumPad 6| Rotate cube's right face clockwise|
|NumPad 5| Rotate cube's front face clockwise|
|NumPad 0| Rotate cube's back face clockwise|
|Left Shift + NumPad 2| Rotate cube's down face counter-clockwise|
|Left Shift + NumPad 8| Rotate cube's up face counter-clockwise|
|Left Shift + NumPad 4| Rotate cube's left face counter-clockwise|
|Left Shift + NumPad 6| Rotate cube's right face counter-clockwise|
|Left Shift + NumPad 5| Rotate cube's front face counter-clockwise|
|Left Shift + NumPad 0| Rotate cube's back face counter-clockwise|
