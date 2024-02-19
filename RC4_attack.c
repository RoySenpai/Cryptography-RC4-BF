#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#define PLAINTEXT_LENGTH 83 // The length of the plaintext in bytes
#define STATE_LENGTH 256
#define KEY_LENGTH 4 // The length of the key in bytes
#define KEYSPACE_BITS (KEY_LENGTH * 8) // The size of the keyspace in bits
#define NUM_THREADS 12 // Adjust this value based on the number of threads you want to use

typedef struct
{
    unsigned char ciphertext[PLAINTEXT_LENGTH + 1];
    uint64_t start_key;
    uint64_t end_key;
    int thread_id;
} ThreadData;

void rc4_init(unsigned char *key, int key_length, unsigned char *state)
{
    for (int i = 0; i < STATE_LENGTH; i++)
    {
        state[i] = i;
    }

    int j = 0;
    for (int i = 0; i < STATE_LENGTH; i++)
    {
        j = (j + state[i] + key[i % key_length]) % STATE_LENGTH;
        unsigned char temp = state[i];
        state[i] = state[j];
        state[j] = temp;
    }
}

void rc4_crypt(unsigned char *input, unsigned char *output, int input_length, unsigned char *state)
{
    int i = 0;
    int j = 0;
    for (int n = 0; n < input_length; n++)
    {
        i = (i + 1) % STATE_LENGTH;
        j = (j + state[i]) % STATE_LENGTH;
        unsigned char temp = state[i];
        state[i] = state[j];
        state[j] = temp;
        int k = state[(state[i] + state[j]) % STATE_LENGTH];
        output[n] = input[n] ^ k;
    }
}

void *brute_force_thread(void *thread_data_ptr)
{
    ThreadData *thread_data = (ThreadData *)thread_data_ptr;
    unsigned char decrypted_text[PLAINTEXT_LENGTH + 1] = {0};
    unsigned char state[STATE_LENGTH] = {0};
    unsigned char current_key[KEY_LENGTH] = {0};
    unsigned char ciphertext[PLAINTEXT_LENGTH + 1] = {0};
    uint64_t start_key = thread_data->start_key;
    uint64_t end_key = thread_data->end_key;
    int thread_id = thread_data->thread_id;
    uint64_t keys_checked = 0;
    uint64_t keyspace_per_thread = (1ULL << KEYSPACE_BITS) / NUM_THREADS;

    memcpy(ciphertext, thread_data->ciphertext, PLAINTEXT_LENGTH + 1);

    printf("Thread %d - Started\n", thread_data->thread_id);

    for (uint64_t key = start_key; key < end_key; key++)
    {
        if (++keys_checked % 10000000 == 0)
        {
            // Print the percentage of the keyspace that has been processed
            printf("Thread %d - Keys checked: %lu/%lu, Progress: %.4f%%\n", thread_id, keys_checked, keyspace_per_thread, (double)(key - start_key) / (end_key - start_key) * 100);
        }

        for (int i = 0; i < KEY_LENGTH; i++)
            current_key[i] = (key >> (8 * i)) & 0xFF;

        rc4_init(current_key, KEY_LENGTH, state);
        rc4_crypt(ciphertext, decrypted_text, PLAINTEXT_LENGTH, state);

        int isValid = 1;

        for (int i = 0; i < PLAINTEXT_LENGTH; i++)
        {
            if (decrypted_text[i] < 32 || decrypted_text[i] > 126)
            {
                // The decrypted text contains non-printable ASCII characters
                // This key is not valid, so we skip the rest of the loop
                isValid = 0;
                break;
            }
        }

        if (!isValid)
            continue;

        printf("Key found: ");

        for (int i = 0; i < KEY_LENGTH; i++)
            printf("%02X", current_key[i]);

        printf("\nPlaintext: %s\n", decrypted_text);

        // We found the key, so we can terminate the program completely.
        exit(0);    
    }

    printf("Thread %d - Finished\n", thread_id);

    return NULL;
}

int main(void) {
    unsigned char key[KEY_LENGTH] = { 0 };
    unsigned char state[STATE_LENGTH] = {0};
    unsigned char plaintext[PLAINTEXT_LENGTH + 1] = "This is a very secret message from general Kenobi, only the chosen one can read it.";
    unsigned char ciphertext[PLAINTEXT_LENGTH + 1] = {0};

    // Seed the random number generator
    srand(time(NULL));

    // Randomly generate a key
    for (int i = 0; i < KEY_LENGTH; i++)
        key[i] = rand() % 256;

    // Encrypt the plaintext
    rc4_init(key, KEY_LENGTH, state);
    rc4_crypt(plaintext, ciphertext, PLAINTEXT_LENGTH, state);

    // Print the ciphertext
    printf("Ciphertext: ");

    for (int i = 0; i < PLAINTEXT_LENGTH; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");

    printf("Starting brute force attack...\n");
    printf("Number of threads: %d\n", NUM_THREADS);
    printf("Keyspace bits: %d bits\n", KEYSPACE_BITS);

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    uint64_t keyspace_per_thread = (1ULL << KEYSPACE_BITS) / NUM_THREADS;
    uint64_t start_key = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].start_key = start_key;
        thread_data[i].end_key = start_key + keyspace_per_thread - 1;
        thread_data[i].thread_id = (i + 1);
        memcpy(thread_data[i].ciphertext, ciphertext, PLAINTEXT_LENGTH + 1);
        start_key += keyspace_per_thread;
        pthread_create(&threads[i], NULL, brute_force_thread, (void *)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
