# arrow-cpp-wasm

Basic example of running Arrow C++ under WASM.

## Roadmap for main.cc

- Compute example
  - [x] Create and use a Status object
  - [x] Create an Array
  - [x] Create an Array from user input
  - [x] Call a compute kernel on that Array
  - [x] Show result to user
- Inspect Arrow IPC files
  - [x] Open a file and print schema
- Your idea here..

## Pre-requisites

- git
- emsdk
- A WASM-compatible build of Arrow C++

## Building Arrow for WASM

See <https://arrow.apache.org/docs/developers/cpp/emscripten.html>.

## Running

```sh
source emsdk/emsdk_env.sh
sh build.sh
```

Now open index.html in a web browser.
