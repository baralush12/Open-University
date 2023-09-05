# Sudoku Game

This project provides a simple Sudoku game with a graphical user interface using JavaFX.

## Overview

The game allows users to input numbers into a Sudoku board and checks if the numbers are valid according to Sudoku rules. The board can be cleared, and initial numbers can be set.

## Classes

### 1. Main

The main class that launches the JavaFX application.

### 2. Sudoku

- **Attributes**:

  - `SIZE`: The size of the Sudoku board (3x3 in this case).
  - `board`: A 2D array representing the Sudoku board.

- **Methods**:
  - `getCell()`: Returns the value of a cell.
  - `setCell()`: Sets the value of a cell.
  - `isAllowed()`: Checks if a number can be placed in a cell.
  - `clearBoard()`: Clears the Sudoku board.

### 3. SudokuController

Manages user interactions and updates the UI.

- **Attributes**:

  - `sudoku`: An instance of the Sudoku class.
  - `setButtonPressed`: A flag indicating if the set button was pressed.
  - `SIZE`: The size of the Sudoku board.
  - `CELL`: The size of a cell in the UI.

- **Methods**:
  - `initialize()`: Initializes the Sudoku board UI.
  - `createBoard()`: Creates the Sudoku board UI.
  - `getBackgroundColor()`: Returns the background color for a cell.
  - `handleInput()`: Handles user input into a cell.
  - `handleSetButton()`: Handles the set button click.
  - `handleClearButton()`: Handles the clear button click.
  - `showAlert()`: Displays an alert to the user.

## Features

- **Interactive UI**: Users can input numbers into the Sudoku board using a graphical interface.
- **Validation**: Checks if the numbers input by the user are valid according to Sudoku rules.
- **Clear & Set**: Allows users to clear the board or set initial numbers.

## How to Run

1. Compile all the classes.
2. Run the `Main` class to launch the Sudoku game.
