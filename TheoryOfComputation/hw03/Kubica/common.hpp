/**
  *@File    common.hpp
  *@Author  Wonseok Lee
  *@Brief   Header file for common classes for Kubica's algorithms.
  */

#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <vector>

typedef long long s64_t;

/**
  *@Brief class for pattern element
  */
class pat_t
{
public:
  s64_t val;
  s64_t pos;

  pat_t(void);
  pat_t(s64_t _val, s64_t _pos);
  pat_t(const pat_t& _ref);

  static bool cmpVal(const pat_t& l, const pat_t& r);
  static bool cmpValPosMax(const pat_t& l, const pat_t& r);
  static bool cmpValPosMin(const pat_t& l, const pat_t& r);
};

/**
  *@Brief class for location table
  */
class LocationTable
{
public:
  std::vector<s64_t> LMax;
  std::vector<s64_t> LMin;

  LocationTable(std::vector<pat_t> _pattern);
};

/**
  *@Brief class for order-borders table
  */
class OrderBordersTable
{
public:
  std::vector<s64_t> failure;

  OrderBordersTable(std::vector<pat_t>& _pattern, LocationTable& _locationTable);
};

#endif
