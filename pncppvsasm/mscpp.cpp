#include "mscpp.h"

void find_primes_cl2(uint32_t *primes, size_t count)
{
    uint32_t test = 1;

    for (size_t cur = 0; cur < count; )
    {
        test += 2;

        for (size_t i = 0; ; ++i)
        {
            if (i < cur)
            {
                const auto quot = test / primes[i];
                const auto rem = test % primes[i];
                if (rem == 0) break;
                if (primes[i] < quot) continue;
            }

            primes[cur] = test;
            ++cur;

            break;
        }
    }
}
