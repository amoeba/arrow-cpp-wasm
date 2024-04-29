#include "emscripten.h"

#include <arrow/status.h>

arrow::Status RunMain() {
  return arrow::Status::OK();
}

EMSCRIPTEN_KEEPALIVE
int main() {
  arrow::Status st = RunMain();

  if (st.ok()) {
    return 0;
  } else {
    return -1;
  }
}
