# arrow-cpp-wasm

Basic example of running Arrow C++ under WASM.

## Roadmap for main.cc

- [x] Create and use a Status object
- [x] Create an Array
- [ ] Create an Array from user input
- [ ] Call a compute kernel on that Array
- [ ] Show result to user

## Pre-requisites

- git
- emsdk
- A WASM-compatible build of Arrow C++

## Building Arrow for WASM

See <https://arrow.apache.org/docs/developers/cpp/emscripten.html>.

The following CMake preset is what I'm currently using but this can probably be removed once I fix build.sh to pass the right flags.

```json
{
  "name": "user",
  "description": "",
  "displayName": "",
  "inherits": [
    "features-emscripten"
  ],
  "cacheVariables": {
    "ARROW_WITH_SNAPPY": "OFF",
    "ARROW_SUBSTRAIT": "OFF",
    "ARROW_WITH_BROTLI": "OFF",
    "ARROW_ORC": "OFF",
    "ARROW_ACERO": "OFF"
  }
}
```

## Running

```sh
source emsdk/emsdk_env.sh
sh build.sh
```

When you open a web browser capable of running WASM binaries, you should see "0"
printed to the developer console.
