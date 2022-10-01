#include "version.h"

using namespace marmot;

void version::print() {
  std::cout << "Marmot Programming Language Compiler" << std::endl;
  std::cout << "Version: " << VERSION << std::endl << std::endl;
}