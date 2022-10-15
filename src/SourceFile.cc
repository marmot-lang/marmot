#include "SourceFile.h"
#include "Header.h"
#include "Utils.h"
#include <iostream>
#include <llvm-10/llvm/Support/raw_ostream.h>

using namespace marmot;

SourceFile::SourceFile(std::filesystem::path &_abs_path)
    : _abs_path(_abs_path), _src("") {
  std::filesystem::path name = _abs_path.filename();
}

SourceFile::~SourceFile() {
  delete &_abs_path;
  delete &_src;
}

void SourceFile::append(char c) { _src.push_back(c); }

AST *SourceFile::to_ast() {
  AST *marmot_ast = new AST(_abs_path);
  int curr = -1;

  while (++curr < _src.length()) {
    curr = ignoreWhiteSpace(_src, curr);

    if (isEnd(_src, curr)) {
      break;
    }

    if (isSameSequences(_src, curr, tokens::STRUCT)) {

#ifdef DEBUG
      std::cout << "[Marmotc Parser] Parse struct expression" << std::endl;
#endif

      int identifier_begin = curr + tokens::STRUCT.length();
      StructExpr *stru = new StructExpr(_src, identifier_begin);
      stru->parse();
      curr = stru->getCurr();

      marmot_ast->add_concrete_struct_if_not_exist(stru);

      if (stru->is_struct_template()) {
        marmot_ast->add_generic_struct_expr(stru);
      } else {
        marmot_ast->add_struct_expr(stru);
      }

    } else if (isSameSequences(_src, curr, tokens::STATIC)) {

      StaticExpr *stati = new StaticExpr(_src, curr);
      stati->parse();
      curr = stati->getCurr();
      marmot_ast->add_static_expr(stati);

    } else if (isSameSequences(_src, curr, tokens::FUNC)) {

      int identifier_begin = curr + tokens::FUNC.length();
      FuncExpr *func = new FuncExpr(_src, identifier_begin);
      func->parse();
      curr = func->getCurr();
      marmot_ast->add_func_expr(func);

    } else {
      if (isNotEnd(_src, curr)) {
        throw new SyntaxExcept(_src, curr);
      }
    }
  }

  return marmot_ast;
}

void SourceFile::print() {
  llvm::outs() << "Source file: ";
  llvm::outs().changeColor(llvm::raw_ostream::GREEN);
  llvm::outs() << "\"" << _abs_path.filename() << "\"";
  llvm::outs().resetColor();
  llvm::outs() << "\n\n";
  llvm::outs() << _src << "\n";
}