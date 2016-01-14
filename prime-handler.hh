#pragma once
#include <vector>
#include <cstdint>

template <typename T = uintmax_t>
class PrimeHandler
{

public:
  using size_type = typename std::vector<T>::size_type;
  bool is_prime(T x);
  const std::vector<T>& get_primes(T max);
  size_type remove_greater_then(T n);

private:
  std::vector<T> primes_{2};
  T last_seen_ = 2;
  void add_primes_(T max);
  bool contains_(T x);
  T max_prime_();
  bool is_divisible_(T x);
};
#include "prime-handler.hxx"