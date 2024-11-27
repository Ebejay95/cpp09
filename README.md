# C++ Module 09

**Standard Template Library (STL)**

This module focuses on advanced usage of the Standard Template Library (STL) in C++ to solve problems using containers and algorithms efficiently.

## Structure

### ex00/ - Bitcoin Exchange
- **BitcoinExchange.{hpp,cpp}**: Implements a program that:
  - Reads a CSV database of Bitcoin prices over time.
  - Processes a second input file with dates and values to calculate the corresponding Bitcoin value based on the closest available date.
  - Outputs errors for invalid dates, values, or file handling.
- **main.cpp**: Entry point for testing Bitcoin value calculations.

### ex01/ - Reverse Polish Notation (RPN)
- **RPN.{hpp,cpp}**: Implements a program that:
  - Processes a Reverse Polish Notation (RPN) expression.
  - Supports basic arithmetic operations (`+`, `-`, `*`, `/`).
  - Validates input and handles errors gracefully.
- **main.cpp**: Tests the RPN evaluator with various expressions.

### ex02/ - PmergeMe
- **PmergeMe.{hpp,cpp}**: Implements a program that:
  - Sorts a sequence of positive integers using the Ford-Johnson merge-insertion sort algorithm.
  - Uses two distinct STL containers to compare performance.
  - Handles at least 3000 integers and outputs performance timing for each container.
- **main.cpp**: Tests the sorting algorithm with small and large datasets.

## Features

- **STL Containers and Algorithms**:
  - Uses containers like `std::vector`, `std::stack`, and others.
  - Employs STL algorithms for efficient operations.
- **Error Handling**:
  - Validates input formats and manages errors for invalid data or operations.
- **Performance Metrics**:
  - Measures and displays execution time for sorting operations.
