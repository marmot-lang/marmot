#ifndef __MARMOT_SOURCE_FILE__
#define __MARMOT_SOURCE_FILE__

#include "ast.h"
#include "header.h"

namespace marmot {
class source_file {
private:
  std::string filename;
  std::filesystem::path &source_path;
  std::string src;

public:
  source_file() = delete;
  source_file(const source_file &expr) = delete;
  source_file &operator=(const source_file &expr) = delete;
  source_file(std::filesystem::path &source_path);

  ~source_file();

  void append(char c);
  ast *to_ast();
};
} // namespace marmot

#endif