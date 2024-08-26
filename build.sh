#!/bin/sh

# TODO: How can I use the pkg-config files in the emsdk sysroot to make the
# -I/-L arguments automatically populate?

if [ -z "$EMSDK" ]; then
  echo "$EMSDK not set. Is the emsdk initialized? Exiting."
  exit 1
fi

# TODO: This is very much hardcoded and could be made way better
emcc -O3 -s WASM=1 \
  -s EXPORTED_RUNTIME_METHODS='["cwrap"]' \
  -s EXPORTED_FUNCTIONS=_main \
  -s FORCE_FILESYSTEM=1 \
  -I"$EMSDK"/upstream/emscripten/cache/sysroot/include/arrow/ \
  -L"$EMSDK"/upstream/emscripten/cache/sysroot/lib/ \
  -larrow \
  main.cc
