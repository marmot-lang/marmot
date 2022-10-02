#ifndef __MARMOT_SYNTAX_EXPR_H__
#define __MARMOT_SYNTAX_EXPR_H__

#include "header.h"

namespace marmot {
class syntax_expr {
protected:
  std::unordered_set<char> _end_tokens;
  int curr;
  std::string &chs;

public:
  syntax_expr() = delete;
  syntax_expr(const syntax_expr &expr) = delete;
  syntax_expr &operator=(const syntax_expr &expr) = delete;
  syntax_expr(std::string &chs, int cur);
  int getCurr();

  inline void add_end_token(char c) { _end_tokens.insert(c); }

  virtual void parse() = 0;
  virtual void print() = 0;
};
} // namespace marmot

#endif