#ifndef __MARMOT_UTILS_H__
#define __MARMOT_UTILS_H__

#include "Header.h"
#include "SyntaxExcept.h"
#include "Tokens.h"

namespace marmot {

bool isEnd(std::string &chs, int curr);

bool isNotEnd(std::string &chs, int curr);

bool isIn(std::string &chs, int curr, std::unordered_set<char> &cs);

bool isNotIn(std::string &chs, int curr, std::unordered_set<char> &cs);

bool isIn(std::string &chs, int curr, std::initializer_list<char> cs);

bool isNotIn(std::string &chs, int curr, std::initializer_list<char> cs);

bool isWriteSpace(std::string &chs, int curr);

int ignoreWhiteSpace(std::string &chs, int curr);

bool isNotWhiteSpace(std::string &chs, int curr);

std::string *findSequencesBefore(std::string &chs, int sequences_begin,
                                 std::initializer_list<char> cs);

std::string *findSequencesBefore(std::string &chs, int sequences_begin,
                                 std::unordered_set<char> &end_tokens);

std::string *findSequences(std::string &chs, int sequences_begin);

void checkSequences(std::string &chs, int curr, std::string target);

bool isSameSequences(std::string &chs, int curr, std::string target);

bool isSame(std::string &s1, std::string &s2);

bool isSame(std::string &chs, int curr, char c);

bool isNotSame(std::string &chs, int curr, char c);

} // namespace marmot

#endif