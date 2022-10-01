#ifndef __MARMOT_TYPE_EXPR_H__
#define __MARMOT_TYPE_EXPR_H__

#include "header.h"
#include "syntax_expr.h"

namespace marmot {
class type_expr : public syntax_expr {
private:
  std::string *_identify;
  std::vector<std::string *> *type_names;

public:
  type_expr() = delete;
  type_expr(const type_expr &expr) = delete;
  type_expr &operator=(const type_expr &expr) = delete;
  type_expr(std::string &chs, int curr);
  void parse();
};
} // namespace marmot

#endif