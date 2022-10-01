#ifndef __MARMOT_AST_H__
#define __MARMOT_AST_H__

#include "func_expr.h"
#include "header.h"
#include "static_expr.h"
#include "struct_expr.h"

namespace marmot {
class ast {
private:
  std::string &filename;
  std::vector<struct_expr *> *structs;
  std::vector<static_expr *> *statics;
  std::vector<func_expr *> *funcs;
  inline bool is_same(std::string &chs, int i, char c) {
    return i < chs.length() && chs[i] == c;
  }

public:
  ast(std::string &filename);
  ~ast();
  void add_struct_expr(struct_expr *expr);
  void add_static_expr(static_expr *expr);
  void add_func_expr(func_expr *expr);
  void to_llvm_ir();
};
} // namespace marmot

#endif