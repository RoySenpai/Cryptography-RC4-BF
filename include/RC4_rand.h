/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Random Number Generator Header File
 *  Copyright (C) 2024  Roy Simanovich and Chen Dahan
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _RC4_RAND_H
#define _RC4_RAND_H

#include <stdint.h>

#ifdef __x86_64__
typedef uint64_t UintRand;
#endif
#ifdef __i386__
typedef uint32_t UintRand;
#endif

/*
 * @brief Check if the CPU supports RDRAND.
 * @return 1 if RDRAND is supported, 0 otherwise.
 * @note Do not use this function directly, use rand64() instead.
 */
int __supports_rdrand();

/*
 * @brief Check if the CPU supports RDSEED.
 * @return 1 if RDSEED is supported, 0 otherwise.
 * @note Do not use this function directly, use rand64() instead.
 */
int __supports_rdseed();

/*
 * @brief Generate a random number using RDSEED.
 * @param rand A pointer to the random number to be generated.
 * @return 1 if RDSEED was successful, 0 otherwise.
 * @note This function is not guaranteed to be successful, and may require a retry loop.
 * @note Adapted from https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
 * @attention Do not use this function directly, use rand64() instead.
 */
int __rdseed_step(UintRand *rand);

/*
 * @brief Generate a random number using RDRAND.
 * @param rand A pointer to the random number to be generated.
 * @return 1 if RDRAND was successful, 0 otherwise.
 * @note This function is not guaranteed to be successful, and may require a retry loop.
 * @note Adapted from https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
 * @attention Do not use this function directly, use rand64() instead.
 */
int __rdrand_step(UintRand *rand);

/*
 * @brief Generate a random number using RDSEED, using a retry loop.
 * @param retries The number of times to retry RDSEED.
 * @param rand A pointer to the random number to be generated.
 * @return 1 if RDSEED was successful, 0 otherwise.
 * @attention Do not use this function directly, use rand64() instead.
 */
int __rdseed_retry(unsigned int retries, UintRand *rand);

/*
 * @brief Generate a random number using RDRAND, using a retry loop.
 * @param retries The number of times to retry RDRAND.
 * @param rand A pointer to the random number to be generated.
 * @return 1 if RDRAND was successful, 0 otherwise.
 * @attention Do not use this function directly, use rand64() instead.
 */
int __rdrand_retry(unsigned int retries, UintRand *rand);

/*
 * @brief Generate a random number using RDSEED or RDRAND.
 * @return A random number.
 * @attention If neither RDSEED nor RDRAND are supported, the function will use the C standard library's rand() PRNG instead.
 */
UintRand rand64(void);

#endif // _RC4_RAND_H