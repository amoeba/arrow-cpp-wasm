#include <fstream>
#include <memory>

#include "emscripten.h"
#include "emscripten/bind.h"

#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <arrow/result.h>
#include <arrow/status.h>
#include <arrow/type.h>
#include <arrow/array/array_base.h>

arrow::Result<std::shared_ptr<arrow::Array>> BuildArray(int a, int b, int c, int d, int e) {
  std::shared_ptr<arrow::Array> arr;

  arrow::Int32Builder builder;
  ARROW_RETURN_NOT_OK(builder.Append(a));
  ARROW_RETURN_NOT_OK(builder.Append(b));
  ARROW_RETURN_NOT_OK(builder.Append(c));
  ARROW_RETURN_NOT_OK(builder.Append(d));
  ARROW_RETURN_NOT_OK(builder.Append(e));

  ARROW_ASSIGN_OR_RAISE(arr, builder.Finish())

  return arr;
}

std::string Crunch(int a, int b, int c, int d, int e) {
  auto answer = BuildArray(a, b, c, d, e);

  if (!answer.ok()) {
    return answer.status().message();
  }

  auto sum = arrow::compute::Sum({answer.ValueUnsafe()});

  if (!sum.ok()) {
    return answer.status().message();
  }

  return sum.ValueUnsafe().ToString();
}

// TODO: Wrap in Result/Status and use macros to simplify
std::string InspectFile(std::string filename) {
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
  emscripten::function("Crunch", &Crunch);
  emscripten::function("InspectFile", &InspectFile);
}
