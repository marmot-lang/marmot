#include "source_file.h"
#include "header.h"
#include "utils.h"
#include <iostream>
#include <llvm-10/llvm/Support/raw_ostream.h>

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

      marmot_ast->add_concrete_struct_if_not_exist(stru);

      if (stru->is_struct_template()) {
        marmot_ast->add_generic_struct_expr(stru);
      } else {
        marmot_ast->add_struct_expr(stru);
      }

    } else if (is_same_sequences(_src, curr, tokens::STATIC)) {

      static_expr *stati = new static_expr(_src, curr);
      stati->parse();
      curr = stati->getCurr();
      marmot_ast->add_static_expr(stati);

    } else if (is_same_sequences(_src, curr, tokens::FUNC)) {

      int identifier_begin = curr + tokens::FUNC.length();
      func_expr *func = new func_expr(_src, identifier_begin);
      func->parse();
      curr = func->getCurr();
      marmot_ast->add_func_expr(func);

    } else {
      if (is_not_end(_src, curr)) {
        throw new syntax_except(_src, curr);
      }
    }
  }

  return marmot_ast;
}

void source_file::print() {
  llvm::outs() << "Source file: ";
  llvm::outs().changeColor(llvm::raw_ostream::GREEN);
  llvm::outs() << "\"" << _abs_path.filename() << "\"";
  llvm::outs().resetColor();
  llvm::outs() << "\n\n";
  llvm::outs() << _src << "\n";
}