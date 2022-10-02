#include "type_expr.h"
#include "tokens.h"
#include "utils.h"

using namespace marmot;

type_expr::type_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr), _identifier(nullptr),
      type_names(new std::vector<std::string *>()) {}

void type_expr::parse() {
  initializer_list<char> end_tokens = {
      tokens::LEFT_ANGLE_BRACKET, tokens::SPACE, tokens::NEW_LINE, tokens::TAB};
  _identifier = find_sequences_before(chs, curr, end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Type is: " << *_identifier << std::endl;
#endif

  int identifier_end = curr + _identifier->size();
  int type_names_begin = ignore_white_space(chs, identifier_end);
  int type_names_end = type_names_begin;

  if (is_in(chs, type_names_begin, {tokens::LEFT_ANGLE_BRACKET})) {
    // parse type names
  }

  curr = type_names_end;
}

void type_expr::print() { cout << "type: " << *_identifier; }