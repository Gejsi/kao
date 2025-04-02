## Build Instructions

The `compile_commands.json` file assumes that CMake
is executed in a directory called build inside the project's root.

```console
mkdir build; cd build
cmake ..
make
```

This project requires gtk4 and libadwaita to compile.
