#ifndef __MARMOT_STRUCT_EXPR_H__
#define __MARMOT_STRUCT_EXPR_H__

#include "declare_variable_expr.h"
#include "syntax_expr.h"
#include "type_expr.h"

namespace marmot {

class struct_attr;

class struct_expr : public syntax_expr {
private:
  std::string *_identifier;
  std::vector<std::string *> _generic_type_names;
  std::vector<declare_variable_expr *> _attrs;

public:
  struct_expr(const struct_expr &expr) = delete;
  struct_expr &operator=(const struct_expr &expr) = delete;
  struct_expr(std::string &chs, int curr);
  void parse();
  std::string *identifier();
  std::vector<declare_variable_expr *> attrs();

  void print();
  std::string generic_type_list_key(std::vector<type_expr *> types);
  struct_expr *generate_concrete(std::vector<type_expr *> types, int id);
  std::vector<type_expr *> all_concrete_struct_attr_type();

  inline bool is_struct_template() { return !_generic_type_names.empty(); }
};
} // namespace marmot

#endif