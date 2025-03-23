
# z80asm: The Z80 Macro Assembler

`z80asm` is a powerful macro assembler for the Zilog Z80 microprocessor, developed by Bas Wijnen. It provides a flexible and efficient way to write assembly code for Z80-based systems, with support for macros, conditional assembly, and more.

- - -

## Table of Contents

1.  Installation
2.  Usage
3.  Testing
4.  Contributing
5.  License
    

- - -

## Installation

### Prerequisites

*   **CMake** (version 3.10 or higher)
*   **C Compiler** (e.g., GCC, Clang)
*   **gettext** (for localization support, optional)
    

### Steps

1.  Clone the repository:
    ```    
    git clone https://github.com/lvitals/z80asm.git
    cd z80asm
    ```
    
2.  Create a build directory and configure the project:
    ```
    mkdir build
    cd build
    cmake ..
    ```
    
3.  Build the project:
    ```
    make
    ```
    
4.  Install the executable (optional):
    ```
    sudo make install
    ```

    This will install `z80asm` to `/usr/local/bin` by default.
    

- - -

## Usage

### Assembling a File

To assemble a `.asm` file, use the following command:

```
z80asm -I /usr/local/share/z80asm/headers your_file.asm -o output.bin
```

*   `-I`: Specifies the directory for include files.
*   `-o`: Specifies the output file.
    

### Example

```
z80asm -I /usr/local/share/z80asm/headers example.asm -o example.bin
```
- - -

## Testing

The project includes a test suite to verify the functionality of `z80asm`. To run the tests:

1.  Build the project (if not already built):
    
    ```
    mkdir build
    cd build
    cmake ..
    make
    ```
    
2.  Run the tests using `ctest`:
    
    ```
    ctest -V
    ```
    
    The `-V` flag enables verbose output, so you can see the detailed results of each test.
    

### Test Files

The test files are located in the `tests` directory. Each test consists of:

*   An `.asm` file (input).
*   A `.correct-bin` file (expected binary output).
*   A `.correct-err` file (expected error output).
    

The test script compiles each `.asm` file and compares the output with the expected results.

- - -

## Contributing

Contributions are welcome! If you'd like to contribute to `z80asm`, please follow these steps:

1.  Fork the repository.
2.  Create a new branch for your feature or bugfix.
3.  Make your changes and commit them.
4.  Submit a pull request with a detailed description of your changes.
    

- - -

## License

`z80asm` is licensed under the **GNU General Public License (GPL)**. See the [LICENSE](GPL3) file for more details.

- - -

## Acknowledgments

*   **Bas Wijnen**: Original author of `z80asm`.
*   Contributors: Everyone who has contributed to the development of this project.

- - -

For more information, visit the [official website](http://www.nongnu.org/z80asm).

- - -

This `README.md` provides a clear and concise guide for users to install, use, and test `z80asm`. Let me know if you need further adjustments!