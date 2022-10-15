#ifndef __MARMOT_SYNTAX_EXPR_H__
#define __MARMOT_SYNTAX_EXPR_H__

#include "Header.h"

namespace marmot {
class SyntaxExpr {
protected:
  std::unordered_set<char> _end_tokens;
  int curr;
  std::string &chs;

public:
  SyntaxExpr() = delete;
  SyntaxExpr(const SyntaxExpr &expr) = delete;
  SyntaxExpr &operator=(const SyntaxExpr &expr) = delete;
  SyntaxExpr(std::string &chs, int cur);
  int getCurr();

  inline void add_end_token(char c) { _end_tokens.insert(c); }

  virtual void parse() = 0;
  virtual void print() = 0;
};
} // namespace marmot

#endif