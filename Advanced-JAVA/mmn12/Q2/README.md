# BigInt Arithmetic

This project provides a `BigInt` class that can handle arithmetic operations for integers of unlimited size.

## Overview

The `BigInt` class is designed to perform arithmetic operations such as addition, subtraction, multiplication, and division on large integers that exceed the standard integer data type limits.

## Classes

### 1. BigInt

- **Attributes**:

  - `digits`: An ArrayList storing the digits of the number.
  - `isNegative`: A flag indicating if the number is negative.

- **Methods**:
  - `plus()`: Adds two BigInt numbers.
  - `minus()`: Subtracts two BigInt numbers.
  - `multiply()`: Multiplies two BigInt numbers.
  - `divide()`: Divides two BigInt numbers.

### 2. Main

A driver class to test the functionality of the `BigInt` class. It prompts the user to input two large integers and then displays the results of various arithmetic operations.

## Features

- **Unlimited Integer Size**: The `BigInt` class can handle integers of any size.
- **Arithmetic Operations**: Supports addition, subtraction, multiplication, and division.
- **Error Handling**: Properly handles invalid inputs and division by zero.

## How to Run

1. Compile all the classes.
2. Run the `Main` class to input two large integers and view the results of the arithmetic operations.
