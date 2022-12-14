#ifndef __MARMOT_TOKENS_H__
#define __MARMOT_TOKENS_H__

#include "Header.h"

namespace marmot {
namespace tokens {
static std::string FUNC = "func";
static std::string IMPORT = "import";
static std::string NAMESPACE = "namespace";
static std::string STRUCT = "struct";
static std::string NULL_REF = "null";
static std::string VOID = "void";
static std::string NEW = "new";
static std::string MATCH = "match";
static std::string CONST = "const";
static std::string STATIC = "static";
static std::string WHILE = "while";
static std::string IF = "if";
static std::string DELETE = "delete";
static std::string RET = "ret";

static std::string BOOL = "bool";
static std::string INT8 = "i8";
static std::string U_INT8 = "u8";
static std::string INT16 = "i16";
static std::string U_INT16 = "u16";
static std::string INT32 = "i32";
static std::string U_INT32 = "u32";
static std::string INT64 = "i64";
static std::string U_INT64 = "u64";
static std::string INT128 = "i128";
static std::string U_INT128 = "u128";

static std::string AND = "&&";
static std::string OR = "||";
static std::string DOUBLE_COLON = "::";
static std::string ARROW = "->";

static char DOT = '.';
static char COMMA = ',';
static char SEMICOLON = ';';
static char LEFT_ANGLE_BRACKET = '<';
static char RIGHT_ANGLE_BRACKET = '>';
static char UNDERSCORE = '_';
static char COLON = ':';
static char LEFT_BRACE = '{';
static char RIGHT_BRACE = '}';
static char LEFT_PARENTHESIS = '(';
static char RIGHT_PARENTHESIS = ')';
static char LEFT_SQUARE_BRACKET = '[';
static char RIGHT_SQUARE_BRACKET = ']';
static char NOT = '!';
static char SPACE = ' ';
static char NEW_LINE = '\n';
static char TAB = '\t';

static std::initializer_list<char> WRITE_SPACE = {SPACE, NEW_LINE, TAB};
} // namespace tokens
} // namespace marmot

#endif