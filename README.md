# CMPUT 275 - Tangible Computing II 

This repository contains materials and resources for the CMPUT 275 course (Tangible Computing 2) at the University of Alberta, Winter 2025 term.

## Course Overview
This is part 2 of a 2 sequence intensive introduction to Computing Science. Part 2 expands to add object-oriented programming, with C++, and more complex algorithms and data structures such as shortest paths in graphs; divide and conquer and dynamic programming; client-server style computing; and recursion. 

## Course Topics

### The Shell
- Executing commands
- I/O Streams and Redirection
- Pipelines
- File Permissions
- PATH Variable
- Shell Scripts
- Make files

### The C Programming Language
- Compilation, and compilation tool chain
- Static typing
- Pointers
- C I/O
- Object Lifetime
- Memory Model and Management
- Structures

### The C++ Programming Language
- C++ I/O
- C++ Memory Management
- References
- Operator overloading
- Classes
- The Big 5
- Memory management with objects
- Methods
- Inheritance
- STL Classes
- Exceptions and Exception Safety
- Templates

## Assignments
1. **Assignment 1: Introduction to Bash Scripting and File Handling**  
   In this assignment, students will be introduced to the basics of bash scripting and file manipulation. The focus will be on creating scripts to automate the testing process, handle input and output files, and compare results with expected outputs. Students will work with bash scripts, C programming, and gain experience in automating tasks related to test execution and file management. The assignment includes exercises on using conditional statements, loops, and error handling in scripts.

2. **Assignment 2: Credit Card Verification, Roman Numerals, and Wordl**  
   - **Credit Card Verification**: Implement Luhn's algorithm to validate credit card numbers using a checksum method. The program should read an account number from input and print whether it is valid or invalid. The challenge is to solve it without using arrays or pointers.
   - **Roman Numerals**: Write a program to convert simplified Roman numerals into Arabic numerals using a set of predefined rules for numeral positioning and subtraction.
   - **Wordl**: Develop a word-guessing game similar to Wordle. The game should provide colorized feedback based on letter positions and allow six attempts for the user to guess the correct word.

3. **Assignment 3: Reverse Polish Notation, Integer Sets, and Image Translation**  
   - **Reverse Polish Notation**: Implement an interpreter for arithmetic expressions using reverse polish notation (postfix).  
   - **Integer Sets**: Create and manipulate sets of integers, supporting operations like insertion, deletion, union, and intersection.  
   - **Image Translation**: Process and modify PPM images, applying transformations such as flipping and a sepia filter.
   
4. **Assignment 4: Linear Sequences and Maze Game**  
   - **Linear Sequences**: Write a C program `sequences.c` that reads pairs of arithmetic operators (`add`, `sub`, `mul`, `div`) and operands from standard input. These operators are applied sequentially to produce a linear numeric sequence. When the special input `n` is encountered, the next number in the sequence is computed and printed.
   - **Maze Game**: Implement an Abstract Data Type (ADT) to represent a maze using the provided header file `maze.h`. Your implementation (`maze.c`) must handle various maze tiles including start (`S`), goal (`G`), open (`O`), wall (`X`), teleporter (`0-9`), and icy tiles (`I`). The player moves based on inputs (`n`, `e`, `s`, `w`) and special tiles affect gameplay dynamics, such as teleportation and sliding movements.

5. **Assignment 5: Game of Life, Integer Set ADT, and Reflection**  
   - **Conway’s Game of Life**: Implement Conway’s Game of Life, a cellular automaton on a grid where each cell can be alive (`O`) or dead (`.`). Based on neighbor counts, each cell changes state following simple rules: underpopulation, overpopulation, reproduction, and survival. Commands include `s` for stepping to the next state and `p` for printing the current grid.  
   - **Integer Set ADT**: Create a full ADT for sets of integers without using STL containers or smart pointers. Implement deep copy constructors and assignment, move constructors and assignment (in constant time), and manual memory management with dynamic arrays that grow by doubling. Support operations include add, remove, union (`|`), intersection (`&`), equality (`==`), subset checks, and printing.  
   - **Reflection**: Write a simple program that prints three things you enjoyed about learning C and/or C++ this term.

## License
All materials and code in this repository are for personal study purposes only.
