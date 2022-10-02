#ifndef __MARMOT_TOKENS_H__
#define __MARMOT_TOKENS_H__

#include <initializer_list>
#include <string>

using namespace std;

namespace marmot {
namespace tokens {

static string FUNC = "func";
static string IMPORT = "import";
static string NAMESPACE = "namespace";
static string STRUCT = "struct";
static string NULL_REF = "null";
static string VOID = "void";
static string NEW = "new";
static string MATCH = "match";
static string CONST = "const";
static string STATIC = "static";
static string WHILE = "while";
static string IF = "if";
static string DELETE = "delete";
static string RET = "ret";

static string BOOL = "bool";
static string INT8 = "int8";
static string U_INT8 = "u_int8";
static string INT16 = "int16";
static string U_INT16 = "u_int16";
static string INT32 = "int32";
static string U_INT32 = "u_int32";
static string INT64 = "int64";
static string U_INT64 = "u_int64";
static string INT128 = "int128";
static string U_INT128 = "u_int128";

static string AND = "&&";
static string OR = "||";
static string DOUBLE_COLON = "::";
static string ARROW = "->";

static char DOT = '.';
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

static initializer_list<char> WRITE_SPACE = {SPACE, NEW_LINE, TAB};
} // namespace tokens
} // namespace marmot

#endif