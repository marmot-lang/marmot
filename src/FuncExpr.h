#ifndef __MARMOT_FUNC_EXPR_H__
#define __MARMOT_FUNC_EXPR_H__

#include "DeclareVariableExpr.h"
#include "Header.h"
#include "SyntaxExpr.h"
#include "TypeExpr.h"

namespace marmot {
class FuncExpr : public SyntaxExpr {
private:
  std::string *_identifier;
  TypeExpr *_call_site;
  std::vector<DeclareVariableExpr *> *_params;
  TypeExpr *_ret_type;

public:
  FuncExpr() = delete;
  FuncExpr(const FuncExpr &expr) = delete;
  FuncExpr &operator=(const FuncExpr &expr) = delete;
  FuncExpr(std::string &chs, int curr);
  void parse();
  void print();
};
} // namespace marmot

#endif