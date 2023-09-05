# Alarm System

This project provides an alarm system that can handle different types of alarms, including smoke, fire, and elevator alarms.

## Overview

The system is designed to be extensible, allowing for the addition of new alarm types in the future. Each alarm type has its specific behavior and attributes.

## Classes

### 1. Alarm (Abstract Class)

- **Attributes**:

  - `address`: The location of the alarm.
  - `operatorName`: The name of the operator handling the alarm.
  - `startTime`: The time when the alarm started.
  - `active`: Indicates if the alarm is active or not.

- **Methods**:
  - `action()`: An abstract method that defines the action to be taken when the alarm is triggered.

### 2. BadAlarmException

A custom exception class to handle invalid alarm configurations.

### 3. Elevator

- **Attributes**:

  - `floor`: The floor where the elevator alarm was triggered.

- **Methods**:
  - `action()`: Provides information about the elevator alarm.
  - `reset()`: Resets the floor attribute.

### 4. Fire

A subclass of `Smoke` that represents a fire alarm.

### 5. Smoke

- **Attributes**:

  - `alertTime`: The time when the smoke was detected.

- **Methods**:
  - `action()`: Provides information about the smoke alarm.

### 6. TestAlarms

A class to test the functionality of the alarm system.

- **Methods**:
  - `process()`: Processes a list of alarms, performing the necessary actions for each type.
  - `main()`: The main method to run the test.

## Features

- **Extensibility**: New alarm types can be easily added to the system.
- **Dynamic Behavior**: Each alarm type has its specific behavior defined in the `action()` method.
- **Custom Exception Handling**: The system can handle invalid alarm configurations using the `BadAlarmException` class.

## How to Run

1. Compile all the classes.
2. Run the `TestAlarms` class to test the functionality of the alarm system.
