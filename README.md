<div align="center">

<img src="assets/logo.svg" height=250>

</div>

# nio

Yet another stream based C++ networking library. For now it only supports \*nix systems, Windows support is planned.

## Features

-   IPv4
-   IPv6
-   Unix sockets

## Usage

The library can be used in other projects via it's CMake integration. To put it siply, do some of this:

```cmake
...

add_subdirectory("path/in/your/project/to/nio/")

...
```

Then you can link your targets with:

```cmake
...

target_link_libraries(<Your target> NioStatic)

...
```

or if you prefer dynamic linking:

```cmake
...

target_link_libraries(<Your target> NioShared)

...
```

By default it builds the static version of the library, `libnio.a`. If you need the shared object version, simply append to you CMake flags: `-DNIO_BUILD_SHARED=ON`.

All of the header files needed are in `nio/include/`, I would recommend leaving them there for easy upgrades.

## Code

To get started simply add the `include/` directory of the repo to your include paths and you can access everything in a structured format. Code namespaces correspond to directories and classes to files.

For code examples see `tests/`.
