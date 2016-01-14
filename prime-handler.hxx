#include <vector>
#include <algorithm>
#include <cmath>

#include "prime-handler.hh"

template <typename T>
bool PrimeHandler<T>::is_prime(T x)
{
  if (x == 0 || x == 1)
    return false;
  add_primes_(x);
  return !is_divisible_(x);
}

template <typename T>
const std::vector<T>& PrimeHandler<T>::get_primes(T max)
{
  add_primes_(max);
  return primes_;
}

template <typename T>
void PrimeHandler<T>::add_primes_(T max)
{
  primes_.reserve(max / log(max));
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
bool PrimeHandler<T>::contains_(T x)
{
  return std::lower_bound(primes_.begin(), primes_.end(), x) != primes_.end();
}

template <typename T>
T PrimeHandler<T>::max_prime_()
{
  return primes_.back();
}

template <typename T>
bool PrimeHandler<T>::is_divisible_(T x)
{
  for (long i = 0; i < primes_.size() && primes_[i] < x; i++)
  {
    if (x % primes_[i] == 0)
      return true;
  }
  return false;
}
