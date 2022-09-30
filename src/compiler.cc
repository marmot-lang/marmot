#include <filesystem>
#include <fstream>
#include <iostream>

#include "ast.h"
#include "compiler.h"

using namespace std;
using namespace std::filesystem;
using namespace marmot;

void compiler::compile(char *relative_path) {
  path current = current_path();
  path absolute = current / relative_path;

  ast *marmot_ast = new ast();

  if (exists(absolute)) {
    ifstream file_stream = ifstream(absolute, ios_base::in);

    while (!file_stream.eof()) {
      char c = file_stream.get();

      if (file_stream.fail()) {
        break;
      }

      marmot_ast->append(c);
    }
  }

  delete marmot_ast;
}