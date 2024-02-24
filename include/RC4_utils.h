/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Library Utilities Header
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

#ifndef _RC4_UTILS_H
#define _RC4_UTILS_H

#include <stdint.h>

/*
 * @brief Swap the values of two unsigned char variables.
 * @param a The first variable to swap.
 * @param b The second variable to swap.
 * @return void
 * @note This function is used internally by the RC4 library and should not be called by the user.
 */
void __swap(unsigned char *a, unsigned char *b);

#endif // _RC4_UTILS_H