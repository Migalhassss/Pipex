# Pipex

## Overview

`Pipex` is a custom implementation of a shell command that simulates the behavior of the shell pipe (`|`) in the C programming language. This project is designed to help you understand how shell pipes work internally and how to create pipelines of processes in a Unix-like environment.

This repository contains the source code for the `pipex` program, along with usage instructions and a brief overview of its features.

## Table of Contents

- [Features](#features)
- [Usage](#usage)
- [Prerequisites](#prerequisites)
- [Building Pipex](#building-pipex)
- [Running Pipex](#running-pipex)
- [Example Usage](#example-usage)
- [Acknowledgments](#acknowledgments)
- [Support](#support)

## Features

- Simulates the behavior of shell pipes (`|`) in a custom C program.
- Enables you to create pipelines of processes to process data.
- Provides a simple but educational example of process management in Unix-like systems.
- Compatible with Unix-like systems (Linux, macOS).

## Usage

### Prerequisites

Before using `Pipex`, you need to have a C compiler (e.g., GCC) and a Unix-like operating system (e.g., Linux, macOS).

### Building Pipex

1. Clone this repository or download the source code.

2. Open a terminal and navigate to the project's root directory.

3. Build the `pipex` program using a C compiler (e.g., GCC):

    ```bash
    make
    ```
    to bonus
    ```bash
    make bonus
    ```

### Running Pipex

To run `pipex`, you need to provide two input files and two commands. The general syntax for running `pipex` is as follows:

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1`: Input file whose contents will be sent as input to the first command (cmd1).
- `cmd1`: First command to be executed.
- `cmd2`: Second command to be executed.
- `file2`: Output file where the result of cmd2 will be written.

## Example Usage

  Here's an example of how to use `pipex` to simulate a shell command pipeline that counts the number of lines in a text file using the `wc` command:

  ```bash
  ./pipex file.txt "cat" "wc -l" output.txt
  ```
  This command reads the contents of `file.txt` using `cat`, and then pipes the output to `wc -l` to count the number of lines. The result is written to `output.txt`.

## Acknowledgments
  This project was inspired by the need for a simple, educational example of shell command pipelines in C. It is meant to serve as a starting point for those interested in learning about process management and Unix-like systems.

  ## Support 

If you have any questions, encounter issues, or need assistance with the libft project, please feel free to open an issue on GitHub. Im here to help and improve the library together
