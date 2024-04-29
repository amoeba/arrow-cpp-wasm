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

## Running

```sh
source emsdk/emsdk_env.sh
sh build.sh
```

When you open a web browser capable of running WASM binaries, you should see "0"
printed to the developer console.
