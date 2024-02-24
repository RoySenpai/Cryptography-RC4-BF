/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Settings
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

#ifndef _RC4_SETTINGS_H
#define _RC4_SETTINGS_H

#include <stdint.h>

#ifdef __x86_64__
    typedef uint64_t UintRand;
#endif
#ifdef __i386__
    typedef uint32_t UintRand;
#endif

/*
 * @brief The length of the plaintext in bytes.
 * @note The default value is 83 bytes, which is the 
 * length of the plaintext "This is a very secret 
 * message from general Kenobi, only the chosen 
 * one can read it."
*/
#define PLAINTEXT_LENGTH 83

/*
 * @brief The length of the key in bytes.
 * @note The default value is 4 bytes.
*/
#define KEY_LENGTH 4

/*
 * @brief The size of the keyspace in bits.
 * @note The default value is 32 bits, which is the size of the keyspace for a 4-byte key.
*/
#define KEYSPACE_BITS (KEY_LENGTH * 8)

/*
 * @brief The size of the keyspace.
 * @note The default value is 2^32 (4,294,967,296).
*/
#define KEYSPACE_SIZE (1ULL << KEYSPACE_BITS)

/*
 * @brief The number of threads to use for the brute force attack.
 * @note The default value is 8 threads.
*/
#define NUM_THREADS 8

/*
 * @brief A structure to hold the data for each thread.
 * @param ciphertext The ciphertext to decrypt.
 * @param start_key The start of the keyspace for this thread.
 * @param end_key The end of the keyspace for this thread.
 * @param total_keys_checked The total number of keys checked by this thread.
 * @param thread_id The ID of this thread.
 * @note This structure is used to pass the data to each thread.
*/
typedef struct _ThreadData
{
	/*
	 * @brief The ciphertext to decrypt.
	 * @note The length of the ciphertext is PLAINTEXT_LENGTH + 1 (to include the null terminator).
	*/
	unsigned char ciphertext[PLAINTEXT_LENGTH + 1];

	/*
	 * @brief The start of the keyspace for this thread.
	 * @note The start_key is inclusive.
	*/
	uint64_t start_key;

	/*
	 * @brief The end of the keyspace for this thread.
	 * @note The end_key is exclusive.
	*/
	uint64_t end_key;

	/*
	 * @brief The total number of keys checked by this thread.
	 * @note This value is updated by the thread as it checks keys.
	*/
	uint64_t total_keys_checked;

	/*
	 * @brief The ID of this thread.
	*/
	int thread_id;
} ThreadData, *PThreadData;

/*
 * @brief Try to generate a truly random number using CPU instructions.
 * @return A random number (64 bits or 32 bits, depending on the CPU).
 * @note If the function fails to generate a random number, it will instead return a pseudo-random number.
 */
extern UintRand rand64(void);

#endif // _RC4_SETTINGS_H