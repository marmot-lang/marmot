#include "type_expr.h"
#include "syntax_expr.h"
#include "tokens.h"
#include "utils.h"
#include <llvm-10/llvm/Support/raw_ostream.h>

using namespace marmot;

type_expr::type_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr) {
  _end_tokens.insert(tokens::LEFT_ANGLE_BRACKET);
  _end_tokens.insert(tokens::RIGHT_ANGLE_BRACKET);
  _end_tokens.insert(tokens::SPACE);
  _end_tokens.insert(tokens::NEW_LINE);
  _end_tokens.insert(tokens::TAB);
}

void type_expr::parse() {
  _identifier = find_sequences_before(chs, curr, _end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Type is: " << *_identifier << std::endl;
#endif

  int identifier_end = curr + _identifier->length();
  int type_names_begin = ignore_white_space(chs, identifier_end);
  int type_names_end = type_names_begin;

  if (is_in(chs, type_names_begin, {tokens::LEFT_ANGLE_BRACKET})) {
    type_names_begin = ignore_white_space(chs, ++type_names_begin);
    while (is_not_same(chs, type_names_begin, tokens::RIGHT_ANGLE_BRACKET)) {
      // parse type names
      type_names_begin = ignore_white_space(chs, type_names_begin);
      type_expr *type_item = new type_expr(chs, type_names_begin);
      type_item->add_end_token(tokens::COMMA);
      type_item->parse();
      type_names_begin = type_item->getCurr();
      _type_names.push_back(type_item);

      type_names_begin = ignore_white_space(chs, type_names_begin);
      if (is_not_in(chs, type_names_begin,
                    {tokens::RIGHT_ANGLE_BRACKET, tokens::COMMA})) {
        throw new syntax_except(chs, type_names_begin);
      }

      if (is_same(chs, type_names_begin, tokens::COMMA)) {
        type_names_begin++;
      }
    }

    type_names_end = ++type_names_begin;
  }

  curr = type_names_end;
}

void type_expr::print() {
  llvm::outs() << *_identifier;

  if (!_type_names.empty()) {
    llvm::outs() << "<";
    _type_names[0]->print();
    for (int i = 1; i < _type_names.size(); i++) {
      llvm::outs() << ", ";
      _type_names[i]->print();
    }
    llvm::outs() << ">";
  }
}

std::string type_expr::generic_type_list_key() {
  std::string key = "";
  key.append(*_identifier);
  if (!_type_names.empty()) {
    key.append("<");
    key.append(_type_names[0]->generic_type_list_key());
    for (int i = 1; i < _type_names.size(); i++) {
      key.append(",");
      key.append(_type_names[i]->generic_type_list_key());
    }
    key.append(">");
  }
  return key;
}

bool type_expr::is_concrete(std::vector<std::string *> generic_type_names) {
  for (type_expr *expr : _type_names) {
    for (std::string *type_name : generic_type_names) {
      if (expr->is_generic()) {
        if (!expr->is_concrete(generic_type_names)) {
          return false;
        }
      } else {
        if (is_same(*(expr->_identifier), *type_name)) {
          return false;
        }
      }
    }
  }
  return true;
}

type_expr *type_expr::generate_concrete(
    std::unordered_map<std::string, type_expr *> &type_map) {
  type_expr *expr = new type_expr(chs, curr);
  std::vector<type_expr *> type_names;
  expr->_type_names = type_names;
  if (is_generic()) {
    expr->_identifier = _identifier;
    for (type_expr *type : _type_names) {
      type_names.push_back(type->generate_concrete(type_map));
    }
  } else {
    std::unordered_map<std::string, type_expr *>::iterator itr =
        type_map.find(*_identifier);
    if (itr._M_cur != nullptr) {
      return itr->second;
    }
  }
  return expr;
}