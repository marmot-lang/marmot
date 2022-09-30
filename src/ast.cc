#include "ast.h"
#include <vector>

using namespace marmot;

ast::ast() { chs = new vector<char>(); }

ast::~ast() { delete chs; }

void ast::append(char c) { chs->push_back(c); }

void ast::build() {}

void ast::toIR() {}