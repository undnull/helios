# Getting started: Cloning
#### Git-based project
For git-based projects you can obtain the code using Git submodules:
```bash
git submodule add https://github.com/undnull/thorn.git
```

#### Other projects
For other projects you may just clone the repository recursively:
```bash
git clone --recursive https://github.com/undnull/thorn.git
```

#### Checking out
If the project happen to have a release or a tag present, it is highly recommended to checkout to it:
```bash
cd thorn
git checkout <tag_name>
```

#### Getting started
* [Requirements](doc/getting_started/00_requirements.md)
* **Cloning**
* [Building](doc/getting_started/02_building.md)
* [A blue Window](doc/getting_started/03_blue_window.md)
