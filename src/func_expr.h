#pragma once

#include "syntax_expr.h"

namespace marmot {
class func_expr : public syntax_expr {
public:
  func_expr() = delete;
  func_expr(const func_expr &expr) = delete;
  func_expr &operator=(const func_expr &expr) = delete;
  func_expr(vector<char> *chs, int curr);
  void parse();
};
} // namespace marmot