# Minishell

Minishell is a simplified version of a Unix shell built in **C** as part of the **42 School curriculum**. The objective of this project is to recreate a command-line interpreter with features like command execution, pipes, redirections, and environment variable handling, providing a deeper understanding of how shells work.

## Table of Contents
- [Project Description](#project-description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Authors](#authors)

## Project Description

Minishell allows users to run basic Unix commands, handle input/output redirection, and chain commands using pipes, simulating the behavior of a real shell. The project emphasizes system calls, process management, and signal handling, offering a hands-on approach to understanding the inner workings of a shell.

## Features

- Executes basic shell commands.
- Supports piping (`|`) and redirection (`>`, `<`, `>>`).
- Handles environment variables.
- Built-in commands: `cd`, `echo`, `pwd`, `env`, `exit`, etc.
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`).

## Installation

Clone the repository and compile the project:

```bash
git clone https://github.com/ashleyfletcher76/MiniShell.git
cd minishell
make
```

## Usage
```bash
./minishell
```
## Authors

- **Ashley Fletcher** - *Developer* - [GitHub Profile](https://github.com/ashleyfletcher76)
- **Muhammet Köse** - *Developer* - [GitHub Profile](https://github.com/masummmm54)
