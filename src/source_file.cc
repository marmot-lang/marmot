#include "source_file.h"
#include "header.h"
#include "utils.h"

using namespace marmot;

source_file::source_file(std::filesystem::path &source_path)
    : source_path(source_path), src("") {
  std::filesystem::path name = source_path.filename();
  filename = name.string();
}

source_file::~source_file() {
  delete &filename;
  delete &source_path;
  delete &src;
}

void source_file::append(char c) { src.push_back(c); }

ast *source_file::to_ast() {
  ast *marmot_ast = new ast(filename);
  int curr = -1;

  while (++curr < src.length()) {
    curr = ignore_white_space(src, curr);

    if (is_end(src, curr)) {
      break;
    }

    if (is_same_sequences(src, curr, tokens::STRUCT)) {

#ifdef DEBUG
      std::cout << "[Marmotc] Parser struct expression" << std::endl;
#endif

      int identify_begin = curr + tokens::STRUCT.length();
      struct_expr *stru = new struct_expr(src, identify_begin);
      stru->parse();
      curr = stru->getCurr();
      marmot_ast->add_struct_expr(stru);

    } else if (is_same_sequences(src, curr, tokens::STATIC)) {

      static_expr *stati = new static_expr(src, curr);
      stati->parse();
      curr = stati->getCurr();
      marmot_ast->add_static_expr(stati);

    } else if (is_same_sequences(src, curr, tokens::FUNC)) {

      //   func_expr *func = new func_expr(src, i);
      //   func->parse();
      //   i = func->getCurr();
      //   funcs->push_back(func);

    } else {
      if (is_not_end(src, curr)) {
        throw new syntax_except(src, curr);
      }
    }
  }

  return marmot_ast;
}