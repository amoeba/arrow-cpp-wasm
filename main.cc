#include "emscripten.h"

#include <arrow/api.h>
#include <arrow/status.h>

arrow::Status RunMain() {
  arrow::Int32Builder builder;

  ARROW_RETURN_NOT_OK(builder.Append(1));
  ARROW_RETURN_NOT_OK(builder.Append(2));
  ARROW_RETURN_NOT_OK(builder.Append(3));
  ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::Array> arr, builder.Finish())

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
