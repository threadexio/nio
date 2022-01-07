<div align="center">

# nio

## Yet another C++ networking library

</div>

<br>

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
