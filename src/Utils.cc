#include "Utils.h"
#include "Header.h"
#include "SyntaxExcept.h"

using namespace marmot;

bool marmot::isEnd(std::string &chs, int curr) { return curr >= chs.size(); }

bool marmot::isNotEnd(std::string &chs, int curr) { return !isEnd(chs, curr); }

bool marmot::isIn(std::string &chs, int curr, std::unordered_set<char> &cs) {
  if (isEnd(chs, curr))
    return false;

  return cs.contains(chs[curr]);
}

bool marmot::isNotIn(std::string &chs, int curr, std::unordered_set<char> &cs) {
  return !isIn(chs, curr, cs);
}

bool marmot::isIn(std::string &chs, int curr, std::initializer_list<char> cs) {
  for (const char *itr = cs.begin(); itr != cs.end(); itr++) {
    if (chs[curr] == (*itr)) {
      return true;
    }
  }

  return false;
}

bool marmot::isNotIn(std::string &chs, int curr,
                     std::initializer_list<char> cs) {
  return !isIn(chs, curr, cs);
}

bool marmot::isWriteSpace(std::string &chs, int curr) {
  return isIn(chs, curr, tokens::WRITE_SPACE);
}

int marmot::ignoreWhiteSpace(std::string &chs, int curr) {
  while (isWriteSpace(chs, curr)) {
    curr++;
  }
  return curr;
}

bool marmot::isNotWhiteSpace(std::string &chs, int curr) {
  return !isWriteSpace(chs, curr);
}

std::string *
marmot::findSequencesBefore(std::string &chs, int sequences_begin,
                            std::initializer_list<char> end_tokes) {
  std::unordered_set<char> end_tokes_set;

  for (const char *itr = end_tokes.begin(); itr != end_tokes.end(); itr++) {
    end_tokes_set.insert(*itr);
  }

  return findSequencesBefore(chs, sequences_begin, end_tokes_set);

  std::unordered_set<char>().swap(end_tokes_set);
}

std::string *marmot::findSequencesBefore(std::string &chs, int sequences_begin,
                                         std::unordered_set<char> &end_tokens) {
  int sequences_end = sequences_begin;

  while (isNotIn(chs, sequences_end, end_tokens)) {
    sequences_end++;
  }

  int identifier_len = sequences_end - sequences_begin;
  std::string *sequence = new std::string();

  for (int i = 0; i < identifier_len; i++) {
    sequence->push_back(chs[sequences_begin + i]);
  }

  return sequence;
}

std::string *marmot::findSequences(std::string &chs, int sequences_begin) {
  return findSequencesBefore(chs, sequences_begin, tokens::WRITE_SPACE);
}

void marmot::checkSequences(std::string &chs, int curr, std::string target) {
  std::string *sequences = findSequences(chs, curr);

  if (sequences->size() != target.size()) {
    throw new SyntaxExcept(chs, curr);
  }

  for (int i = 0; i < sequences->size(); i++) {
    if ((*sequences)[i] != target[i]) {
      throw new SyntaxExcept(chs, curr);
    }
  }
}

bool marmot::isSameSequences(std::string &chs, int curr, std::string target) {
  std::string *sequences = findSequences(chs, curr);

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

bool marmot::isSame(std::string &s1, std::string &s2) {
  if (s1.length() != s2.length())
    return false;

  int len = s1.length();
  for (int i = 0; i < len; i++) {
    if (s1[i] == s2[i])
      return false;
  }

  return true;
}

bool marmot::isSame(std::string &chs, int curr, char c) {
  return curr < chs.length() && chs[curr] == c;
}

bool marmot::isNotSame(std::string &chs, int curr, char c) {
  return !isSame(chs, curr, c);
}