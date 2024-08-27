#include <fstream>

#include "emscripten.h"
#include "emscripten/bind.h"

#include <arrow/api.h>
#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/type.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>

std::string ProcessFile(std::string filename) {
  auto open_result =
      arrow::io::ReadableFile::Open(filename, arrow::default_memory_pool());

  if (!open_result.ok()) {
    return "Failed to open file: " + filename + " with error " +
           open_result.status().message();
  }

  auto rbr_result =
      arrow::ipc::RecordBatchFileReader::Open(open_result.ValueUnsafe());

  if (!rbr_result.ok()) {
    return "Failed to RBR reader for file: " + filename + " with error " +
           rbr_result.status().message();
  }

  auto ipc_reader = rbr_result.ValueUnsafe();

  // Read a batch so we can print schema??
  std::shared_ptr<arrow::RecordBatch> rbatch;
  auto read_result = ipc_reader->ReadRecordBatch(0);

  if (!read_result.ok()) {
    return "Failed to read a single record batch from file: " + filename +
           " with error " + read_result.status().message();
  }

  // WIP: Just return schema as string for now... In the future, return an
  // object with more info about the file?
  return read_result.ValueUnsafe()->schema()->ToString();
}

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::function("ProcessFile", &ProcessFile);
}
