#include "struct_expr.h"
#include "syntax_except.h"
#include "tokens.h"
#include "utils.h"
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>

using namespace marmot;

struct_expr::struct_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr), _identifier(nullptr),
      generic_types(new vector<string>()), _attrs(new vector<struct_attr *>()) {
}

void struct_expr::parse() {
  // parse struct identifier
  int identifier_begin = ignore_white_space(chs, curr);
  _identifier = find_sequences(chs, identifier_begin);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Struct identifier is: " << *_identifier
            << std::endl;
#endif

  int identifier_end = identifier_begin + _identifier->size();

  int body_begin = ignore_white_space(chs, identifier_end);
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

    _attrs->push_back(attr);

    if (is_not_in(chs, attr_begin, {tokens::SEMICOLON})) {
      throw syntax_except(chs, attr_begin);
    }

    attr_begin = ignore_white_space(chs, ++attr_begin);
  }

  curr = attr_begin;
}

std::string *struct_expr::identifier() { return _identifier; }
std::vector<struct_attr *> *struct_expr::attrs() { return _attrs; }

void struct_expr::print() {
  std::cout << "[Marmot AST] (Struct) identifier: " << *_identifier
            << std::endl;

  for (struct_attr *stru_expr : *_attrs) {
    stru_expr->print();
  }
}

struct_attr::struct_attr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr) {}

void struct_attr::parse() {
  _attr_type = new type_expr(chs, curr);
  _attr_type->parse();
  int type_end = _attr_type->getCurr();
  int identifier_begin = ignore_white_space(chs, type_end);

  initializer_list<char> end_tokens = {tokens::SPACE, tokens::NEW_LINE,
                                       tokens::TAB, tokens::SEMICOLON};
  _attr_identifier = find_sequences_before(chs, identifier_begin, end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Struct attribute identifier is: "
            << *_attr_identifier << std::endl;
#endif

  curr = identifier_begin + _attr_identifier->length();
}

void struct_attr::print() {
  std::cout << "[Marmot AST] (Struct Attribute) identifier: "
            << *_attr_identifier << ", type: ";

  _attr_type->print();
  std::cout << std::endl;
}