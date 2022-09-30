#pragma once

#include "syntax_expr.h"

namespace marmot {
class static_expr : public syntax_expr {
public:
  static_expr() = delete;
  static_expr(const static_expr &expr) = delete;
  static_expr &operator=(const static_expr &expr) = delete;
  static_expr(vector<char> *chs, int curr);
  void parse();
};
} // namespace marmot