#ifndef __MARMOT_STATIC_EXPR_H__
#define __MARMOT_STATIC_EXPR_H__

#include "syntax_expr.h"

namespace marmot {
class static_expr : public syntax_expr {
public:
  static_expr() = delete;
  static_expr(const static_expr &expr) = delete;
  static_expr &operator=(const static_expr &expr) = delete;
  static_expr(std::string &chs, int curr);
  void parse();

  void print();
};
} // namespace marmot

#endif