#ifndef __MARMOT_DECLARE_VARIABLE_EXPR_H__
#define __MARMOT_DECLARE_VARIABLE_EXPR_H__

#include "header.h"
#include "type_expr.h"

namespace marmot {
class declare_variable_expr : public syntax_expr {
private:
  type_expr *_var_type;
  std::string *_var_identifier;

public:
  declare_variable_expr() = delete;
  declare_variable_expr(const declare_variable_expr &expr) = delete;
  declare_variable_expr &operator=(const declare_variable_expr &expr) = delete;
  declare_variable_expr(std::string &chs, int curr);

  void parse();
  void print();
  declare_variable_expr *
  generate_concrete(std::unordered_map<std::string, type_expr *> &type_map);
  bool is_concrete(std::vector<std::string *> generic_type_names);

  inline type_expr *var_type() { return _var_type; };
  inline std::string *var_identifier() { return _var_identifier; };
  inline bool is_generic() { return _var_type->is_generic(); }
  inline std::string generic_type_list_key() {
    return _var_type->generic_type_list_key();
  }
};
} // namespace marmot

#endif