#ifndef __MARMOT_SOURCE_FILE__
#define __MARMOT_SOURCE_FILE__

#include "AST.h"
#include "Header.h"

namespace marmot {
class SourceFile {
private:
  std::filesystem::path &_abs_path;
  std::string _src;

public:
  SourceFile() = delete;
  SourceFile(const SourceFile &expr) = delete;
  SourceFile &operator=(const SourceFile &expr) = delete;
  SourceFile(std::filesystem::path &source_path);

  ~SourceFile();

  void append(char c);
  AST *to_ast();

  void print();
};
} // namespace marmot

#endif