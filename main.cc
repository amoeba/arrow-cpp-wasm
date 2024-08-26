#include "arrow/io/file.h"
#include "arrow/io/interfaces.h"
#include "emscripten.h"

#include <arrow/api.h>
#include <arrow/status.h>
#include <arrow/ipc/reader.h>

arrow::Status RunMain() {
  // arrow::Int32Builder builder;

  // ARROW_RETURN_NOT_OK(builder.Append(1));
  // ARROW_RETURN_NOT_OK(builder.Append(2));
  // ARROW_RETURN_NOT_OK(builder.Append(3));
  // ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::Array> arr, builder.Finish())

  // ***
  std::shared_ptr<arrow::io::RandomAccessFile> input;
  ARROW_ASSIGN_OR_RAISE(input, arrow::io::ReadableFile::Open("foo.arrow"));
  auto read_options = arrow::ipc::IpcReadOptions::Defaults();
  ARROW_ASSIGN_OR_RAISE(auto reader, arrow::ipc::RecordBatchFileReader::Open(input, read_options));
  reader->schema()->ToString();

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
