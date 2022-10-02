#include "declare_variable_expr.h"
#include "utils.h"
#include <llvm-10/llvm/Support/raw_ostream.h>

using namespace marmot;

declare_variable_expr::declare_variable_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr) {
  _end_tokens.insert(tokens::SPACE);
  _end_tokens.insert(tokens::NEW_LINE);
  _end_tokens.insert(tokens::TAB);
}

void declare_variable_expr::parse() {
  _var_type = new type_expr(chs, curr);
  _var_type->parse();
  int type_end = _var_type->getCurr();
  int identifier_begin = ignore_white_space(chs, type_end);
  _var_identifier = find_sequences_before(chs, identifier_begin, _end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Variable identifier is: " << *_var_identifier
            << std::endl;
#endif

  curr = identifier_begin + _var_identifier->length();
}

void declare_variable_expr::print() {
  llvm::outs() << "[Marmot AST] (Struct Attribute) identifier: "
               << *_var_identifier << ", type: ";

  _var_type->print();
  llvm::outs() << "\n";
}

declare_variable_expr *declare_variable_expr::generate_concrete(
    std::unordered_map<std::string, type_expr *> &type_map) {
  declare_variable_expr *expr = new declare_variable_expr(chs, curr);
  expr->_var_identifier = _var_identifier;
  expr->_var_type = _var_type->generate_concrete(type_map);
  return expr;
}

bool declare_variable_expr::is_concrete(
    std::vector<std::string *> generic_type_names) {
  if (generic_type_names.empty())
    return true;
  return _var_type->is_concrete(generic_type_names);
}