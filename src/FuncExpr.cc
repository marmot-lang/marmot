#include "FuncExpr.h"
#include "SyntaxExcept.h"
#include "SyntaxExpr.h"
#include "Tokens.h"
#include "TypeExpr.h"
#include "Utils.h"

using namespace marmot;

FuncExpr::FuncExpr(std::string &chs, int curr) : SyntaxExpr(chs, curr) {}

void FuncExpr::parse() {
  int identifier_begin = ignoreWhiteSpace(chs, curr);

  std::initializer_list<char> end_tokens = {
      tokens::SPACE, tokens::NEW_LINE, tokens::TAB, tokens::LEFT_SQUARE_BRACKET,
      tokens::LEFT_PARENTHESIS};
  _identifier = findSequencesBefore(chs, identifier_begin, end_tokens);

#ifdef DEBUG
  std::cout << "[Marmotc Parser] Parse function, identifier: " << *_identifier
            << std::endl;
#endif

  int call_site_begin = identifier_begin + _identifier->length();
  call_site_begin = ignoreWhiteSpace(chs, call_site_begin);
  int params_begin = call_site_begin;
  if (isSame(chs, call_site_begin, tokens::LEFT_SQUARE_BRACKET)) {
    _call_site = new TypeExpr(chs, ++call_site_begin);
    _call_site->add_end_token(tokens::RIGHT_SQUARE_BRACKET);
    _call_site->parse();

    int call_site_end = _call_site->getCurr();
    call_site_end = ignoreWhiteSpace(chs, call_site_end);

    if (isNotSame(chs, call_site_end, tokens::RIGHT_SQUARE_BRACKET)) {
      throw new SyntaxExcept(chs, call_site_end);
    }

    params_begin = ++call_site_end;
  }

  if (isSame(chs, params_begin, tokens::LEFT_PARENTHESIS)) {
    params_begin = ignoreWhiteSpace(chs, ++params_begin);

    while (isNotSame(chs, params_begin, tokens::RIGHT_PARENTHESIS)) {
      params_begin = ignoreWhiteSpace(chs, params_begin);
      DeclareVariableExpr *param = new DeclareVariableExpr(chs, params_begin);
      param->add_end_token(tokens::COMMA);
      param->add_end_token(tokens::RIGHT_PARENTHESIS);
      param->parse();
      params_begin = param->getCurr();
      params_begin = ignoreWhiteSpace(chs, params_begin);
      if (isSame(chs, params_begin, tokens::COMMA)) {
        params_begin++;
      } else if (isSame(chs, params_begin, tokens::RIGHT_PARENTHESIS)) {
        params_begin++;
        break;
      } else {
        throw new SyntaxExcept(chs, params_begin);
      }
    }
  }

  int ret_begin = ignoreWhiteSpace(chs, params_begin);
  int body_begin = ret_begin;
  if (isSame(chs, ret_begin, tokens::COLON)) {
    ret_begin = ignoreWhiteSpace(chs, ++ret_begin);
    _ret_type = new TypeExpr(chs, ret_begin);
    _ret_type->add_end_token(tokens::LEFT_BRACE);
    _ret_type->parse();
    body_begin = _ret_type->getCurr();
  }

  body_begin = ignoreWhiteSpace(chs, body_begin);
  int body_end = body_begin;
  if (isSame(chs, body_begin, tokens::LEFT_BRACE)) {
    // parse intrument
    body_end = ignoreWhiteSpace(chs, ++body_begin);
  } else {
    throw new SyntaxExcept(chs, body_begin);
  }

  if (isNotSame(chs, body_end, tokens::RIGHT_BRACE)) {
    throw new SyntaxExcept(chs, body_end);
  }

  curr = body_end;
}

void FuncExpr::print() {}