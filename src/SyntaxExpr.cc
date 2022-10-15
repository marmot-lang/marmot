#include "SyntaxExpr.h"

using namespace marmot;

SyntaxExpr::SyntaxExpr(std::string &chs, int curr) : chs(chs), curr(curr) {}

int SyntaxExpr::getCurr() { return curr; }