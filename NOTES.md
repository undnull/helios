# Notes
This file contains some personal comments about how is the project organized and why I've chosen to organize it like that.  
Also beware of some crazy stuff that I'm planning to do.

## The project name
The project origin is a voxel sandbox, thus the name is still belongs to it.  
This _will_ be changed in future. The most possible variant is "Helios".

## OpenGL 4.6
I've chosen OpenGL 4.6 because I wanted to research this version a bit and was interested in using SPIR-V shaders so I don't have to worry about shader caching.  
At this point my code is compatible with even older GL versions (such as ubiquitous OpenGL 3.3) with extensions. Those extensions seem to be supported on a big amount of GPUs now.

## HLSL
I've chosen HLSL as a main shader language just because I generally don't like GLSL and its way to deal with built-in shader inputs and outputs.  
While GLSL has some hard-coded constant names, HLSL has semantics which means you can name those variables whatever you want.  
Another entry in the pros list is that you can organize your shader sources better since the entry point can return stuff.  

The shader compilation process is a bit complicated because glslangValidator doesn't support HLSL for OpenGL enrironment yet.  
The main problem now is semantics: they are just being bound to wrong places!

## Game or engine?
I was making a game but now I am going to make an engine with Godot-ish way of doing things:
* The engine is an executable that is being built from sources
* Game developers can add modules written in C++ in the engine
* The game itself is a bunch of assets and scripts
* Scripts can be compiled (in case of Lua or AngelScript) and distributed in binary form

## Licensing
I originally was making a game and choose GNU GPL 3.0 as a license.  
But over time the project started shaping to a game engine, so I've relicensed it to the MPL 2.0 because it allows me to have proprietary sources (game scripts) and proprietary modules for my games.

## Editor
I was often thinking about this. Will there be an embedded level editor or script editor? The answer is... **No**. I don't want to bloat the engine with some heavy stuff that won't be even used for production.  
Instead, I would write a small amount of plug-ins for VSCode (engine API auto-completion for scripts) and Tiled Editor (engine's tilemap format support). Of couse I will write my own toolset for stuff like JSON->BSON compiler.  
Be as simple as possible, right? :)

## Scripting language
I firstly was thinking about Lua as an easy to learn language that is widely supported.  
But I also like AngelScript for its C++-ish nature and syntax.  
I will choose that when the time comes.
