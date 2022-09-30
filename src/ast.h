#pragma once

#include <vector>

using namespace std;

namespace marmot {
class ast {
private:
  vector<char> *chs;

public:
  ast();
  ~ast();
  void append(char c);
  void build();
  void toIR();
};
} // namespace marmot