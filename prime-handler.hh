#pragma once
#include <vector>
#include <cstdint>

/// A structure representing an prime factor of the form base^exponent.
template <typename T>
struct PrimeFactor
{
  /// The base of the factor.
  T base = 0;
  /// The exponent of the factor.
  T exponent = 0;
};

/// A class for manipulating different operations on prime numbers.
template <typename T = uintmax_t>
class PrimeHandler
{

public:
  /**
   * Type used for indexing.
   */
  using size_type = typename std::vector<T>::size_type;

  /**
   * Returns whether or not x is a prime number.
   */
  bool is_prime(const T& x);
  /**
   * Returns all the prime numbers up to max. Can potentially contain
   * greater numbers then max.
   */
  const std::vector<T>& get_primes(const T& max);
  /**
   * Removes all prime numbers stored greater then n. Used to reclaim space.
   * Using other functions after reclaiming space will potentially increse
   * the runtime. Returns the number of primes removed.
   */
  size_type remove_greater_then(const T& n);
  /**
   * Caches all primes less then or equal to n.
   * Returns the number of primes cached.
   * Increses performance before usages of the following kind:
   * \code
   *  for (uintmax_t i = 0; i < big_number; i++)
   *    std::cout << i << "is prime: " << prime_handler.is_prime() << "\n";
   * \endcode
   */
  size_type cache_up_to(const T& n);
  /**
   * Returns the list of all prime factors of n. The returned list is
   * sorted in increasing order of the base.
   */
  std::vector<PrimeFactor<T>> factorize(T n);
  /**
   * Returns the nth prime number, indexed starting at 0.
   */
  const T& prime_at_index(size_type n);

private:
  /**
   * List of cached primes. Always contains at least 2.
   */
  std::vector<T> primes_{2};
  /**
   * Last number tested for primality. All primes less or equal to
   * last_seen_ are stored in primes_. Is greater or equal to 2.
   */
  T last_seen_ = 2;
  /**
   * Adds all primes up to max to primes_.
   */
  void add_primes_(const T& max);
  /// Returns whether or not primes_ contains x.
  bool contains_(const T& x) const;
  /**
   * Returns whether there exists a number in primes_ that divides x.
   * This function tests all primes in primes_ less or equal to root, which
   * shall be equal to √x.
   */
  bool is_divisible_(const T& x, const T& root) const;
  /// Equivalent to is_divisible_(x, √x)
  bool is_divisible_(const T& x) const;
  /** Returns an estimate of the nth prime. The returned value
   *  is always greater then the actual nth prime.
   */
  T estimate_prime_at_index_(size_type n);
};
#include "prime-handler.hxx"