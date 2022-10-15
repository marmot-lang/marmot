#include "DeclareVariableExpr.h"
#include "Utils.h"
#include <llvm-10/llvm/Support/raw_ostream.h>

using namespace marmot;

DeclareVariableExpr::DeclareVariableExpr(std::string &chs, int curr)
    : SyntaxExpr::SyntaxExpr(chs, curr) {
  _end_tokens.insert(tokens::SPACE);
  _end_tokens.insert(tokens::NEW_LINE);
  _end_tokens.insert(tokens::TAB);
}

void DeclareVariableExpr::parse() {
  _var_type = new TypeExpr(chs, curr);
  _var_type->parse();
  int type_end = _var_type->getCurr();
  int identifier_begin = ignoreWhiteSpace(chs, type_end);
  _var_identifier = findSequencesBefore(chs, identifier_begin, _end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Variable identifier is: " << *_var_identifier
            << std::endl;
#endif

  curr = identifier_begin + _var_identifier->length();
}

void DeclareVariableExpr::print() {
  llvm::outs() << "[Marmot AST] (Struct Attribute) identifier: "
               << *_var_identifier << ", type: ";

  _var_type->print();
  llvm::outs() << "\n";
}

DeclareVariableExpr *DeclareVariableExpr::generate_concrete(
    std::unordered_map<std::string, TypeExpr *> &type_map) {
  DeclareVariableExpr *expr = new DeclareVariableExpr(chs, curr);
  expr->_var_identifier = _var_identifier;
  expr->_var_type = _var_type->generate_concrete(type_map);
  return expr;
}

bool DeclareVariableExpr::is_concrete(
    std::vector<std::string *> generic_type_names) {
  if (generic_type_names.empty())
    return true;
  return _var_type->is_concrete(generic_type_names);
}