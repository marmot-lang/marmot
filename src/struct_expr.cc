#include "struct_expr.h"
#include "syntax_except.h"
#include "tokens.h"
#include "type_expr.h"
#include "utils.h"
#include <llvm-10/llvm/Support/raw_ostream.h>
#include <string>
#include <unordered_map>
#include <utility>

using namespace marmot;

struct_expr::struct_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr), _identifier(nullptr) {}

void struct_expr::parse() {
  // parse struct identifier
  int identifier_begin = ignore_white_space(chs, curr);
  _identifier =
      find_sequences_before(chs, identifier_begin,
                            {tokens::SPACE, tokens::NEW_LINE, tokens::TAB,
                             tokens::LEFT_ANGLE_BRACKET});

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Struct identifier is: " << *_identifier
            << std::endl;
#endif

  int template_type_begin = identifier_begin + _identifier->size();
  template_type_begin = ignore_white_space(chs, template_type_begin);

  int template_type_end = template_type_begin;
  if (is_same(chs, template_type_begin, tokens::LEFT_ANGLE_BRACKET)) {
    template_type_begin = ignore_white_space(chs, ++template_type_begin);
    while (is_not_same(chs, template_type_begin, tokens::RIGHT_ANGLE_BRACKET)) {
      template_type_begin = ignore_white_space(chs, template_type_begin);
      std::string *generic_type_name =
          find_sequences_before(chs, template_type_begin,
                                {tokens::COMMA, tokens::RIGHT_ANGLE_BRACKET});
#ifdef DEBUG
      llvm::outs() << "[Marmotc Parser] Struct template, type name is: "
                   << *generic_type_name << "\n";
#endif
      _generic_type_names.push_back(generic_type_name);
      template_type_begin = template_type_begin + generic_type_name->length();
      template_type_begin = ignore_white_space(chs, template_type_begin);

      if (is_not_in(chs, template_type_begin,
                    {tokens::RIGHT_ANGLE_BRACKET, tokens::COMMA})) {
        throw new syntax_except(chs, template_type_begin);
      }

      if (is_same(chs, template_type_begin, tokens::COMMA)) {
        template_type_begin++;
      }
    }
    template_type_end = ++template_type_begin;
  }

  int body_begin = ignore_white_space(chs, template_type_end);
  if (is_not_in(chs, body_begin, {tokens::LEFT_BRACE})) {
    throw new syntax_except(chs, body_begin);
  }

  int attr_begin = ignore_white_space(chs, ++body_begin);
  while (is_not_in(chs, attr_begin, {tokens::RIGHT_BRACE})) {
    // parse struct's attribute
    attr_begin = ignore_white_space(chs, attr_begin);
    declare_variable_expr *attr_expr =
        new declare_variable_expr(chs, attr_begin);

    attr_expr->add_end_token(tokens::SEMICOLON);
    attr_expr->parse();
    attr_begin = attr_expr->getCurr();
    attr_begin = ignore_white_space(chs, attr_begin);

    _attrs.push_back(attr_expr);

    if (is_not_in(chs, attr_begin, {tokens::SEMICOLON})) {
      throw syntax_except(chs, attr_begin);
    }

    attr_begin = ignore_white_space(chs, ++attr_begin);
  }

  curr = attr_begin;
}

std::string *struct_expr::identifier() { return _identifier; }
std::vector<declare_variable_expr *> struct_expr::attrs() { return _attrs; }

void struct_expr::print() {
  llvm::outs() << "[Marmot AST] (Struct) identifier: " << *_identifier << "\n";

  for (declare_variable_expr *attr : _attrs) {
    attr->print();
  }
}

std::string struct_expr::generic_type_list_key(std::vector<type_expr *> types) {
  std::string result = "";
  result.append(*_identifier);
  if (!types.empty()) {
    result.append("<");
    result.append(types[0]->generic_type_list_key());
    for (int i = 1; i < types.size(); i++) {
      result.append(",");
      result.append(types[i]->generic_type_list_key());
    }

    result.append(">");
  }
  return result;
}

struct_expr *struct_expr::generate_concrete(std::vector<type_expr *> types,
                                            int id) {
  if (_generic_type_names.size() != types.size()) {
    llvm::outs() << "Generic type name size is not equals to types size\n";
    exit(1);
  }

  struct_expr *stru_expr = new struct_expr(chs, curr);
  std::string *identifier = new std::string();

  identifier->append(*_identifier);
  identifier->append(".");
  identifier->append(std::to_string(id));
  stru_expr->_identifier = identifier;

  std::unordered_map<std::string, type_expr *> type_map;
  for (int i = 0; i < types.size(); i++) {
    type_map.insert(std::make_pair(*_generic_type_names[i], types[i]));
  }

  for (declare_variable_expr *attr : _attrs) {
    stru_expr->_attrs.push_back(attr->generate_concrete(type_map));
  }

  return stru_expr;
}

std::vector<type_expr *> struct_expr::all_concrete_struct_attr_type() {
  std::vector<type_expr *> types;
  for (declare_variable_expr *attr : _attrs) {
    if (attr->is_generic() && attr->is_concrete(_generic_type_names)) {
      types.push_back(attr->var_type());
    }
  }
  return types;
}