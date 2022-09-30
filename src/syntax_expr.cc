#include "syntax_expr.h"

using namespace marmot;

syntax_expr::syntax_expr(vector<char> *chs, int curr) {
  this->chs = chs;
  this->curr = curr;
}

int syntax_expr::getCurr() { return curr; }