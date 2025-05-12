# Minishell - A Simplified Bash

Minishell is a simplified shell implementation developed as a project for the [42 São Paulo](https://www.42sp.org.br/) Common Core curriculum. It replicates basic functionalities of a Unix shell, such as executing commands, handling pipes, redirections, and managing signals, while providing an interactive command-line interface. Built in C, Minishell aims to mimic the behavior of Bash, focusing on process management, input parsing, and environment variable handling.

**Credits:**
- [Luiz Gandra](https://github.com/LuizGandra)
- [Luiz Henrique](https://github.com/lhenriqu42)
*This project was a collaborative effort for the 42 São Paulo curriculum.*

![42 São Paulo](https://img.shields.io/badge/42-São_Paulo-black?style=flat-square&logo=42)

## About 42

[42 São Paulo](https://www.42sp.org.br/) is a tuition-free, global coding school emphasizing peer-to-peer learning and project-based education. This project sharpens algorithmic thinking and optimization skills in C.

## Project Overview

Minishell is a single program that provides an interactive command-line interface to execute commands, manage environment variables, and handle input/output redirections. It is divided into:
- **Mandatory Part:** implements a shell with command execution, built-in commands, pipes, redirections, and signal handling.
- **Bonus Part:** adds advanced features like logical operators (&&, ||), wildcard expansion (*), and command grouping with parentheses `()`.

### Key Features

- **Command Execution**: runs external commands using `execve`, resolving paths via `PATH`.
- **Built-in Commands**:
  - `echo`: prints text, with `-n` option support.
  - `cd`: changes directories (relative/absolute paths).
  - `pwd`: displays the current working directory.
  - `export`: sets or lists environment variables.
  - `unset`: removes environment variables.
  - `env`: displays environment variables.
  - `exit`: exits the shell with a status code.
- **Pipes**: supports pipelines (e.g., `ls | grep txt`) with proper subprocess and file descriptor management.
- **Redirections**: handles `<`, `>`, `>>`, and heredoc (`<<`) for input/output.
- **Environment Variables**: expands variables (e.g., `$HOME`) and manages the environment.
- **Signal Handling**: manages `Ctrl+C` (new prompt), `Ctrl+D` (exit), and ignores `Ctrl+\`.
- **Error Handling**: outputs "Error" for invalid inputs, syntax errors, or file issues.
- **Bonus Features**:
  - Logical operators (`&&`, `||`) for conditional execution.
  - Wildcard (`*`) expansion for file matching.
  - Parentheses `()` for command grouping.

### Restrictions

- Written in C, compliant with the 42 Norm.
- No unexpected crashes (e.g., segmentation faults).
- No memory leaks from heap allocations.
- Compiled with `-Wall -Wextra -Werror`.
- Uses the `readline` library for input handling.

## Getting Started

### Prerequisites

- C compiler (e.g., `gcc` or `clang`).
- `make` utility.
- `readline` library:
  - Debian/Ubuntu: `sudo apt-get install libreadline-dev`
  - macOS: `brew install readline`

### How to Build and Run

1. Clone the repository:

   ```bash
   git clone https://github.com/LuizGandra/minishell.git
   cd minishell
   ```

2. Build the mandatory part:

   ```bash
   make
   ```

3. Run `minishell`:

   ```bash
   ./minishell
   ```

4. Build the bonus part (optional):

   ```bash
   make bonus
   ```

5. Exit the shell with `exit` or `Ctrl+D`.

#### Additional commands

- `make clean`: remove object files.
- `make fclean`: remove the program and object files.
- `make re`: rebuild everything.

## Project Structure

- `include/*.h`: header files.
- `src/main.c`: main entry point of the program.
- `src/builtins/*.c`: source files for built-in command implementations (e.g., echo.c, cd.c).
- `src/exec/*.c`: source files for command execution logic (e.g., exec.c).
- `src/expander/*.c`: source files for variable expansion and wildcard handling (e.g., expander.c).
- `src/lexing/*.c`: source files for tokenization and syntax analysis and validation (e.g., lexer.c).
- `src/parser/*.c`: source files for command parsing and tree building (e.g., parser.c).
- `src/signals/*.c`: source files for signal handling (e.g., signals.c).
- `src/utils/*.c`: utility functions (e.g., string handling, memory management).
- `Makefile`: compilation automation.
- `libs/libft/`: directory for the libft library.

## License

This project is part of the 42 curriculum and intended for educational use.
