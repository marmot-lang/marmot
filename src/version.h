#ifndef __MARMOT_VERSION_H__
#define __MARMOT_VERSION_H__

#include <iostream>
#include <string>

using namespace std;

namespace marmot {
static string VERSION = "2020.0.0-alpha";

class version {
public:
  static void print();
};
} // namespace marmot

#endif