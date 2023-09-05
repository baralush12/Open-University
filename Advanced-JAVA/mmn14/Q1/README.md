# Sorted Group Application

This project demonstrates the use of a generic `SortedGroup` class to maintain an ordered collection of `Comparable` elements. The primary use case demonstrated is the management of a group of `Student` objects.

## Overview

The application showcases the addition, removal, and reduction operations on a `SortedGroup` of `Student` objects. Students are added to the group in a sorted manner based on their scores. The group can be reduced to only include students with scores above a certain threshold.

## Classes

### 1. Main

The main driver class that demonstrates the usage of `SortedGroup` and `Student` classes.

### 2. SortedGroup<T>

A generic class representing an ordered collection of `Comparable` elements. It provides methods to add, remove, and iterate over the elements.

### 3. SortedGroupRed

Provides a static method to produce a reduced `SortedGroup` based on a given threshold.

### 4. Student

Represents a student with attributes such as name, identification document, and score. Implements the `Comparable` interface to allow for sorting based on the student's score.

## Features

- **Generic Sorted Group**: The `SortedGroup` class is generic and can hold any type of `Comparable` elements.
- **Ordered Insertion**: Elements are added to the `SortedGroup` in a sorted manner.
- **Reduction**: The `SortedGroupRed` class provides functionality to reduce a `SortedGroup` based on a given threshold.
- **Student Management**: The application demonstrates the management of `Student` objects, including adding them to a group, removing them, and reducing the group based on score.

## How to Run

1. Compile all the classes.
2. Run the `Main` class to see the demonstration of the `SortedGroup` and `Student` classes in action.
