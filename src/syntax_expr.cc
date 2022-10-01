#include "syntax_expr.h"

using namespace marmot;

syntax_expr::syntax_expr(std::string &chs, int curr) : chs(chs), curr(curr) {}

int syntax_expr::getCurr() { return curr; }