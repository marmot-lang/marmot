#include "ast.h"
#include "syntax_except.h"

using namespace marmot;

ast::ast() {
  chs = new vector<char>();
  structs = new vector<struct_expr *>();
  statics = new vector<static_expr *>();
}

ast::~ast() {
  delete chs;
  delete structs;
  delete statics;
}

void ast::append(char c) { chs->push_back(c); }

void ast::parse() {
  for (int i = 0; i < (*chs).size(); i++) {
    if (is_same(chs, i, 's') && is_same(chs, i + 1, 't')) {

      // parse struct
      if (is_same(chs, i + 2, 'r')) {

        struct_expr *stru = new struct_expr(chs, i);
        stru->parse();
        i = stru->getCurr();
        structs->push_back(stru);

      }

      // parse static
      else if (is_same(chs, i + 2, 'a')) {

        static_expr *stati = new static_expr(chs, i);
        stati->parse();
        i = stati->getCurr();
        statics->push_back(stati);
      }

    }
    // parse func
    else if (is_same(chs, i, 'f')) {
      func_expr *func = new func_expr(chs, i);
      func->parse();
      i = func->getCurr();
      funcs->push_back(func);

    } else {
      throw new syntax_except(chs, i);
    }
  }
}

void ast::toIR() {}