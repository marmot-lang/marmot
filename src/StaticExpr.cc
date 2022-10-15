#include "StaticExpr.h"

using namespace marmot;

StaticExpr::StaticExpr(std::string &chs, int curr)
    : SyntaxExpr::SyntaxExpr(chs, curr) {}

void StaticExpr::parse() {}

void StaticExpr::print() {}