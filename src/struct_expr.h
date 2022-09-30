#pragma once

#include <string>

#include "syntax_expr.h"

using namespace std;

namespace marmot {
class struct_expr : public syntax_expr {
private:
  string name;
  vector<string> generic_types;
  vector<tuple<string, vector<string>, string>> attrs;

public:
  struct_expr() = delete;
  struct_expr(const struct_expr &expr) = delete;
  struct_expr &operator=(const struct_expr &expr) = delete;
  struct_expr(vector<char> *chs, int curr);
  void parse();
};
} // namespace marmot