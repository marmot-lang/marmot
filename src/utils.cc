#include "utils.h"
#include "header.h"
#include "syntax_except.h"

using namespace marmot;

bool marmot::is_end(std::string &chs, int curr) { return curr >= chs.size(); }

bool marmot::is_not_end(std::string &chs, int curr) {
  return !is_end(chs, curr);
}

bool marmot::is_in(std::string &chs, int curr, std::unordered_set<char> &cs) {
  if (is_end(chs, curr))
    return false;

  return cs.contains(chs[curr]);
}

bool marmot::is_not_in(std::string &chs, int curr,
                       std::unordered_set<char> &cs) {
  return !is_in(chs, curr, cs);
}

bool marmot::is_in(std::string &chs, int curr, initializer_list<char> cs) {

  std::unordered_set<char> set;

  for (const char *itr = cs.begin(); itr != cs.end(); itr++) {
    set.insert(*itr);
  }

  bool result = is_in(chs, curr, set);

  std::unordered_set<char>().swap(set);

  return result;
}

bool marmot::is_not_in(std::string &chs, int curr, initializer_list<char> cs) {
  return !is_in(chs, curr, cs);
}

bool marmot::is_write_space(std::string &chs, int curr) {
  return is_in(chs, curr, tokens::WRITE_SPACE);
}

int marmot::ignore_white_space(std::string &chs, int curr) {
  while (is_write_space(chs, curr)) {
    curr++;
  }
  return curr;
}

bool marmot::is_not_white_space(std::string &chs, int i) {
  return !is_write_space(chs, i);
}

std::string *marmot::find_sequences_before(std::string &chs,
                                           int sequences_begin,
                                           initializer_list<char> cs) {
  int sequences_end = sequences_begin;

  std::unordered_set<char> set;

  for (const char *itr = cs.begin(); itr != cs.end(); itr++) {
    set.insert(*itr);
  }

  while (is_not_in(chs, sequences_end, set)) {
    sequences_end++;
  }

  std::unordered_set<char>().swap(set);

  int identifier_len = sequences_end - sequences_begin;
  std::string *sequence = new std::string();

  for (int i = 0; i < identifier_len; i++) {
    sequence->push_back(chs[sequences_begin + i]);
  }

  return sequence;
}

std::string *marmot::find_sequences(std::string &chs, int sequences_begin) {
  return find_sequences_before(chs, sequences_begin, tokens::WRITE_SPACE);
}

void marmot::check_sequences(std::string &chs, int curr, std::string target) {
  std::string *sequences = find_sequences(chs, curr);

  if (sequences->size() != target.size()) {
    throw new syntax_except(chs, curr);
  }

  for (int i = 0; i < sequences->size(); i++) {
    if ((*sequences)[i] != target[i]) {
      throw new syntax_except(chs, curr);
    }
  }
}

bool marmot::is_same_sequences(std::string &chs, int curr, std::string target) {
  std::string *sequences = find_sequences(chs, curr);

  if (sequences->size() != target.size()) {
    return false;
  }

  for (int i = 0; i < sequences->size(); i++) {
    if ((*sequences)[i] != target[i]) {
      return false;
    }
  }

  return true;
}

bool marmot::is_same(std::string &s1, std::string &s2) {
  if (s1.length() != s2.length())
    return false;

  int len = s1.length();
  for (int i = 0; i < len; i++) {
    if (s1[i] == s2[i])
      return false;
  }

  return true;
}