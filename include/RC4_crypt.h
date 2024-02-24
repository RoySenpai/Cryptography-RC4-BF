/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Library Header
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

#ifndef _RC4_CRYPT_H
#define _RC4_CRYPT_H

#include "RC4_utils.h"

/*
 * @brief The length of the state in bytes.
 * @note This value is fixed and should not be changed.
 */
#define STATE_LENGTH 256

/*
 * @brief Initialize the RC4 state with the given key.
 * @param key The key to initialize the state with.
 * @param key_length The length of the key in bytes.
 * @param state The state to initialize.
 * @return void
 * @note The state must be 256 bytes long and must be allocated by the caller.
 */
void rc4_init(unsigned char *key, int key_length, unsigned char *state);

/*
 * @brief Encrypt or decrypt the input using the given state.
 * @param input The input to encrypt or decrypt.
 * @param output The output buffer to store the result.
 * @param input_length The length of the input in bytes.
 * @param state The state to use for encryption or decryption.
 * @return void
 * @note The input and output buffers must not overlap.
 * @note The input and output buffers must be at least input_length bytes long.
 * @warning The state must be initialized with rc4_init before calling this function.
 */
void rc4_crypt(unsigned char *input, unsigned char *output, int input_length, unsigned char *state);

#endif // _RC4_CRYPT_H