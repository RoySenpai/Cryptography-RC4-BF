/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Library Functions
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

#include "../include/RC4_crypt.h"

void rc4_init(unsigned char *key, int key_length, unsigned char *state) {
	int j = 0;

	// Initialize the state with the identity permutation
	for (int i = 0; i < STATE_LENGTH; i++)
		state[i] = i;

	// Permute the state with the key
	for (int i = 0; i < STATE_LENGTH; i++)
	{
		// Update the index
		j = (j + state[i] + key[i % key_length]) % STATE_LENGTH;

		// Swap the values of state[i] and state[j]
		__swap(&state[i], &state[j]);
	}
}

void rc4_crypt(unsigned char *input, unsigned char *output, int input_length, unsigned char *state) {
	int i = 0, j = 0;

	// Encrypt or decrypt the input using the state
	for (int n = 0; n < input_length; n++)
	{
		// Update the indices
		i = (i + 1) % STATE_LENGTH;
		j = (j + state[i]) % STATE_LENGTH;

		// Swap the values of state[i] and state[j]
		__swap(&state[i], &state[j]);

		// Generate the key
		int k = state[(state[i] + state[j]) % STATE_LENGTH];

		// Encrypt or decrypt the input
		output[n] = input[n] ^ k;
	}
}