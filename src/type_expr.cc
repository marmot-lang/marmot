#include "type_expr.h"
#include "tokens.h"
#include "utils.h"

using namespace marmot;

type_expr::type_expr(std::string &chs, int curr)
    : syntax_expr::syntax_expr(chs, curr), _identify(nullptr),
      type_names(new std::vector<std::string *>()) {}

void type_expr::parse() {
  initializer_list<char> end_tokens = {
      tokens::LEFT_ANGLE_BRACKET, tokens::SPACE, tokens::NEW_LINE, tokens::TAB};
  _identify = find_sequences_before(chs, curr, end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc] Type is: " << *_identify << std::endl;
#endif

  int identify_end = curr + _identify->size();
  int type_names_begin = ignore_white_space(chs, identify_end);
  int type_names_end = type_names_begin;

  if (is_in(chs, type_names_begin, {tokens::LEFT_ANGLE_BRACKET})) {
    // parse type names
  }

  curr = type_names_end;
}