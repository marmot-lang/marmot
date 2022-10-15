#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Header.h"
#include "SourceFile.h"
#include "SyntaxExcept.h"
#include "Version.h"

using namespace marmot;

int main(int argc, char *argv[]) {
  version::print();

  for (int i = 1; i < argc; i++) {
    char *relative_path = argv[i];

    std::filesystem::path current = std::filesystem::current_path();
    std::filesystem::path absolute = current / relative_path;

    if (std::filesystem::exists(absolute) &&
        !std::filesystem::is_directory(absolute)) {
      std::ifstream file_stream = std::ifstream(absolute, std::ios_base::in);

      SourceFile *file = new SourceFile(absolute);

      while (!file_stream.eof()) {
        char c = file_stream.get();

        if (file_stream.fail()) {
          break;
        }

        file->append(c);
      }

      file->print();

      try {
        AST *marmot_ast = file->to_ast();
        marmot_ast->print();
        std::cout << std::endl;
        marmot_ast->to_llvm_ir();
      } catch (SyntaxExcept *e) {
        std::cout << std::endl << "Syntax Exception in: " << std::endl;
        std::cout << *(e->message()) << std::endl;
      }
    }
  }

  return 0;
}