# Build script
Since Thorn uses pre-compiled shaders, I wrote a build script that automates the shader building process.

#### Command line
```
$ ./tools/buildshaders.sh -h                                                            usage: ./tools/buildshaders.sh [-m <path>] [-o <path>] [-r] [-h]
example: ./tools/buildshaders.sh -r -o assets/shaders
options:
  -m <path>   : add the manifest file
  -o <path>   : set the output directory
  -r          : force rebuild
  -h          : print this message and exit
```

#### Manifest file
Shader manifest files are just text files with shader source names that need to be compiled. That helps to ignore unused shaders that you would want to leave for better times.  
A manifest file example:
```
background.frag.hlsl
background.vert.hlsl
blit.frag.hlsl
blit.vert.hlsl
sprite.frag.hlsl
sprite.vert.hlsl
tilemap.frag.hlsl
tilemap.vert.hlsl
```

#### Output directory
The script places all built files in a directory.  
If the specified path doesn't exists, the script tries to create it.

#### Default values
Default manifest and output paths are present to simplify the internal shader building process (Thorn is still in development!).

#### Build process
Since you can't compile HLSL directly to OpenGL, I use a trick called chain-compilation:
1. Firstly we compile HLSL for Vulkan and emit SPIR-V to an intermediate directory.
2. Secondly we decompile this SPIR-V to OpenGL-compatible GLSL.
3. Finally we compile this GLSL to OpenGL SPIR-V and copy the built binary to the output directory.

# Shader Guide
* [Root](../shader_guide.md)
* [Requirements](00_requirements.md)
* [Thorn's HLSL](01_thorns_hlsl.md)
* **Build script**
* [Shader example](03_shader_example.md)
