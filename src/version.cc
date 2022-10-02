#include "version.h"
#include <llvm-10/llvm/Support/raw_ostream.h>

using namespace marmot;

void version::print() {
  llvm::outs().changeColor(llvm::raw_ostream::MAGENTA, true);
  llvm::outs() << "Marmot Programming Language Compiler"
               << "\n";
  llvm::outs().resetColor();
  llvm::outs() << "Language Version: ";
  llvm::outs().changeColor(llvm::raw_ostream::YELLOW);
  llvm::outs() << MARMOT_LANG_VERSION << "\n";
  llvm::outs().resetColor();
  llvm::outs() << "Compiler Version: ";
  llvm::outs().changeColor(llvm::raw_ostream::YELLOW);
  llvm::outs() << COMPILER_VERSION << "\n";
  llvm::outs().resetColor();
  llvm::outs() << "Author: ";
  llvm::outs() << AUTHOR << "\n";
  llvm::outs() << "E-Mail: ";
  llvm::outs() << EMAIL << "\n\n";
}