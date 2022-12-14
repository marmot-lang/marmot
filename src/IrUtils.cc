#include "IrUtils.h"
#include "Tokens.h"
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <unordered_map>
#include <utility>

using namespace marmot;

IrUitls::IrUitls() {
  int_types.insert(std::make_pair(tokens::INT8, _build_int8));
  int_types.insert(std::make_pair(tokens::INT16, _build_int16));
  int_types.insert(std::make_pair(tokens::INT32, _build_int32));
  int_types.insert(std::make_pair(tokens::INT64, _build_int64));
  int_types.insert(std::make_pair(tokens::INT128, _build_int128));
  int_types.insert(std::make_pair(tokens::U_INT8, _build_int8));
  int_types.insert(std::make_pair(tokens::U_INT16, _build_int16));
  int_types.insert(std::make_pair(tokens::U_INT32, _build_int32));
  int_types.insert(std::make_pair(tokens::U_INT64, _build_int64));
  int_types.insert(std::make_pair(tokens::U_INT128, _build_int128));
}

llvm::Type *IrUitls::find_raw_type(std::string &type_name,
                                   llvm::IRBuilder<> &builder) {
  std::unordered_map<std::string,
                     std::function<llvm::Type *(llvm::IRBuilder<> &)>>::iterator
      itr = int_types.find(type_name);

  if (itr._M_cur != nullptr) {
    return itr->second(builder);
  }
  return nullptr;
}