# Hello World with SQLite3

[vcpkg](https://vcpkg.io/en/index.html) is required for this project. After ensuring that `vcpkg` is installed and configured,
run the following:

`vcpkg install sqlite3 --triplet {arch}`

You need to be sure to install for your target architecture in your build configuration. For example, if you're building for 
x64 Windows OS, you'll need to install `--triplet x64-windows`.

### Visual Studio Code

- Set the path to `vcpkg` in `settings.json` to the location of `vcpkg/scripts/buildsystems/vcpkg.cmake` on your system. 
  Something like the example below:

```
"cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE": "${workspaceFolder}/../../../c++/vcpkg/scripts/buildsystems/vcpkg.cmake"
}
```