# Introduction to Cryptography Assignment 1

### For Computer Science B.S.c Ariel University

**By Roy Simanovich and Chen Dahan**

## Description

This assignment is about the basics of cryptograppy. We encrypted some text using the RC4 algorithm with a 32 bit key, and then try to brute force the key. We chose 32 bit key instead of 40 bit key like the assignment asked, because it was too hard to brute force the 40 bit key in a reasonable time, even with the help of multithreading, on a regular laptop. The code is compatible for both Linux and Windows, and it is written in C.

### Settings

You can change the settings of the program in the `RC4_settings.h` file. You can change the number of threads, the length of the key, and the encrypted text.

The following settings are available:
- `PLAINTEXT_LENGTH` - The length of the plaintext. The plaintext is defined in the `RC4_attack.c` file, and it is the text that will be encrypted and then decrypted with the brute forced key.
- `KEY_LENGTH` - The length of the key.
- `NUM_THREADS` - The number of threads to use for the brute force, the more threads, the faster the brute force will be, as each thread will cover a smaller chunk of the keyspace, and it increases the chance of finding the correct key faster.


### Components
#### RC4 Library
The RC4 library is a simple implementation of the RC4 algorithm. It has the following functions:
- `void rc4_init(unsigned char *key, int key_length, unsigned char *state)` - Initialize the RC4 state with the given key.
- `void rc4_crypt(unsigned char *input, unsigned char *output, int input_length, unsigned char *state)` - Encrypt or decrypt the input with the given state.

#### Random Key Generator
The random key generator is a simple implementation of a random key generator by using `RDSEED` or `RDRAND` instructions if they are available, and if not, it uses the `rand()` function as a fallback. The random key generator has the following function:
- `UintRand rand64(void)` - Generate a random 64/32 bit number, depending on the system, and using the `RDSEED` or `RDRAND` instructions if they are available or the `rand()` function with seed of the current time as a fallback.

## Requirements

- Linux or Windows machine
- GNU Compiler Collection (GCC)
- Make

## How to use

1. Clone the repository:

```
git clone https://github.com/RoySenpai/Cryptography-RC4-BF.git
```

2. Compile the code:

```
make all
```

3. Run the code:

- On Windows:

```
RC4_attack.exe
```

- On Linux:

```
./RC4_attack
```

4. The program will print the key and the decrypted text, and also show the progress of the brute force.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details
