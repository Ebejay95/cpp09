# C++ Module 09

**STL (Standard Template Library)**

This module focuses on practical applications of STL containers and algorithms in C++.

## Structure

### ex00/ - Bitcoin Exchange
- **BitcoinExchange.{hpp,cpp}**: Implements functionality to read and process bitcoin price data from a CSV database.
- **main.cpp**: Program that takes an input file with date and value pairs, calculates the bitcoin value based on exchange rates, and handles various error cases.
- Key features:
  - CSV file parsing
  - Date validation and lookup
  - Error handling for invalid inputs
  - Value calculation with appropriate exchange rates

### ex01/ - Reverse Polish Notation (RPN)
- **RPN.{hpp,cpp}**: Implements a calculator for Reverse Polish Notation expressions.
- **main.cpp**: Processes RPN expressions provided as command-line arguments.
- Key features:
  - Stack-based expression evaluation
  - Support for basic operations: +, -, *, /
  - Error handling for invalid expressions

### ex02/ - PmergeMe
- **PmergeMe.{hpp,cpp}**: Implements the Ford-Johnson merge-insertion sort algorithm using different containers.
- **main.cpp**: Sorts a sequence of positive integers and compares performance between two container implementations.
- Key features:
  - Implementation of merge-insertion sort
  - Performance comparison between different STL containers
  - Handling large datasets (3000+ integers)
  - Time measurement for algorithm analysis

## Requirements

- Each exercise must use at least one STL container, and each container can only be used once throughout the module.
- Exercise 02 must use at least two different containers.
- All programs must include proper error handling.
- Code must compile with C++98 standard and flags: `-Wall -Wextra -Werror`.
- All classes must be designed in Orthodox Canonical Form.
- Each program requires a Makefile with standard rules (NAME, all, clean, fclean, re).

## Features

- **Container Utilization**: Each exercise demonstrates practical use of different STL containers.
- **Data Processing**: Implementations for handling real-world data formats and calculations.
- **Algorithm Optimization**: Performance comparison between different container implementations.
- **Error Management**: Robust error handling for various input scenarios.
