#include <vector>
#include <algorithm>
#include <cmath>

#include "prime-handler.hh"

// O(nˆ3/2 / log(n)) --- O(√n / log(n))
template <typename T>
bool PrimeHandler<T>::is_prime(const T& x)
{
  if (x == 0 || x == 1)
    return false;
  if (x == 2)
    return true;
  T root = sqrt(x) + 1;
  add_primes_(root);
  return !is_divisible_(x, root);
}

template <typename T>
const std::vector<T>& PrimeHandler<T>::get_primes(const T& max)
{
  add_primes_(max);
  return primes_;
}

template <typename T>
auto PrimeHandler<T>::remove_greater_then(const T& n) -> size_type
{
  size_type count = 0;
  while (!primes_.empty() && primes_.back() > n)
  {
    primes_.pop_back();
    count++;
  }
  if (primes_.empty())
  {
    primes_.push_back(2);
  }
  last_seen_ = primes_.back();
  primes_.shrink_to_fit();
  return count;
}

template <typename T>
auto PrimeHandler<T>::factorize(T n) -> std::vector<PrimeFactor<T>>
{
  add_primes_(n);
  std::vector<PrimeFactor<T>> factors;
  for (auto prime : primes_)
  {
    if (n == 0)
      break;
    PrimeFactor<T> factor;
    factor.base = prime;
    while (n > 0 && n % prime == 0)
    {
      factor.exponent++;
      n /= prime;
    }
    if (factor.exponent > 0)
    {
      factors.push_back(std::move(factor));
    }
  }
  return factors;
}

// O(n * π(n))
template <typename T>
void PrimeHandler<T>::add_primes_(const T& max)
{

  primes_.reserve(1.25506 * max / log(max));
  T min = last_seen_;

  if (min % 2 == 0)
    min++;

  for (T i = min; i <= max; i += 2)
  {
    if (!is_divisible_(i, sqrt(i)))
    {
      primes_.push_back(i);
    }
  }
  last_seen_ = max;
}

template <typename T>
bool PrimeHandler<T>::contains_(const T& x) const
{
  return std::lower_bound(primes_.begin(), primes_.end(), x) != primes_.end();
}

// O(π(√n))
template <typename T>
bool PrimeHandler<T>::is_divisible_(const T& x, const T& root) const
{
  size_type size = primes_.size();
  for (size_type i = 0; i < size; i++)
  {
    T prime = primes_[i];
    if (prime > root)
      break;
    if (x % prime == 0)
      return true;
  }
  return false;
}

template <typename T>
bool PrimeHandler<T>::is_divisible_(const T& x) const
{
  return is_divisible_(x, sqrt(x));
}
