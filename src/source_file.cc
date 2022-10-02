#include "source_file.h"
#include "header.h"
#include "utils.h"
#include <iostream>

using namespace marmot;

source_file::source_file(std::filesystem::path &_abs_path)
    : _abs_path(_abs_path), _src("") {
  std::filesystem::path name = _abs_path.filename();
}

source_file::~source_file() {
  delete &_abs_path;
  delete &_src;
}

void source_file::append(char c) { _src.push_back(c); }

ast *source_file::to_ast() {
  ast *marmot_ast = new ast(_abs_path);
  int curr = -1;

  while (++curr < _src.length()) {
    curr = ignore_white_space(_src, curr);

    if (is_end(_src, curr)) {
      break;
    }

    if (is_same_sequences(_src, curr, tokens::STRUCT)) {

#ifdef DEBUG
      std::cout << "[Marmotc Parser] Parse struct expression" << std::endl;
#endif

      int identifier_begin = curr + tokens::STRUCT.length();
      struct_expr *stru = new struct_expr(_src, identifier_begin);
      stru->parse();
      curr = stru->getCurr();
      marmot_ast->add_struct_expr(stru);

    } else if (is_same_sequences(_src, curr, tokens::STATIC)) {

      static_expr *stati = new static_expr(_src, curr);
      stati->parse();
      curr = stati->getCurr();
      marmot_ast->add_static_expr(stati);

    } else if (is_same_sequences(_src, curr, tokens::FUNC)) {

      //   func_expr *func = new func_expr(src, i);
      //   func->parse();
      //   i = func->getCurr();
      //   funcs->push_back(func);

    } else {
      if (is_not_end(_src, curr)) {
        throw new syntax_except(_src, curr);
      }
    }
  }

  return marmot_ast;
}

void source_file::print() {
  std::cout << "Source file: " << _abs_path.filename() << std::endl
            << std::endl;
  std::cout << _src << std::endl;
}