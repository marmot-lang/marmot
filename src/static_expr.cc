#include "static_expr.h"

using namespace marmot;

static_expr::static_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr) {}

void static_expr::parse() {}