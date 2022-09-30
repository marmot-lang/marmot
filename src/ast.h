#pragma once

#include <vector>

#include "func_expr.h"
#include "static_expr.h"
#include "struct_expr.h"

using namespace std;

namespace marmot {
class ast {
private:
  vector<char> *chs;
  vector<struct_expr *> *structs;
  vector<static_expr *> *statics;
  vector<func_expr *> *funcs;
  inline bool is_same(vector<char> *chs, int i, char c) {
    return i < chs->size() && (*chs)[i] == c;
  }

public:
  ast();
  ~ast();
  void append(char c);
  void parse();
  void toIR();
};
} // namespace marmot