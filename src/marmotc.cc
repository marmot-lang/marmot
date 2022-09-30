#include <iostream>

#include "compiler.h"
#include "version.h"

using namespace marmot;

int main(int argc, char *argv[]) {
  version::print();

  for (int i = 1; i < argc; i++) {
    compiler::compile(argv[i]);
  }

  return 0;
}