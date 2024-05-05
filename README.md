Install
---

**Il faut clone en incluant les submodules (ce qui inclurat SOIL)**

```
git clone <cet url> --depth=1 --recurse-submodules --shallow-submodules
mkdir BUILD
cmake -S . -B BUILD
cmake --build BUILD
./BUILD/cours_soil
```