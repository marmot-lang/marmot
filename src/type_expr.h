#ifndef __MARMOT_TYPE_EXPR_H__
#define __MARMOT_TYPE_EXPR_H__

#include "header.h"
#include "syntax_expr.h"

namespace marmot {
class type_expr : public syntax_expr {
private:
  std::string *_identifier;
  std::vector<type_expr *> _type_names;

public:
  type_expr();
  type_expr(const type_expr &expr) = delete;
  type_expr &operator=(const type_expr &expr) = delete;
  type_expr(std::string &chs, int curr);

  void parse();
  void print();
  std::string generic_type_list_key();
  bool is_concrete(std::vector<std::string *> generic_type_names);
  type_expr *
  generate_concrete(std::unordered_map<std::string, type_expr *> &type_map);

  inline std::string *identifier() { return _identifier; }
  inline std::vector<type_expr *> type_names() { return _type_names; }
  inline bool is_generic() { return !_type_names.empty(); }
};
} // namespace marmot

#endif