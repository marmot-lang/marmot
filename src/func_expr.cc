#include "func_expr.h"
#include "syntax_except.h"
#include "syntax_expr.h"
#include "tokens.h"
#include "type_expr.h"
#include "utils.h"

using namespace marmot;

func_expr::func_expr(std::string &chs, int curr) : syntax_expr(chs, curr) {}

void func_expr::parse() {
  int identifier_begin = ignore_white_space(chs, curr);

  std::initializer_list<char> end_tokens = {
      tokens::SPACE, tokens::NEW_LINE, tokens::TAB, tokens::LEFT_SQUARE_BRACKET,
      tokens::LEFT_PARENTHESIS};
  _identifier = find_sequences_before(chs, identifier_begin, end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Parse function, identifier: " << *_identifier
            << std::endl;
#endif

  int call_site_begin = identifier_begin + _identifier->length();
  call_site_begin = ignore_white_space(chs, call_site_begin);
  int params_begin = call_site_begin;
  if (is_same(chs, call_site_begin, tokens::LEFT_SQUARE_BRACKET)) {
    _call_site = new type_expr(chs, ++call_site_begin);
    _call_site->add_end_token(tokens::RIGHT_SQUARE_BRACKET);
    _call_site->parse();

    int call_site_end = _call_site->getCurr();
    call_site_end = ignore_white_space(chs, call_site_end);

    if (is_not_same(chs, call_site_end, tokens::RIGHT_SQUARE_BRACKET)) {
      throw new syntax_except(chs, call_site_end);
    }

    params_begin = ++call_site_end;
  }

  if (is_same(chs, params_begin, tokens::LEFT_PARENTHESIS)) {
    params_begin = ignore_white_space(chs, ++params_begin);

    while (is_not_same(chs, params_begin, tokens::RIGHT_PARENTHESIS)) {
      params_begin = ignore_white_space(chs, params_begin);
      declare_variable_expr *param =
          new declare_variable_expr(chs, params_begin);
      param->add_end_token(tokens::COMMA);
      param->add_end_token(tokens::RIGHT_PARENTHESIS);
      param->parse();
      params_begin = param->getCurr();
      params_begin = ignore_white_space(chs, params_begin);
      if (is_same(chs, params_begin, tokens::COMMA)) {
        params_begin++;
      } else if (is_same(chs, params_begin, tokens::RIGHT_PARENTHESIS)) {
        params_begin++;
        break;
      } else {
        throw new syntax_except(chs, params_begin);
      }
    }
  }

  int ret_begin = ignore_white_space(chs, params_begin);
  int body_begin = ret_begin;
  if (is_same(chs, ret_begin, tokens::COLON)) {
    ret_begin = ignore_white_space(chs, ++ret_begin);
    _ret_type = new type_expr(chs, ret_begin);
    _ret_type->add_end_token(tokens::LEFT_BRACE);
    _ret_type->parse();
    body_begin = _ret_type->getCurr();
  }

  body_begin = ignore_white_space(chs, body_begin);
  int body_end = body_begin;
  if (is_same(chs, body_begin, tokens::LEFT_BRACE)) {
    // parse intrument
    body_end = ignore_white_space(chs, ++body_begin);
  } else {
    throw new syntax_except(chs, body_begin);
  }

  if (is_not_same(chs, body_end, tokens::RIGHT_BRACE)) {
    throw new syntax_except(chs, body_end);
  }

  curr = body_end;
}

void func_expr::print() {}