#ifndef _NEVIL_UTIL_PRINT_HPP_
#define _NEVIL_UTIL_PRINT_HPP_

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::stack<T> &s)
{
  std::stack<T> tmp = s;
  stream << '[';
  while (tmp.size() > 1)
  {
    stream << tmp.top() << ", ";
    tmp.pop();
  }
  stream << tmp.top() << ']';
  tmp.pop();
  return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T> &vec)
{
  stream << '[';
  for (size_t i = 0; i < vec.size() - 1 ; ++i)
    stream << vec[i] << ", ";
  stream << vec[vec.size() - 1] << ']';
  return stream;
}

template <typename T, typename T1>
std::ostream& operator<<(std::ostream& stream, const std::pair<T, T1> &p)
{
  stream << '<' << p.first << ',' << p.second << '>';
  return stream;
}

template <typename T, typename T1>
std::ostream& operator<<(std::ostream& stream, const std::unordered_map<T, T1> &map)
{
  for (auto it = map.begin(); it != map.end(); ++it)
    stream << it->first << ": " << it->second << std::endl;
  return stream;
}


#endif // _NEVIL_UTIL_PRINT_HPP_
