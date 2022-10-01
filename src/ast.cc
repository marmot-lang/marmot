#include "ast.h"
#include "syntax_except.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <iostream>
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <llvm-10/llvm/IR/Type.h>
#include <llvm-10/llvm/Support/raw_ostream.h>
#include <string>

using namespace marmot;

ast::ast(std::string &filename)
    : structs(new std::vector<struct_expr *>()),
      statics(new std::vector<static_expr *>()), filename(filename) {}

ast::~ast() {
  delete structs;
  delete statics;
}

void ast::add_struct_expr(struct_expr *expr) { structs->push_back(expr); }
void ast::add_static_expr(static_expr *expr) { statics->push_back(expr); }
void ast::add_func_expr(func_expr *expr) { funcs->push_back(expr); }

void ast::to_llvm_ir() {
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder(context);
  llvm::Module *module = new llvm::Module(filename, context);

  for (struct_expr *stru_e : *structs) {
    llvm::StructType *struct_type =
        llvm::StructType::create(context, *(stru_e->identify()));
    struct_type->setBody(builder.getInt32Ty());
    struct_type->print(llvm::outs());
  }

  module->print(llvm::outs(), nullptr);
}