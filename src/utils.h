#ifndef __MARMOT_UTILS_H__
#define __MARMOT_UTILS_H__

#include "header.h"
#include "syntax_except.h"
#include "tokens.h"

namespace marmot {

bool is_end(std::string &chs, int curr);

bool is_not_end(std::string &chs, int curr);

bool is_in(std::string &chs, int curr, std::unordered_set<char> &cs);

bool is_not_in(std::string &chs, int curr, std::unordered_set<char> &cs);

bool is_in(std::string &chs, int curr, initializer_list<char> cs);

bool is_not_in(std::string &chs, int curr, initializer_list<char> cs);

bool is_write_space(std::string &chs, int curr);

int ignore_white_space(std::string &chs, int curr);

bool is_not_white_space(std::string &chs, int i);

std::string *find_sequences_before(std::string &chs, int sequences_begin,
                                   initializer_list<char> cs);

std::string *find_sequences(std::string &chs, int sequences_begin);

void check_sequences(std::string &chs, int curr, std::string target);

bool is_same_sequences(std::string &chs, int curr, std::string target);

bool is_same(std::string &s1, std::string &s2);

} // namespace marmot

#endif