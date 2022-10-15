#ifndef __MARMOT_TYPE_EXPR_H__
#define __MARMOT_TYPE_EXPR_H__

#include "Header.h"
#include "SyntaxExpr.h"

namespace marmot {
class TypeExpr : public SyntaxExpr {
private:
  std::string *_identifier;
  std::vector<TypeExpr *> _type_names;

public:
  TypeExpr();
  TypeExpr(const TypeExpr &expr) = delete;
  TypeExpr &operator=(const TypeExpr &expr) = delete;
  TypeExpr(std::string &chs, int curr);

  void parse();
  void print();
  std::string generic_type_list_key();
  bool is_concrete(std::vector<std::string *> generic_type_names);
  TypeExpr *
  generate_concrete(std::unordered_map<std::string, TypeExpr *> &type_map);

  inline std::string *identifier() { return _identifier; }
  inline std::vector<TypeExpr *> type_names() { return _type_names; }
  inline bool is_generic() { return !_type_names.empty(); }
};
} // namespace marmot

#endif