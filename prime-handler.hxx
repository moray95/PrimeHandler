#include <vector>
#include <algorithm>
#include <cmath>

#include "prime-handler.hh"

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
auto PrimeHandler<T>::cache_up_to(const T& n) -> size_type
{
  auto old_size = primes_.size();
  add_primes_(estimate_prime_at_index_(n));
  return primes_.size() - old_size;
}

template <typename T>
auto PrimeHandler<T>::factorize(T n) -> std::vector<PrimeFactor<T>>
{
  std::vector<PrimeFactor<T>> factors;
  for (size_type i = 0; n > 1; i++)
  {
    auto prime = prime_at_index(i);
    PrimeFactor<T> factor;
    factor.base = prime;
    while (n > 1 && n % prime == 0)
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

template <typename T>
const T&  PrimeHandler<T>::prime_at_index(size_type n)
{
  if (n < primes_.size())
    return primes_[n];
  add_primes_(estimate_prime_at_index_(n));
  while (primes_.size() <= n)
  {
    add_primes_(last_seen_ + 10);
  }
  return primes_[n];
}

template <typename T>
void PrimeHandler<T>::add_primes_(const T& max)
{
  primes_.reserve(1.25506 * max / log(max));
  T min = last_seen_;

  if (min % 2 == 0)
    min++;

  for (T i = min; i <= max; i += 2)
  {
    if (!is_divisible_(i))
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
    const T& prime = primes_[i];
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
  return is_divisible_(x, sqrt(x) + 1);
}

template <typename T>
T PrimeHandler<T>::estimate_prime_at_index_(size_type n)
{
  std::vector<T> first_prime{0, 2, 3, 5, 7, 11};
  if (n < first_prime.size())
    return first_prime[n];

  double logn = log(n);
  double loglogn = log(logn);

  if (n >= 688383)
  {
    return n * (logn + loglogn - 1.0 + (loglogn - 2.00) / logn);
  }
  if (n >= 178974)
  {
    return n * (logn + logn - 1.0 + (loglogn - 1.95) / logn);
  }
  if (n >=  39017)
  {
    return n * (logn + loglogn - 0.9484);
  }
  return n * (logn  +  0.6000 * loglogn);
}
