#ifndef __MARMOT_FUNC_EXPR_H__
#define __MARMOT_FUNC_EXPR_H__

#include "declare_variable_expr.h"
#include "header.h"
#include "syntax_expr.h"
#include "type_expr.h"

namespace marmot {
class func_expr : public syntax_expr {
private:
  std::string *_identifier;
  type_expr *_call_site;
  std::vector<declare_variable_expr *> *_params;
  type_expr *_ret_type;

public:
  func_expr() = delete;
  func_expr(const func_expr &expr) = delete;
  func_expr &operator=(const func_expr &expr) = delete;
  func_expr(std::string &chs, int curr);
  void parse();
  void print();
};
} // namespace marmot

#endif