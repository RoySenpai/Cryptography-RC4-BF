# Introduction to Cryptography Assignment 1

### For Computer Science B.S.c Ariel University

**By Roy Simanovich and Chen Dahan**

## Description

This assignment is about the basics of cryptograppy. We encrypted some text using the RC4 algorithm with a 32 bit key, and then try to brute force the key. We chose 32 bit key instead of 40 bit key like the assignment asked, because it was too hard to brute force the 40 bit key in a reasonable time, even with the help of multithreading, on a regular laptop. The code is compatible for both Linux and Windows, and it is written in C.

### Settings

You can change the settings of the program in the `RC4_settings.h` file. You can change the number of threads, the length of the key, and the encrypted text.

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
