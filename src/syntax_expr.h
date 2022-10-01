#ifndef __MARMOT_SYNTAX_EXPR_H__
#define __MARMOT_SYNTAX_EXPR_H__

#include "header.h"

namespace marmot {
class syntax_expr {
protected:
  int curr;
  std::string &chs;

public:
  syntax_expr() = delete;
  syntax_expr(const syntax_expr &expr) = delete;
  syntax_expr &operator=(const syntax_expr &expr) = delete;
  syntax_expr(std::string &chs, int cur);
  int getCurr();
  virtual void parse() = 0;
};
} // namespace marmot

#endif