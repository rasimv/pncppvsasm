#pragma once

#include <cstdint>
#include <cstdlib>

inline static void find_primes_cl(uint32_t *primes, size_t count)
{
    uint32_t test = 1;

    for (size_t cur = 0; cur < count; )
    {
        test += 2;

        for (size_t i = 0; ; ++i)
        {
            if (i < cur)
            {
                const auto res{std::lldiv(test, primes[i])};
                if (res.rem == 0) break;
                if (primes[i] < res.quot) continue;
            }

			primes[cur] = test;
			++cur;

			break;
        }
    }
}

void find_primes_cl2(uint32_t *primes, size_t count);
