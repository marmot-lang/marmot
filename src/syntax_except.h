#pragma once

#include <vector>

using namespace std;

namespace marmot {
class syntax_except {
public:
  syntax_except() = delete;
  syntax_except(const syntax_except &expr) = delete;
  syntax_except &operator=(const syntax_except &expr) = delete;
  syntax_except(vector<char> *chs, int cur);
};
} // namespace marmot