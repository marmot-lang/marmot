#include "SyntaxExcept.h"

using namespace marmot;

SyntaxExcept::SyntaxExcept(std::string &chs, int curr) : chs(chs), curr(curr) {}

std::string *SyntaxExcept::message() {
  int min_len = std::min(100, (int)chs.length());
  std::string *message = new std::string();

  for (int i = curr; i < min_len; i++) {
    message->push_back(chs[i]);
  }
  return message;
}