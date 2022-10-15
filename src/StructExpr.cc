#include "StructExpr.h"
#include "SyntaxExcept.h"
#include "Tokens.h"
#include "TypeExpr.h"
#include "Utils.h"
#include <llvm-10/llvm/Support/raw_ostream.h>
#include <string>
#include <unordered_map>
#include <utility>

using namespace marmot;

StructExpr::StructExpr(std::string &chs, int curr)
    : SyntaxExpr::SyntaxExpr(chs, curr), _identifier(nullptr) {}

void StructExpr::parse() {
  // parse struct identifier
  int identifier_begin = ignoreWhiteSpace(chs, curr);
  _identifier = findSequencesBefore(chs, identifier_begin,
                                    {tokens::SPACE, tokens::NEW_LINE,
                                     tokens::TAB, tokens::LEFT_ANGLE_BRACKET});

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Struct identifier is: " << *_identifier
            << std::endl;
#endif

  int template_type_begin = identifier_begin + _identifier->size();
  template_type_begin = ignoreWhiteSpace(chs, template_type_begin);

  int template_type_end = template_type_begin;
  if (isSame(chs, template_type_begin, tokens::LEFT_ANGLE_BRACKET)) {
    template_type_begin = ignoreWhiteSpace(chs, ++template_type_begin);
    while (isNotSame(chs, template_type_begin, tokens::RIGHT_ANGLE_BRACKET)) {
      template_type_begin = ignoreWhiteSpace(chs, template_type_begin);
      std::string *generic_type_name =
          findSequencesBefore(chs, template_type_begin,
                              {tokens::COMMA, tokens::RIGHT_ANGLE_BRACKET});
#ifdef DEBUG
      llvm::outs() << "[Marmotc Parser] Struct template, type name is: "
                   << *generic_type_name << "\n";
#endif
      _generic_type_names.push_back(generic_type_name);
      template_type_begin = template_type_begin + generic_type_name->length();
      template_type_begin = ignoreWhiteSpace(chs, template_type_begin);

      if (isNotIn(chs, template_type_begin,
                  {tokens::RIGHT_ANGLE_BRACKET, tokens::COMMA})) {
        throw new SyntaxExcept(chs, template_type_begin);
      }

      if (isSame(chs, template_type_begin, tokens::COMMA)) {
        template_type_begin++;
      }
    }
    template_type_end = ++template_type_begin;
  }

  int body_begin = ignoreWhiteSpace(chs, template_type_end);
  if (isNotIn(chs, body_begin, {tokens::LEFT_BRACE})) {
    throw new SyntaxExcept(chs, body_begin);
  }

  int attr_begin = ignoreWhiteSpace(chs, ++body_begin);
  while (isNotIn(chs, attr_begin, {tokens::RIGHT_BRACE})) {
    // parse struct's attribute
    attr_begin = ignoreWhiteSpace(chs, attr_begin);
    DeclareVariableExpr *attr_expr = new DeclareVariableExpr(chs, attr_begin);

    attr_expr->add_end_token(tokens::SEMICOLON);
    attr_expr->parse();
    attr_begin = attr_expr->getCurr();
    attr_begin = ignoreWhiteSpace(chs, attr_begin);

    _attrs.push_back(attr_expr);

    if (isNotIn(chs, attr_begin, {tokens::SEMICOLON})) {
      throw SyntaxExcept(chs, attr_begin);
    }

    attr_begin = ignoreWhiteSpace(chs, ++attr_begin);
  }

  curr = attr_begin;
}

std::string *StructExpr::identifier() { return _identifier; }
std::vector<DeclareVariableExpr *> StructExpr::attrs() { return _attrs; }

void StructExpr::print() {
  llvm::outs() << "[Marmot AST] (Struct) identifier: " << *_identifier << "\n";

  for (DeclareVariableExpr *attr : _attrs) {
    attr->print();
  }
}

std::string StructExpr::generic_type_list_key(std::vector<TypeExpr *> types) {
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

StructExpr *StructExpr::generate_concrete(std::vector<TypeExpr *> types,
                                          int id) {
  if (_generic_type_names.size() != types.size()) {
    llvm::outs() << "Generic type name size is not equals to types size\n";
    exit(1);
  }

  StructExpr *stru_expr = new StructExpr(chs, curr);
  std::string *identifier = new std::string();

  identifier->append(*_identifier);
  identifier->append(".");
  identifier->append(std::to_string(id));
  stru_expr->_identifier = identifier;

  std::unordered_map<std::string, TypeExpr *> type_map;
  for (int i = 0; i < types.size(); i++) {
    type_map.insert(std::make_pair(*_generic_type_names[i], types[i]));
  }

  for (DeclareVariableExpr *attr : _attrs) {
    stru_expr->_attrs.push_back(attr->generate_concrete(type_map));
  }

  return stru_expr;
}

std::vector<TypeExpr *> StructExpr::all_concrete_struct_attr_type() {
  std::vector<TypeExpr *> types;
  for (DeclareVariableExpr *attr : _attrs) {
    if (attr->is_generic() && attr->is_concrete(_generic_type_names)) {
      types.push_back(attr->var_type());
    }
  }
  return types;
}