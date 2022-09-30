#pragma once

#include <vector>

using namespace std;

namespace marmot {
class syntax_expr {
protected:
  int curr;
  vector<char> *chs;

public:
  syntax_expr() = delete;
  syntax_expr(const syntax_expr &expr) = delete;
  syntax_expr &operator=(const syntax_expr &expr) = delete;
  syntax_expr(vector<char> *chs, int cur);
  int getCurr();
  virtual void parse() = 0;
};
} // namespace marmot