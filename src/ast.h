#ifndef __MARMOT_AST_H__
#define __MARMOT_AST_H__

#include "func_expr.h"
#include "header.h"
#include "llvm_ir_utils.h"
#include "static_expr.h"
#include "struct_expr.h"
#include <ostream>

namespace marmot {
class ast {
private:
  std::error_code _ec;
  llvm::raw_fd_ostream *_llvm_ir_os;

  std::string _filename;
  std::vector<struct_expr *> *_structs;
  std::vector<static_expr *> *_statics;
  std::vector<func_expr *> *_funcs;

public:
  ast(std::filesystem::path &abs_path);
  ~ast();
  void add_struct_expr(struct_expr *expr);
  void add_static_expr(static_expr *expr);
  void add_func_expr(func_expr *expr);
  void to_llvm_ir();

  void print();
};
} // namespace marmot

#endif