#ifndef __MARMOT_AST_H__
#define __MARMOT_AST_H__

#include "FuncExpr.h"
#include "Header.h"
#include "IrUtils.h"
#include "StaticExpr.h"
#include "StructExpr.h"
#include <ostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace marmot {
class AST {
private:
  std::error_code _ec;
  llvm::raw_fd_ostream *_llvm_ir_os;

  std::string _filename;

  std::unordered_map<std::string, std::unordered_map<std::string, int> *>
      _generic_structs_id_map;

  std::unordered_map<std::string, StructExpr *> _generic_structs;
  std::vector<StructExpr *> _structs;
  std::vector<StaticExpr *> _statics;
  std::vector<FuncExpr *> _funcs;

  std::unordered_map<std::string, llvm::PointerType *> _point_type_map;

public:
  AST(std::filesystem::path &abs_path);
  ~AST();
  void to_llvm_ir();

  void print();
  void add_concrete_struct(std::string &name, std::vector<TypeExpr *> types);
  void add_concrete_struct_if_not_exist(StructExpr *expr);

  inline void add_struct_expr(StructExpr *expr) { _structs.push_back(expr); }
  inline void add_static_expr(StaticExpr *expr) { _statics.push_back(expr); }
  inline void add_func_expr(FuncExpr *expr) { _funcs.push_back(expr); }
  inline void add_generic_struct_expr(StructExpr *expr) {
    _generic_structs.insert(std::make_pair(*(expr->identifier()), expr));
  }
};
} // namespace marmot

#endif