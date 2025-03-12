# Libft

Libft is my custom C library, featuring a personal implementation of several common functions in C.  
The Makefile compiles the code and generates the `libft.a` file, which can be used in other projects.  

**Note:** Some functions rely on `<unistd.h>`, so this code is not compatible with Windows.

## How to Compile

1. Clone this repository:
   ```bash
   git clone https://github.com/lhenriqu42/libft
   ```

2. Navigate to the repository folder:
   ```bash 
   cd libft
   ```

3. Compile the code using Make build:
   ```bash
   make build
   ```

## How to Use

1. Include the `libft.h` header file in your code:
   ```c
   #include "libft.h"
   ```
   Ensure the libft.h file is in the root of your project directory, or provide its absolute path when including it.

2. Link the `libft.a` file during compilation with your C compiler. For example:
   ```bash
   gcc your_program.c -L. -lft -o your_program
   ```
   Here, -L. specifies the directory containing libft.a (current directory), and -lft links the libft.a library.
