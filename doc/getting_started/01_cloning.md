# Cloning
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
