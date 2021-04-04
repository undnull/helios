# Cloning
#### Git-based project
For git-based projects you can obtain the code using Git submodules:
```bash
git submodule add https://github.com/undnull/thorn.git
cd thorn
git submodule update --init --recursive
```

#### Other projects
For other projects you may just clone the repository recursively:
```bash
git clone --recursive https://github.com/undnull/thorn.git
cd thorn
```

#### Checking out
If the project happen to have a release or a tag present, it is highly recommended to checkout to it:
```bash
cd thorn
git checkout <tag_name>
```

# Getting Started
* [Root](../getting_started.md)
* [Requirements](00_requirements.md)
* **Cloning**
* [Building](02_building.md)
* [A blue window](03_blue_window.md)
