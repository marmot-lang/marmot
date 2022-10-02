#ifndef __MARMOT_VERSION_H__
#define __MARMOT_VERSION_H__

#include "header.h"

namespace marmot {
static std::string MARMOT_LANG_VERSION = "0.0.1";
static std::string COMPILER_VERSION = "2020.0.0-alpha";
static std::string AUTHOR = "Baili Zhang";
static std::string EMAIL = "1456938262@qq.com";

class version {
public:
  static void print();
};
} // namespace marmot

#endif