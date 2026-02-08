# Email Encryptor using Flex and C++
[![Ask DeepWiki](https://devin.ai/assets/askdeepwiki.png)](https://deepwiki.com/goliverosj/email-encryptor-flex-cpp)

This repository contains a C++ and Flex-based tool designed to find and encrypt email addresses within text files. It can also decrypt the previously encrypted emails.

## Features

*   **Email Detection**: Utilizes Flex to parse text files and identify email addresses based on a regular expression pattern.
*   **Simple Encryption**: Encrypts found emails using a Caesar cipher (character shift).
*   **Text Sanitization**: Creates a new version of the input file where emails are replaced with the placeholder `[correo oculto]`.
*   **Decryption**: Provides a mode to decrypt a file containing encrypted email addresses.

## How It Works

The project is composed of two main parts: a Flex file for lexical analysis and a C++ driver program.

1.  **`trabajoflex.l`**: This Flex file defines the rules for tokenizing the input text.
    *   A regular expression `[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}` is used to match email patterns.
    *   When an email is matched, it is encrypted using a simple `+3` character shift. The encrypted email is saved to `encriptados.txt`, and the original email in the main output stream is replaced by `[correo oculto]`.
    *   All other characters are passed through to the output file unchanged.

2.  **`main.cpp`**: This is the main C++ program that orchestrates the process.
    *   It accepts command-line arguments to switch between encryption and decryption modes.
    *   **Encryption Mode (`0`)**: Opens the source text file, initializes the Flex lexer, and runs the analysis. It generates `salida_modificada.txt` (the sanitized text) and `encriptados.txt` (the list of encrypted emails).
    *   **Decryption Mode (`1`)**: Reads a file of encrypted emails (e.g., `encriptados.txt`) and applies the reverse character shift (`-3`) to each line, saving the result to `desencriptados.txt`.

## Prerequisites

To compile and run this project, you will need:
*   A C++ compiler (e.g., g++)
*   Flex (The Fast Lexical Analyzer)

## Installation and Compilation

1.  Clone the repository:
    ```sh
    git clone https://github.com/goliverosj/email-encryptor-flex-cpp.git
    cd email-encryptor-flex-cpp
    ```

2.  Use Flex to generate the C source file from the `.l` definition:
    ```sh
    flex -o lex.yy.c trabajoflex.l
    ```

3.  Compile the C++ source and the generated Flex file, linking the Flex library (`-lfl`):
    ```sh
    g++ main.cpp lex.yy.c -o email_encryptor -lfl
    ```
    This will create an executable named `email_encryptor`.

## Usage

The program is operated via the command line with two arguments: an operation mode and an input file.

### Encrypt Emails

To scan a file for emails and encrypt them, use mode `0`.

**Syntax:**
```sh
./email_encryptor 0 <input_file.txt>
```

**Example:**
```sh
./email_encryptor 0 entrada.txt
```
This command will:
*   Read `entrada.txt`.
*   Create `salida_modificada.txt` with emails replaced by `[correo oculto]`.
*   Create `encriptados.txt` with the encrypted versions of the emails found.

### Decrypt Emails

To decrypt a file containing encrypted emails (like the `encriptados.txt` generated above), use mode `1`.

**Syntax:**
```sh
./email_encryptor 1 <encrypted_emails_file.txt>
```

**Example:**
```sh
./email_encryptor 1 encriptados.txt
```
This command will:
*   Read `encriptados.txt`.
*   Create `desencriptados.txt` with the decrypted, original email addresses.
