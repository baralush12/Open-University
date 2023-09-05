# Restaurant Menu Application

This project provides a simple restaurant menu application with a graphical user interface using JavaFX.

## Overview

The application allows users to select items from a menu, place an order, and view the details of their order. The menu items are loaded from a text file, and the order details are saved to a file.

## Classes

### 1. Item

Represents a single item on the restaurant menu, with attributes such as name, description, type, and price.

### 2. Main

The main class that launches the JavaFX application.

### 3. Menu

Stores a collection of `Item` objects to represent the entire restaurant menu.

### 4. MenuController

Controls the behavior of the UI. It handles loading the menu from a file, adding items to the order, and managing the "Order" button click event.

### 5. Order

Stores the current user's order, including their name, ID, and a map of `Item` objects to quantities.

## Features

- **Interactive UI**: Users can select items from a menu and view their order details.
- **File I/O**: Menu items are loaded from a text file, and order details are saved to a file.
- **Order Management**: Users can place an order, view the details, update the order, or clear it.

## How to Run

1. Compile all the classes.
2. Run the `Main` class to launch the Restaurant Menu application.
3. Select items from the menu and place an order.
