# clings

![cling-logo](https://github.com/Trevodorax/clings/assets/73560235/d4ef8356-014b-4caa-9287-21706a6f7169)

This project contains a collection of exercises to learn [C](https://en.wikipedia.org/wiki/C_(programming_language)) and is blazingly inspired by [Rustlings](https://github.com/rust-lang/rustlings).

## Quickstart
> This project uses [vcpkg](https://vcpkg.io/en/index.html) to manage dependencies. Please [install](https://vcpkg.io/en/getting-started) it before continuing. Then run `vcpkg install`.

You can build the project with the following commands:
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build
```
> /!\ Replace `[path to vcpkg]` with the path to your vcpkg installation.
> If you're using CLion, it's likely `~/.vcpkg-clion/vcpkg`.

You can then run the project with:
```bash
./build/clings
```

You should see the following output:
```text
Compiling katas/compilation_error.c
katas/compilation_error.c:6:5: error: expected expression
    return EXIT_SUCCESS;
    ^
1 error generated.
Compilation failure...

Compilation error
```

IT WORKS ! You can now start coding.

Update the file `katas/compilation_error.c` to make the program compile and run successfully.
Then run the project again to check your solution.
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build
./build/clings
```