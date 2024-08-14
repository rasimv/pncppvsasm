#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <chrono>
#include <iomanip>

#include "mscpp.h"
#include "kauer.h"

template <typename C, typename ... A>
uint64_t exec(C c, A &&... a)
{
    const auto start = std::chrono::high_resolution_clock::now();

    c(std::forward<A>(a)...);

    const auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>
                                            (end - start).count();
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argv == nullptr || argv[1] == nullptr) return -1;

    long long count = 0;
    try { count = std::stoll(argv[1]); } catch(...) { return -1; }

    if (count < 0) return -1;

    std::vector<uint32_t> primes1(count, 0), primes2(count, 0);

    double cl = 0, k = 0;
    for (int i = 0; i < 10; ++i)
    {
        primes1 = primes2;
        cl += exec(find_primes_cl2, primes2.data(), primes2.size());

        primes1 = primes2;
        k += exec(find_primes, primes2.data(), primes2.size());

        if (primes1 != primes2)
        {
            std::cout << "err" << std::endl;
            return -1;
        }
    }

    std::cout << std::fixed << std::setprecision(0) << "us:\t"
        "cl: " << std::round(cl) << " | k: " << std::round(k) << std::endl;

    return 0;
}
