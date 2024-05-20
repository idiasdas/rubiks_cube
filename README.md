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
