#ifndef __MARMOT_SYNTAX_EXCEPT_H__
#define __MARMOT_SYNTAX_EXCEPT_H__

#include "header.h"

namespace marmot {
class syntax_except {
private:
  int curr;
  std::string &chs;

public:
  syntax_except() = delete;
  syntax_except(const syntax_except &expr) = delete;
  syntax_except &operator=(const syntax_except &expr) = delete;
  syntax_except(std::string &chs, int curr);
  std::string *message();
};
} // namespace marmot

#endif