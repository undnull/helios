# Thorn
[![Doxygen](https://github.com/undnull/thorn/actions/workflows/doxygen.yml/badge.svg)](https://github.com/undnull/thorn/actions/workflows/doxygen.yml) [![Issues](https://img.shields.io/github/issues/undnull/thorn?style=flat)](https://github.com/undnull/thorn/issues) [![License](https://img.shields.io/github/license/undnull/thorn?style=flat)](https://github.com/undnull/thorn/blob/master/LICENSE)  

Thorn is a general-purpose set of libraries and abstractions to make the life of a 2D graphics programmer easier.  
You may call it "SFML, but a bit closer to the hardware" game engine.  

# Features
Well that's all cool but why to use it instead of other libraries?  
Well...
1. Objects **don't render themselves**. Instead, there are a bunch of renderers for different types of objects.
2. These renderers aim at the performance: almost everything is being drawn using a single draw call!
3. The API abstractions are literally zero-cost: everything is inlined in the header files!
4. Shaders are pre-compiled, removing the requirement to implement a unique shader cache for each application.
5. Shaders are written in HLSL.
6. As a consequence, the latest OpenGL version is recommended because it has all the needed extensions embedded in the core profile.
7. The project is being built **completely** from sources and is probably compatible with your CMake project!

# Building
**The project won't build on a headless system unless you have the required libraries**
### Standalone
1. Clone the repo:
   ```bash
   git clone --recursive https://github.com/undnull/thorn.git
   ```
2. Setup the CMake environment:
   ```bash
   cd thorn
   cmake -B build .
   ```
3. Build it:
   ```bash
   cmake --build build
   ```

### Submodule
1. Add the repo as a submodule:
   ```bash
   git submodule add https://github.com/undnull/thorn.git
   git submodule update --init --recursive
   ```
2. Add the project as a subdirectory in your CMakeLists:
   ```cmake
   add_subdirectory(thorn)
   ```
3. Add the project as a library to your executable:
   ```cmake
   target_link_libraries(my_game thorn)
   ```
4. Build the project as usual!

# Contributing
Feel free to contribute through PRs and Issues.  
Make sure your code is formatted as [described](CODE_STYLE.md).  
Use clang-format to correct your mistakes!

# Licensing
Thorn is licensed under MPL 2.0 License, see LICENSE for details.

### Dependencies
* **GLAD:** [MIT License](https://github.com/Dav1dde/glad/blob/master/LICENSE)
* **GLFW:** [zlib License](https://github.com/glfw/glfw/blob/master/LICENSE.md)
* **GLM:** [MIT License](https://github.com/g-truc/glm/blob/master/copying.txt#L36)
* **STB:** [Public Domain](https://github.com/nothings/stb/blob/master/LICENSE#L22)
