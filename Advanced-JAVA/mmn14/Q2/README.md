# Reminder Application

This application allows users to save and retrieve reminders for specific dates. It uses JavaFX for the graphical user interface and Java's serialization mechanism to persist reminders to a file.

## Overview

The application provides a user-friendly interface where users can select a date, type in a reminder, and either save it to a file or retrieve a previously saved reminder for a given date.

## Classes

### 1. Date

Represents a date with day, month, and year attributes. Implements the `Serializable` interface to allow for serialization and deserialization.

### 2. Main

The main driver class that launches the JavaFX application.

### 3. ReminderController

Defines the actions to be taken when the user interacts with the GUI. Manages a `HashMap` of reminders and persists it to a file.

## Features

- **Date Selection**: Users can select a day, month, and year using combo boxes.
- **Reminder Input**: A text area is provided for users to type in their reminders.
- **File Persistence**: Reminders are saved to a `.ser` file specified by the user.
- **Reminder Retrieval**: Users can retrieve a previously saved reminder for a specific date.
- **File Loading**: Users can load reminders from a previously saved file.

## How to Run

1. Compile all the classes.
2. Run the `Main` class to launch the application.
3. Use the GUI to save and retrieve reminders.
