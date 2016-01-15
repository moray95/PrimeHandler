#pragma once
#include <vector>
#include <cstdint>

template <typename T>
struct PrimeFactor
{
  T base = 0;
  T exponent = 0;
};

template <typename T = uintmax_t>
class PrimeHandler
{

public:
  using size_type = typename std::vector<T>::size_type;
  bool is_prime(const T& x);
  const std::vector<T>& get_primes(const T& max);
  size_type remove_greater_then(const T& n);
  std::vector<PrimeFactor<T>> factorize(T n);

private:
  std::vector<T> primes_{2};
  T last_seen_ = 2;
  void add_primes_(const T& max);
  bool contains_(const T& x) const;
  bool is_divisible_(const T& x, const T& root) const;
  bool is_divisible_(const T& x) const;
};
#include "prime-handler.hxx"