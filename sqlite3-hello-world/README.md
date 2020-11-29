# Hello World with SQLite3

- `vcpkg` is required for this project.
- Set the path to `vcpkg` in `settings.json` to the location of `vcpkg/scripts/buildsystems/vcpkg.cmake` on your system.

```
"cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE": "${workspaceFolder}/../../../c++/vcpkg/scripts/buildsystems/vcpkg.cmake"
}
```