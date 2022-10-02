#ifndef __MARMOT_STRUCT_EXPR_H__
#define __MARMOT_STRUCT_EXPR_H__

#include "syntax_expr.h"
#include "type_expr.h"

namespace marmot {

class struct_attr;

class struct_expr : public syntax_expr {
private:
  std::string *_identifier;
  std::vector<std::string> *generic_types;
  std::vector<struct_attr *> *_attrs;

public:
  struct_expr() = delete;
  struct_expr(const struct_expr &expr) = delete;
  struct_expr &operator=(const struct_expr &expr) = delete;
  struct_expr(std::string &chs, int curr);
  void parse();
  std::string *identifier();
  std::vector<struct_attr *> *attrs();

  void print();
};

class struct_attr : public syntax_expr {
private:
  type_expr *_attr_type;
  std::string *_attr_identifier;

public:
  struct_attr() = delete;
  struct_attr(const struct_attr &expr) = delete;
  struct_attr &operator=(const struct_attr &expr) = delete;
  struct_attr(std::string &chs, int curr);
  void parse();

  void print();

  inline type_expr *attr_type() { return _attr_type; };
  inline std::string *attr_identifier() { return _attr_identifier; };
};

} // namespace marmot

#endif