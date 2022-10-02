#ifndef __MARMOT_AST_H__
#define __MARMOT_AST_H__

#include "func_expr.h"
#include "header.h"
#include "llvm_ir_utils.h"
#include "static_expr.h"
#include "struct_expr.h"
#include <ostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace marmot {
class ast {
private:
  std::error_code _ec;
  llvm::raw_fd_ostream *_llvm_ir_os;

  std::string _filename;

  std::unordered_map<std::string, std::unordered_map<std::string, int> *>
      _generic_structs_id_map;

  std::unordered_map<std::string, struct_expr *> _generic_structs;
  std::vector<struct_expr *> _structs;
  std::vector<static_expr *> _statics;
  std::vector<func_expr *> _funcs;

  std::unordered_map<std::string, llvm::PointerType *> _point_type_map;

public:
  ast(std::filesystem::path &abs_path);
  ~ast();
  void to_llvm_ir();

  void print();
  void add_concrete_struct(std::string &name, std::vector<type_expr *> types);
  void add_concrete_struct_if_not_exist(struct_expr *expr);

  inline void add_struct_expr(struct_expr *expr) { _structs.push_back(expr); }
  inline void add_static_expr(static_expr *expr) { _statics.push_back(expr); }
  inline void add_func_expr(func_expr *expr) { _funcs.push_back(expr); }
  inline void add_generic_struct_expr(struct_expr *expr) {
    _generic_structs.insert(std::make_pair(*(expr->identifier()), expr));
  }
};
} // namespace marmot

#endif