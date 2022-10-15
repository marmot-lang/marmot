#ifndef __MARMOT_DECLARE_VARIABLE_EXPR_H__
#define __MARMOT_DECLARE_VARIABLE_EXPR_H__

#include "Header.h"
#include "TypeExpr.h"

namespace marmot {
class DeclareVariableExpr : public SyntaxExpr {
private:
  TypeExpr *_var_type;
  std::string *_var_identifier;

public:
  DeclareVariableExpr() = delete;
  DeclareVariableExpr(const DeclareVariableExpr &expr) = delete;
  DeclareVariableExpr &operator=(const DeclareVariableExpr &expr) = delete;
  DeclareVariableExpr(std::string &chs, int curr);

  void parse();
  void print();
  DeclareVariableExpr *
  generate_concrete(std::unordered_map<std::string, TypeExpr *> &type_map);
  bool is_concrete(std::vector<std::string *> generic_type_names);

  inline TypeExpr *var_type() { return _var_type; };
  inline std::string *var_identifier() { return _var_identifier; };
  inline bool is_generic() { return _var_type->is_generic(); }
  inline std::string generic_type_list_key() {
    return _var_type->generic_type_list_key();
  }
};
} // namespace marmot

#endif