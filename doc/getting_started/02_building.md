# Getting started: Building
## Standalone
Some projects use libraries in their binary forms without building them.  
This part shows how to build Thorn for those projects.

#### Generating the CMake build directory
In most cases you should just use:
```bash
cmake -B build .
```

This command will run CMake which will generate a bunch of important build files in the `build` subdirectory.

#### Using alternative CMake generators
Sometimes CMake may chose the invalid generator. If that happens, use:
```bash
cmake -B build -G "<My Beloved Generator>" .
```

#### Building
In most cases it is enough to build the library using CMake itself:
```bash
cmake --build build
```

## Subproject
Some other projects often use CMake to build their dependencies from sources.  
Thorn is oriented to work with those projects.  
This part assumes that you already have a CMake project.

#### Adding Thorn subdirectory
Should be fairly easy:
```cmake
add_subdirectory(thorn)
```

#### Adding Thorn dependency
Should be also fairly easy:
```cmake
# Of course you would need to replace "my_beloved_game"
# with the correct name of your target.
target_link_libraries(my_beloved_game thorn)
```

#### Building
Just build your project as usual.  
**Note:** if you don't use CMake to build project directly, consider updaing the project files!

#### Getting started
* [Root](../getting_started.md)
* [Requirements](00_requirements.md)
* [Cloning](01_cloning.md)
* **Building**
* [A blue Window](03_blue_window.md)
