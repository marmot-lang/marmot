#include "struct_expr.h"
#include "syntax_except.h"
#include "tokens.h"
#include "utils.h"
#include <initializer_list>
#include <iostream>

using namespace marmot;

struct_expr::struct_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr), _identify(nullptr),
      generic_types(new vector<string>()), attrs(new vector<struct_attr *>()) {}

void struct_expr::parse() {
  // parse struct identify
  int identify_begin = ignore_white_space(chs, curr);
  _identify = find_sequences(chs, identify_begin);

#ifdef DEBUG
  std::cout << "[Marmotc] Struct identify is: " << *_identify << std::endl;
#endif

  int identify_end = identify_begin + _identify->size();

  int body_begin = ignore_white_space(chs, identify_end);
  if (is_not_in(chs, body_begin, {tokens::LEFT_BRACE})) {
    throw new syntax_except(chs, body_begin);
  }

  int attr_begin = ignore_white_space(chs, body_begin + 1);
  while (is_not_in(chs, attr_begin, {tokens::RIGHT_BRACE})) {
    // parse struct's attribute
    struct_attr *attr = new struct_attr(chs, attr_begin);
    attr->parse();
    attr_begin = attr->getCurr();
    attr_begin = ignore_white_space(chs, attr_begin);

    if (is_not_in(chs, attr_begin, {tokens::SEMICOLON})) {
      throw syntax_except(chs, attr_begin);
    }

    attr_begin = ignore_white_space(chs, ++attr_begin);
  }

  curr = attr_begin + 1;
}

std::string *struct_expr::identify() { return _identify; }

struct_attr::struct_attr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr) {}

void struct_attr::parse() {
  _attr_type = new type_expr(chs, curr);
  _attr_type->parse();
  int type_end = _attr_type->getCurr();
  int identify_begin = ignore_white_space(chs, type_end);

  initializer_list<char> end_tokens = {tokens::SPACE, tokens::NEW_LINE,
                                       tokens::TAB, tokens::SEMICOLON};
  _attr_identify = find_sequences_before(chs, identify_begin, end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc] Struct attribute identify is: " << *_attr_identify
            << std::endl;
#endif

  curr = identify_begin + _attr_identify->length();
}