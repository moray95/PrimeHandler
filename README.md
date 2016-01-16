This small library offers basic functions for operations on prime numbers.
The PrimeHandler template offers the following operations:

- Determining if a given number is prime
- Finding all the primes up to a given number
- Finding the prime factorization of a given number
- Finding the nth prime.

The library is guaranteed to be compiled with the following compilation flags:
-std=c++14 -pedanctic -Wall -Wextra

Documentation:
--------------

The documentation can be obtained using 'make'. It will be generated under
the doc folder, in HTML and LaTeX formats.

Exemple Usage:
--------------
```C++
PrimeHandler<> handler;
uintmax_t n = 0;
std::cin >> n;
std::cout << n << " is prime: " << handler.is_prime(n) << "\n";
std::cout << "The " << n << "th prime is " << handler.prime_at_index(n) << "\n";
std::cout << "Primes up to " << n << ":\n";

auto primes = handler.get_primes(n);
for (unsigned i = 0; i < primes.size() && primes[i] <= n; i++)
{
  std::cout << primes[i] << "\n";
}

std::cout << "n = ";
auto factors = handler.factorize(n);
std::cout << factors[0].base << "ˆ" << factors[0].exponent;
for (unsigned i = 1; i < factors.size(); i++)
{
  std::cout << " * " << factors[i].base << "ˆ" << factors[i].exponent;
}
std::cout << std::endl;

```
