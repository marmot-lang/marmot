#ifndef __MARMOT_LOG_H__
#define __MARMOT_LOG_H__

#include "Header.h"

namespace marmot {
class Log {
private:
  std::string module;

public:
  void info() {
    llvm::outs().changeColor(llvm::raw_ostream::GREEN);
    llvm::outs() << "INFO";
  }
};
} // namespace marmot

#endif