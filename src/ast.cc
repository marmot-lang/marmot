#include "ast.h"
#include "syntax_except.h"
#include "utils.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <llvm-10/llvm/IR/Type.h>
#include <llvm-10/llvm/Support/raw_ostream.h>
#include <ostream>
#include <string>

using namespace marmot;

ast::ast(std::filesystem::path &abs_path)
    : _structs(new std::vector<struct_expr *>()),
      _statics(new std::vector<static_expr *>()) {

  _filename = abs_path.filename().string();
  _llvm_ir_os = new llvm::raw_fd_ostream("build.ll", _ec);
}

ast::~ast() {
  delete _structs;
  delete _statics;
}

void ast::add_struct_expr(struct_expr *expr) { _structs->push_back(expr); }
void ast::add_static_expr(static_expr *expr) { _statics->push_back(expr); }
void ast::add_func_expr(func_expr *expr) { _funcs->push_back(expr); }

void ast::to_llvm_ir() {
  llvm_ir_uitls *ir_uitls = new llvm_ir_uitls();

  llvm::LLVMContext context;
  llvm::IRBuilder<> builder(context);
  llvm::Module *module = new llvm::Module(_filename, context);

  for (struct_expr *stru_expr : *_structs) {
    std::string *identifier = stru_expr->identifier();

    llvm::StructType *ir_struct_type =
        llvm::StructType::create(context, *(stru_expr->identifier()));

#ifdef DEBUG
    std::cout << "[Marmotc Generator] Generate IR struct, identifier is: "
              << *identifier << std::endl;
#endif

    std::vector<struct_attr *> *attrs = stru_expr->attrs();
    int len = attrs->size();

    std::vector<llvm::Type *> *attr_types = new std::vector<llvm::Type *>();
    for (struct_attr *stru_attr : *attrs) {
      std::string *type_identifier = stru_attr->attr_type()->identifier();

#ifdef DEBUG
      std::cout << "[Marmotc Generator] Generate IR struct body, type is: "
                << *type_identifier << std::endl;
#endif

      llvm::Type *int_type = ir_uitls->find_type(*type_identifier, builder);
      attr_types->push_back(int_type);
    }

    llvm::ArrayRef<llvm::Type *> *attr_types_ref =
        new llvm::ArrayRef<llvm::Type *>(*attr_types);
    ir_struct_type->setBody(*attr_types_ref);
    module->getOrInsertGlobal(*identifier, ir_struct_type);
  }

  module->print(*_llvm_ir_os, nullptr);
}

void ast::print() {
  for (struct_expr *stru_expr : *_structs) {
    stru_expr->print();
  }
}