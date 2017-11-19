/**
  *@File    common.cpp
  *@Author  Wonseok Lee
  *@Brief   Source file for common classes for Kubica's algorithms.
  */

#include <stack>
#include <limits>
#include <vector>
#include <algorithm>

#include "common.hpp"

/**
  *@Brief default constructor
  */
pat_t::pat_t(void)
{

}

/**
  *@Brief user defined constructor
  */
pat_t::pat_t(s64_t _val, s64_t _pos)
{
  this->val = _val;
  this->pos = _pos;
}

/**
  *@Brief default copy constructor
  */
pat_t::pat_t(const pat_t& _ref)
{
  this->val = _ref.val;
  this->pos = _ref.pos;
}

/**
  *@Brief predicate for noraml sorting
  */
bool pat_t::cmpVal(const pat_t& l, const pat_t& r)
{
  return l.val < r.val;
}

/**
  *@Brief predicate for sorting (LMax)
  */
bool pat_t::cmpValPosMax(const pat_t& l, const pat_t& r)
{
  if (l.val != r.val)
    return l.val < r.val;
  else
    return l.pos < r.pos;
}

/**
  *@Brief predicate for sorting (LMin)
  */
bool pat_t::cmpValPosMin(const pat_t& l, const pat_t& r)
{
  if (l.val != r.val)
    return l.val < r.val;
  else
    return l.pos > r.pos;
}

/**
  *@Brief default constructor for location table which builds location table
  */
LocationTable::LocationTable(std::vector<pat_t> _pattern)
{
  _pattern[0].val = std::numeric_limits<s64_t>::min();
  _pattern[0].pos = std::numeric_limits<s64_t>::min();

  LMax.assign(_pattern.size(), 0);
  std::sort(_pattern.begin() + 1, _pattern.end(), pat_t::cmpValPosMax);

  std::stack<s64_t> maxStack;
  for (int pos = 1; pos < _pattern.size(); ++pos)
  {
    s64_t elem = _pattern[pos].pos;

    while (!maxStack.empty() && maxStack.top() >= elem)
      maxStack.pop();

    if (maxStack.empty())
      LMax[elem] = 0;
    else
      LMax[elem] = maxStack.top();

    maxStack.push(elem);
  }
  
  LMin.assign(_pattern.size(), 0);
  std::sort(_pattern.begin() + 1, _pattern.end(), pat_t::cmpValPosMin);

  std::stack<s64_t> minStack;
  for (int pos = _pattern.size() - 1; pos >= 1; --pos)
  {
    s64_t elem = _pattern[pos].pos;
    while (!minStack.empty() && minStack.top() >= elem)
      minStack.pop();

    if (minStack.empty())
      LMin[elem] = 0;
    else
      LMin[elem] = minStack.top();

    minStack.push(elem);
  }

  printf("LMIN\n");
  for (int i = 1; i < LMin.size(); ++i)
    printf("%5lld ", LMin[i]);
  printf("\n");

  printf("LMAX\n");
  for (int i = 1; i < LMax.size(); ++i)
    printf("%5lld ", LMax[i]);
  printf("\n");
}

/**
  *@Brief default constructor for order-borders table which builds order-borders table
  */
OrderBordersTable::OrderBordersTable(std::vector<pat_t>& _pattern, LocationTable& _locationTable)
{
  failure.assign(_pattern.size(), 0);
  failure[0] = -1;

  s64_t t = -1;
  for (s64_t i = 1; i < _pattern.size(); ++i)
  {
    while (true)
    {
      if (t < 0)
        break;

      s64_t a = _locationTable.LMax[t + 1];
      s64_t b = _locationTable.LMin[t + 1];
      s64_t y_a = (a == 0)? std::numeric_limits<s64_t>::min() : _pattern[i - t + a - 1].val;
      s64_t y_b = (b == 0)? std::numeric_limits<s64_t>::max() : _pattern[i - t + b - 1].val;

      if (y_a <= _pattern[i].val && _pattern[i].val <= y_b)
        break;

      t = failure[t];
    }
    failure[i] = ++t;
  }

  printf("ORDER-BORDER\n");
  for (int i = 1; i < failure.size(); ++i)
    printf("%5lld ", failure[i]);
  printf("\n");
}


