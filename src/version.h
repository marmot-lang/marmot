#pragma once

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