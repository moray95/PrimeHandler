#pragma once
#include <vector>
#include <cstdint>

template <typename T = uintmax_t>
class PrimeHandler
{

public:
  bool is_prime(T x);
  const std::vector<T>& get_primes(T max);

private:
  std::vector<T> primes_{2};
  T last_seen_ = 2;
  void add_primes_(T max);
  bool contains_(T x);
  T max_prime_();
  bool is_divisible_(T x);
};
#include "prime-handler.hxx"