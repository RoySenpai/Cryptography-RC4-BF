/*
 *  Introduction to Cyptography Course Assignment 1
 *  RC4 Brute Force Attack Header File
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

#ifndef _RC4_ATTACK_H
#define _RC4_ATTACK_H

#include "RC4_crypt.h"
#include "RC4_settings.h"

// Windows compatibility layer
#ifdef _WIN32
#include <windows.h>

/*
 * @brief The function to be called by each thread.
 * @param thread_data_ptr A pointer to the thread data.
 * @return The exit code of the thread.
 * @note Windows way of defining a thread function.
 */
DWORD WINAPI brute_force_thread(LPVOID thread_data_ptr);

/*
 * @brief The function to be called by the counting thread to print the progress of the brute force attack.
 * @param lpParam A pointer to the thread data.
 * @return The exit code of the thread.
 * @note Windows way of defining a thread function.
 */
DWORD WINAPI count_keys_checked(LPVOID lpParam);
#else
#include <pthread.h>

/*
 * @brief The function to be called by each thread.
 * @param thread_data_ptr A pointer to the thread data.
 * @return The exit code of the thread.
 * @note POSIX way of defining a thread function.
 */
void *brute_force_thread(void *thread_data_ptr);

/*
 * @brief The function to be called by the counting thread to print the progress of the brute force attack.
 * @param lpParam A pointer to the thread data.
 * @return The exit code of the thread.
 * @note POSIX way of defining a thread function.
 */
void *count_keys_checked(void *lpParam);
#endif

#endif // _RC4_ATTACK_H