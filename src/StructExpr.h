#ifndef __MARMOT_STRUCT_EXPR_H__
#define __MARMOT_STRUCT_EXPR_H__

#include "DeclareVariableExpr.h"
#include "SyntaxExpr.h"
#include "TypeExpr.h"

namespace marmot {

class StructAttr;

class StructExpr : public SyntaxExpr {
private:
  std::string *_identifier;
  std::vector<std::string *> _generic_type_names;
  std::vector<DeclareVariableExpr *> _attrs;

public:
  StructExpr(const StructExpr &expr) = delete;
  StructExpr &operator=(const StructExpr &expr) = delete;
  StructExpr(std::string &chs, int curr);
  void parse();
  std::string *identifier();
  std::vector<DeclareVariableExpr *> attrs();

  void print();
  std::string generic_type_list_key(std::vector<TypeExpr *> types);
  StructExpr *generate_concrete(std::vector<TypeExpr *> types, int id);
  std::vector<TypeExpr *> all_concrete_struct_attr_type();

  inline bool is_struct_template() { return !_generic_type_names.empty(); }
};
} // namespace marmot

#endif