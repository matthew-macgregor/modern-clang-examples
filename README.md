# Modern C Language Examples

This repo was created as part of a "documentation crawl" to refresh my C language 
skills. My very first code was written in C twenty-odd years ago, but I haven't kept
current with modern features. I created examples of as much as I reasonably could. 
Additionally, I stepped through some C language references, trying to cover as much 
of the c library as possible.

Books referenced as part of the documentation crawl:

- *Modern C Quick Syntax Reference, Second Edition* by Mikael Olsson

## This Repository

This repo contains a number of examples, which are enumerated in the `CMakeLists.txt`
file at the top level. Many of the examples are fully cross-platform requiring only
a standards-compliant C runtime library. A few examples have external dependencies:

- Anything prefixed with `win` are for Windows (Win32/64 API). They will be skipped
  if you are building on a different platform.
- Some examples (for example, `sqlit3-*`) expect dependencies provided by 
  [vcpkg](https://vcpkg.io/en/index.html). Follow the setup steps for `vcpkg` first, 
  and install the dependencies listed in the README for that particular example.
- You can disable these examples by passing the option `USE_VCPKG=OFF` to `cmake`.

## Vcpkg Setup

After installing `vcpkg` define the following environment variable to tell cmake
where to find the dependencies. This supports VSCode and command line usage.

`CMAKE_TOOLCHAIN_FILE` set to `${path_to_vcpkg}\scripts\buildsystems\vcpkg.cmake`.

For Visual Studio, run `.\vcpkg integrate install` to allow VS to find the vcpkg 
dependencies.

## Building the Examples

### Prerequisites
- CMake 3.17+
- Windows: Visual Studio Build Tools (C++), GCC 8.3+
- Vcpkg 2022-03-30+
  - Windows: `vcpkg install sqlite3:x64-windows` or `sqlite3:x86-windows`
  - Linux:   `vcpkg install sqlite3:x64-TBD` or `sqlite3:x86-TBD`
  - MacOS:   `vcpkg install sqlite3:x64-TBD` or `sqlite3:x86-TBD`
  - (Naturally, you need to install for the architecture you are building.)

### Windows: Visual Studio 2019

Visual Studio 2019 has support for CMake-based projects. Choose the configuration you would like to build (Debug/Release). Open the base folder in VS and right click on `CMakeLists.txt > Configure`.

- To run the tests: right click on `CMakeLists.txt > Run Tests`
- To run a single example: choose the startup item in the dropdown on the toolbar.

### Windows: Visual Studio Code

Install [Microsoft CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools).

Make sure you have set up `vcpkg` and set the `CMAKE_TOOLCHAIN_FILE` environment variable (see above). This will allow CMake to find the dependencies installed by `vcpkg`.

1. Select the kit you wish to use for builds on the status bar at the bottom of the window. Example: `Visual Studio Community 2019 Release - amd64`
2. Configuration should begin automatically. You can trigger it manually by right-clicking on `CMakeLists.txt` and selecting "Configure All Projects".
3. Click "Build" `[ALL_BUILD]` to build all examples, or select an example to build and run only one.
4. Run the tests by clicking on `Run CTest` on the status bar at the bottom of the window. (After tests have run this changes to the message "x/y tests passing").

**Tip**: You may need to clean and reconfigure if something isn't building properly.

### Windows: Command Line

Make sure you have set up `vcpkg` and set the `CMAKE_TOOLCHAIN_FILE` environment variable (see above). This will allow CMake to find the dependencies installed by `vcpkg`.

Configure the build (obviously substituting the generator/toolset/architecture desired):

```ps1
# Configure:
cmake -S. -B./build -G "Visual Studio 16 2019" -T host=x64 -A x64

# Build all examples in Debug mode:
# Note that the -j {n} option spreads the job across threads.
cmake --build ./build --config Debug --target ALL_BUILD -j12
# Build selected example:
cmake --build ./build --config Debug --target conditionals
# Run the tests:
ctest --test-dir ./build -C Debug -T test --output-on-failure -j14
```

### Windows: VSCode + GCC

TODO

# Build for Other Platforms

TODO

## Philosophy: The Power of Practice

Over my years I've often found that one of the most important (and often overlooked)
skills is that of practice. This is true not just for learning a new skill, but also
for keeping existing skills honed. I used to think that the "side project" was the 
best way to practice programming skills, but it's certainly not the only way. Side
projects require a lot of thought and effort to make something useful, which isn't
the goal when learning or practicing your skills.

These days I enjoy what I call the "documentation crawl". The idea is to pick a
tool, language, project, or technology and systematically go through the documentation,
interacting with the information as you go. In the case of code, I've found that it
can be really useful to write unit tests as you encounter features. This not only
gives you hands on with the language or library, but also gives you practice writing
tests.

When you're done, you will have produced a set of runnable examples that you can use
to refresh your knowledge in the future.

Finally, it matters less what you do to practice and more that you do indeed practice
your skills. I have often been surprised when I learn something totally unexpected
while working on something with no goal of creating a useful project. It's important
to focus on honing core skills, something that practice makes easy to do.