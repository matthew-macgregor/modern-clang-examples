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
and install the dependencies listed in the README for the example.
- You can disable these examples by passing the option `USE_VCPKG=OFF` to `cmake`.

After installing `vcpkg` define the following environment variable:
`VCPKG_CMAKE_TOOLCHAIN_FILE` set to `${path_to_vcpkg}\scripts\buildsystems\vcpkg.cmake`.

## Building the Examples

### Windows: Visual Studio 2019

Visual Studio 2019 has support for CMake-based projects. Choose the configuration you
would like to build (Debug/Release). Open the base folder in VS and right click on 
`CMakeLists.txt > Configure`.

- To run the tests: right click on `CMakeLists.txt > Run Tests`
- To run a single example: choose the startup item in the dropdown on the toolbar.

### Windows: Visual Studio Code

TODO

### Windows: Command Line

TODO

### Other Platforms

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