# clings

![cling-logo](https://github.com/Trevodorax/clings/assets/73560235/d4ef8356-014b-4caa-9287-21706a6f7169)

This project contains a collection of exercises to learn [C](https://en.wikipedia.org/wiki/C_(programming_language)) and is blazingly inspired by [Rustlings](https://github.com/rust-lang/rustlings).

## Requirements
* Having CMake [installed](https://cmake.org/download/)
## Quickstart

You can build the project with the following commands:
```bash
cmake -S . -B build && cmake --build build
```

You can then run the project with:
```bash
./build/clings
```

You should see the following output:
```text
Compiling katas/00_intro/intro.c
Success !

Hello !
This exercise compiles successfully. The...
```

IT WORKS ! You can now start coding.

Update the file `katas/00_intro/intro.c` and remove the comment `// I AM NOT DONE` to pass to the next 
```bash
cmake -S . -B build && cmake --build build
./build/clings
```

## Tests
After building the project in [Quickstart](#quickstart), you can run the tests with:
```shell
ctest --test-dir build
```