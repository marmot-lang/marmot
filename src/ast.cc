#include "ast.h"
#include "syntax_except.h"
#include "utils.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <llvm-10/llvm/Support/raw_ostream.h>
#include <string>
#include <utility>
#include <vector>

using namespace marmot;

ast::ast(std::filesystem::path &abs_path) {
  _filename = abs_path.filename().string();
  _llvm_ir_os = new llvm::raw_fd_ostream("build.ll", _ec);
}

void ast::to_llvm_ir() {
  llvm_ir_uitls *ir_uitls = new llvm_ir_uitls();

  llvm::LLVMContext context;
  llvm::IRBuilder<> builder(context);
  llvm::Module *module = new llvm::Module(_filename, context);

  for (struct_expr *stru_expr : _structs) {
    std::string *identifier = stru_expr->identifier();

    llvm::StructType *ir_struct_type =
        llvm::StructType::create(context, *(stru_expr->identifier()));

    _point_type_map.insert(std::make_pair(
        *identifier, llvm::PointerType::getUnqual(ir_struct_type)));

#ifdef DEBUG
    std::cout << "[Marmotc Generator] Generate IR struct, identifier is: "
              << *identifier << std::endl;
#endif

    std::vector<declare_variable_expr *> attrs = stru_expr->attrs();
    int len = attrs.size();

    std::vector<llvm::Type *> *attr_types = new std::vector<llvm::Type *>();
    for (declare_variable_expr *stru_attr : attrs) {
      std::string *type_identifier = stru_attr->var_type()->identifier();

#ifdef DEBUG
      std::cout << "[Marmotc Generator] Generate IR struct body, type is: "
                << *type_identifier << std::endl;
#endif

      llvm::Type *attr_type =
          ir_uitls->find_raw_type(*type_identifier, builder);
      if (attr_type != nullptr) {
        attr_types->push_back(attr_type);
        continue;
      }

      if (stru_attr->is_generic()) {
        std::string stru_attr_type_name =
            *(stru_attr->var_type()->identifier());

        std::string generic_type_list_key = stru_attr->generic_type_list_key();
        std::unordered_map<std::string, std::unordered_map<std::string, int>
                                            *>::iterator id_map_itr =
            _generic_structs_id_map.find(stru_attr_type_name);

        std::unordered_map<std::string, int>::iterator id_itr =
            id_map_itr->second->find(generic_type_list_key);

        int id = id_itr->second;
        std::string struct_type_key;
        struct_type_key.append(stru_attr_type_name);
        struct_type_key.append(".");
        struct_type_key.append(std::to_string(id));

        std::unordered_map<std::string, llvm::PointerType *>::iterator
            point_itr = _point_type_map.find(struct_type_key);

        if (point_itr._M_cur == nullptr) {
          llvm::StructType *generic_struct_type =
              llvm::StructType::create(context, struct_type_key);

          _point_type_map.insert(std::make_pair(
              struct_type_key,
              llvm::PointerType::getUnqual(generic_struct_type)));

          attr_types->push_back(generic_struct_type);
          continue;
        }

        attr_types->push_back(point_itr->second);
        continue;
      }

      std::unordered_map<std::string, llvm::PointerType *>::iterator
          attr_type_itr = _point_type_map.find(*type_identifier);

      if (attr_type_itr._M_cur != nullptr) {
        attr_types->push_back(attr_type_itr->second);
        continue;
      }

      std::cout << "Not found type: " << *type_identifier << std::endl;
      exit(1);
    }

    llvm::ArrayRef<llvm::Type *> *attr_types_ref =
        new llvm::ArrayRef<llvm::Type *>(*attr_types);
    ir_struct_type->setBody(*attr_types_ref);
    module->getOrInsertGlobal(*identifier, ir_struct_type);
  }

  module->print(*_llvm_ir_os, nullptr);
}

void ast::print() {
  for (struct_expr *stru_expr : _structs) {
    stru_expr->print();
  }
}

void ast::add_concrete_struct(std::string &name,
                              std::vector<type_expr *> types) {
  std::unordered_map<std::string,
                     std::unordered_map<std::string, int> *>::iterator itr =
      _generic_structs_id_map.find(name);

  int id;
  std::unordered_map<std::string, struct_expr *>::iterator generic_struct_itr =
      _generic_structs.find(name);
  struct_expr *generic_struct = generic_struct_itr->second;

  std::string generic_type_list_key =
      generic_struct->generic_type_list_key(types);

  if (itr._M_cur != nullptr) {
    std::unordered_map<std::string, int> *id_map = itr->second;

    std::unordered_map<std::string, int>::iterator id_itr =
        id_map->find(generic_type_list_key);
    if (id_itr._M_cur == nullptr) {
      id = id_map->size();
      id_map->insert(std::make_pair(generic_type_list_key, id));

      struct_expr *concrete = generic_struct->generate_concrete(types, id);
      _structs.push_back(concrete);
#ifdef DEBUG
      llvm::outs() << "[Marmot AST] Concrete struct: "
                   << *(concrete->identifier()) << "\n";
      concrete->print();
#endif
    } else {
      id = id_itr->second;
    }
  } else {
    std::unordered_map<std::string, int> *id_map =
        new std::unordered_map<std::string, int>();
    _generic_structs_id_map.insert(std::make_pair(name, id_map));

    id = id_map->size();
    id_map->insert(std::make_pair(generic_type_list_key, id));

    struct_expr *concrete = generic_struct->generate_concrete(types, id);
    _structs.push_back(concrete);

#ifdef DEBUG
    llvm::outs() << "[Marmot AST] First concrete struct: "
                 << *(concrete->identifier()) << "\n";
    concrete->print();
#endif
  }
}

void ast::add_concrete_struct_if_not_exist(struct_expr *expr) {
  std::vector<type_expr *> types = expr->all_concrete_struct_attr_type();

  for (type_expr *type : types) {
    add_concrete_struct(*(type->identifier()), type->type_names());

#ifdef DEBUG
    llvm::outs() << "[Marmots Parser] (Struct) find concrete struct: ";
    llvm::outs() << type->generic_type_list_key() << "\n";
#endif
  }
}