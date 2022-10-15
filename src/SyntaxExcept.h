#ifndef __MARMOT_SYNTAX_EXCEPT_H__
#define __MARMOT_SYNTAX_EXCEPT_H__

#include "Header.h"

namespace marmot {
class SyntaxExcept {
private:
  int curr;
  std::string &chs;

public:
  SyntaxExcept() = delete;
  SyntaxExcept(const SyntaxExcept &expr) = delete;
  SyntaxExcept &operator=(const SyntaxExcept &expr) = delete;
  SyntaxExcept(std::string &chs, int curr);
  std::string *message();
};
} // namespace marmot

#endif