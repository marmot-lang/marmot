#ifndef __MARMOT_LLVM_IR_H__
#define __MARMOT_LLVM_IR_H__

#include "header.h"

namespace marmot {

static const std::function<llvm::Type *(llvm::IRBuilder<> &)> _build_int8 =
    [](llvm::IRBuilder<> &builder) -> llvm::Type * {
  return builder.getInt8Ty();
};

static const std::function<llvm::Type *(llvm::IRBuilder<> &)> _build_int16 =
    [](llvm::IRBuilder<> &builder) -> llvm::Type * {
  return builder.getInt16Ty();
};

static const std::function<llvm::Type *(llvm::IRBuilder<> &)> _build_int32 =
    [](llvm::IRBuilder<> &builder) -> llvm::Type * {
  return builder.getInt32Ty();
};

static const std::function<llvm::Type *(llvm::IRBuilder<> &)> _build_int64 =
    [](llvm::IRBuilder<> &builder) -> llvm::Type * {
  return builder.getInt64Ty();
};

static const std::function<llvm::Type *(llvm::IRBuilder<> &)> _build_int128 =
    [](llvm::IRBuilder<> &builder) -> llvm::Type * {
  return builder.getInt128Ty();
};

class llvm_ir_uitls {
private:
  std::unordered_map<std::string,
                     std::function<llvm::Type *(llvm::IRBuilder<> &)>>
      int_types;

public:
  llvm_ir_uitls();
  llvm_ir_uitls(const llvm_ir_uitls &ir) = delete;
  llvm_ir_uitls &operator=(const llvm_ir_uitls &ir) = delete;

  llvm::Type *find_raw_type(std::string &type_name, llvm::IRBuilder<> &builder);
};
} // namespace marmot

#endif
