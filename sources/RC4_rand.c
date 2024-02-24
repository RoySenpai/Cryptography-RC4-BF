/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Random Number Generator Implementation
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

#include "../include/RC4_rand.h"
#include <stdlib.h> // for rand()
#include <cpuid.h>	// for __get_cpuid intrinsic
#include <time.h>	// for time()

int __supports_rdrand() {
	const unsigned RDRAND_bit = (1 << 30);
	unsigned eax = 0, ebx = 0, ecx = 0, edx = 0;

	return (__get_cpuid(1, &eax, &ebx, &ecx, &edx) ? ((ecx & RDRAND_bit) == RDRAND_bit) : 0);
}

int __supports_rdseed() {
	const unsigned RDSEED_bit = (1 << 18);
	unsigned eax = 0, ebx = 0, ecx = 0, edx = 0;
	return (__get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx) ? ((ebx & RDSEED_bit) == RDSEED_bit) : 0);
}

int __rdrand_step(UintRand *rand) {
	unsigned char ok;

	__asm__ volatile("rdrand %0;"
					 "setc %1"
					 : "=r"(*rand), "=qm"(ok));

	return (int)ok;
}

int __rdrand_retry(unsigned int retries, UintRand *rand) {
	unsigned count = 0;

	while (count <= retries)
	{
		if (__rdrand_step(rand))
			return 1;

		++count;
	}

	return 0;
}

int __rdseed_step(UintRand *rand) {
	unsigned char ok;

	__asm__ volatile("rdseed %0;"
					 "setc %1"
					 : "=r"(*rand), "=qm"(ok));

	return (int)ok;
}

int __rdseed_retry(unsigned int retries, UintRand *rand) {
	unsigned count = 0;

	while (count <= retries)
	{
		if (__rdseed_step(rand))
			return 1;

		++count;
	}

	return 0;
}

UintRand rand64() {
	UintRand num;

	// try RDSEED first
	if (__supports_rdseed() && __rdseed_retry(10, &num))
		return num;

	// then try RDRAND
	if (__supports_rdrand() && __rdrand_retry(10, &num))
		return num;

	// fall back to software-based PRNG
	// generate a random number using the system time as the seed, and the rand() function.
	srand(time(NULL));
	return (UintRand)rand();
}