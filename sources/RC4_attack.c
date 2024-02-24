/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Brute Force Attack Program
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

#include "../include/RC4_attack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main(void) {
	unsigned char key[KEY_LENGTH] = {0};
	unsigned char state[STATE_LENGTH] = {0};
	unsigned char plaintext[PLAINTEXT_LENGTH + 1] = "This is a very secret message from general Kenobi, only the chosen one can read it.";
	unsigned char ciphertext[PLAINTEXT_LENGTH + 1] = {0};

	// Randomly generate a key
	for (int i = 0; i < KEY_LENGTH; i++)
		key[i] = (unsigned char)rand64();

	// Encrypt the plaintext
	rc4_init(key, KEY_LENGTH, state);
	rc4_crypt(plaintext, ciphertext, PLAINTEXT_LENGTH, state);

	// Print the ciphertext
	printf("Ciphertext: ");

	for (int i = 0; i < PLAINTEXT_LENGTH; i++)
		printf("%02x", ciphertext[i]);

	printf("\n");

	printf("Starting brute force attack...\n");
	printf("Number of threads: %d\n", NUM_THREADS);
	printf("Keyspace bits: %d bits\n", KEYSPACE_BITS);

	ThreadData thread_data[NUM_THREADS];

	uint64_t keyspace_per_thread = (1ULL << KEYSPACE_BITS) / NUM_THREADS;
	uint64_t start_key = 0;

// Windows compatibility layer
#ifdef _WIN32
	HANDLE threads[NUM_THREADS];
#else
	pthread_t threads[NUM_THREADS];
#endif

	for (int i = 0; i < NUM_THREADS; i++)
	{
		thread_data[i].start_key = start_key;
		thread_data[i].end_key = start_key + keyspace_per_thread - 1;
		thread_data[i].thread_id = (i + 1);
		thread_data[i].total_keys_checked = 0;
		memcpy(thread_data[i].ciphertext, ciphertext, PLAINTEXT_LENGTH + 1);
		start_key += keyspace_per_thread;

#ifdef _WIN32
		threads[i] = CreateThread(NULL, 0, brute_force_thread, (void *)&thread_data[i], 0, NULL);
#else
		pthread_create(&threads[i], NULL, brute_force_thread, (void *)&thread_data[i]);
#endif
	}

#ifdef _WIN32
	CreateThread(NULL, 0, count_keys_checked, (void *)thread_data, 0, NULL);
	WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

	for (int i = 0; i < NUM_THREADS; i++)
		CloseHandle(threads[i]);
#else
	pthread_t count_thread;
	pthread_create(&count_thread, NULL, count_keys_checked, (void *)thread_data);

	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

#endif

	return 0;
}

#ifdef _WIN32
DWORD WINAPI brute_force_thread(LPVOID thread_data_ptr) // Windows compatibility layer
#else
void *brute_force_thread(void *thread_data_ptr)
#endif
{
	ThreadData *thread_data = (ThreadData *)thread_data_ptr;
	unsigned char decrypted_text[PLAINTEXT_LENGTH + 1] = {0};
	unsigned char state[STATE_LENGTH] = {0};
	unsigned char current_key[KEY_LENGTH] = {0};
	unsigned char ciphertext[PLAINTEXT_LENGTH + 1] = {0};
	uint64_t start_key = thread_data->start_key;
	uint64_t end_key = thread_data->end_key;
	uint64_t keyspace_per_thread = (1ULL << KEYSPACE_BITS) / NUM_THREADS;
	int thread_id = thread_data->thread_id;

	memcpy(ciphertext, thread_data->ciphertext, PLAINTEXT_LENGTH + 1);

	for (uint64_t key = start_key; key < end_key; key++)
	{
		++thread_data->total_keys_checked;

		// Update the current key to the next key in the keyspace
		for (int i = 0; i < KEY_LENGTH; i++)
			current_key[i] = (key >> (8 * i)) & 0xFF;

		// Decrypt the ciphertext using the current key
		rc4_init(current_key, KEY_LENGTH, state);
		rc4_crypt(ciphertext, decrypted_text, PLAINTEXT_LENGTH, state);

		int isValid = 1;

		// Check if the decrypted text contains only printable ASCII characters.
		for (int i = 0; i < PLAINTEXT_LENGTH; i++)
		{
			if (decrypted_text[i] < 0x20 || decrypted_text[i] > 0x7E)
			{
				// The decrypted text contains non-printable ASCII characters
				// This key is not valid, so we skip the rest of the loop
				isValid = 0;
				break;
			}
		}

		if (!isValid)
			continue;

		// Print the key and the decrypted text
		printf("Key found: 0x");

		for (int i = 0; i < KEY_LENGTH; i++)
			printf("%02x", current_key[i]);

		printf("\nPlaintext: %s\n", decrypted_text);

		// We found the key, so we can terminate the program completely.
		exit(0);
	}

// Windows compatibility layer
#ifdef _WIN32
	return 0;
#else
	return NULL;
#endif
}

#ifdef _WIN32
DWORD WINAPI count_keys_checked(LPVOID lpParam) // Windows compatibility layer
#else
void *count_keys_checked(void *lpParam)
#endif
{
	PThreadData thread_data = (PThreadData)lpParam;

	// Randomly generate a verbose interval to print the progress of the brute force attack
	// Used to avoid printing too many times, but still print enough to show progress.
	uint64_t verbose_interval = KEYSPACE_SIZE / (rand64() % 1000 + 100);

	// Busy wait until all threads have finished
	// Print the progress of the brute force attack.
	while (1)
	{
		uint64_t total_keys_checked = 0;

		for (int i = 0; i < NUM_THREADS; i++)
			total_keys_checked += thread_data[i].total_keys_checked;

		if (total_keys_checked % verbose_interval == 0)
// Some windows garbage fix for printf
#ifdef _WIN32
			printf("Keys checked: %llu/%llu, Progress: %.4f%%\n", 
			total_keys_checked, 
			KEYSPACE_SIZE, 
			(double)total_keys_checked / KEYSPACE_SIZE * 100
		);
#else
			printf("Keys checked: %lu/%llu, Progress: %.4f%%\n", 
			total_keys_checked, 
			KEYSPACE_SIZE, 
			(double)total_keys_checked / KEYSPACE_SIZE * 100
		);
#endif

		if (total_keys_checked >= KEYSPACE_SIZE)
			break;
	}

// Windows compatibility layer
#ifdef _WIN32
	return 0;
#else
	return NULL;
#endif
}