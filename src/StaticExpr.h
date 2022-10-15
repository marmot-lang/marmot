#ifndef __MARMOT_STATIC_EXPR_H__
#define __MARMOT_STATIC_EXPR_H__

#include "SyntaxExpr.h"

namespace marmot {
class StaticExpr : public SyntaxExpr {
public:
  StaticExpr() = delete;
  StaticExpr(const StaticExpr &expr) = delete;
  StaticExpr &operator=(const StaticExpr &expr) = delete;
  StaticExpr(std::string &chs, int curr);
  void parse();

  void print();
};
} // namespace marmot

#endif