# Maman 13 Project Collection

#### By: Bar Aloush (314673849)

This repository showcases a collection of Python scripts, each demonstrating unique functionalities ranging from text manipulation to dynamic class creation.

---

## Table of Contents

1. [Forming Past Tense of Words (Q1-a)](#forming-past-tense-of-words-q1-a)
2. [Counting Rainy Months (Q1-b)](#counting-rainy-months-q1-b)
3. [Apple Basket Management (Q2-a)](#apple-basket-management-q2-a)
4. [Bank Account Management (Q2-b)](#bank-account-management-q2-b)
5. [Dynamic Class Creation (Q3-a)](#dynamic-class-creation-q3-a)
6. [Dynamic Method Extension (Q3-b)](#dynamic-method-extension-q3-b)

---

## Forming Past Tense of Words (Q1-a)

This script processes a list of words, converting them to their past tense by appending 'ed' or 'd' based on the word's ending.

**Note:** The script examines the last characters of each word to determine the appropriate past tense form.

---

## Counting Rainy Months (Q1-b)

Given a list of monthly rainfall data, this script calculates the number of months with rainfall exceeding 75.0 mm.

**Note:** Rainfall data is converted from string to float for accurate comparison.

---

## Apple Basket Management (Q2-a)

A Python class, `AppleBasket`, is introduced to manage apple baskets. The class provides functionalities to:

- Initialize an apple basket with a specific color and quantity.
- Increment the quantity of apples.
- Display the contents of the basket.

---

## Bank Account Management (Q2-b)

The `BankAccount` class offers a simple bank account management system. Features include:

- Initializing a bank account with an account holder's name and balance.
- Displaying account details in a formatted string.

---

## Dynamic Class Creation (Q3-a)

This interactive script facilitates the dynamic creation of classes during runtime. Users can:

- Specify a new class name.
- Choose a base class for inheritance.
- Define methods and attributes for the new class.

**Defensive Programming Features:**

- Validation for alphabetic class names.
- Checks for unique class names to prevent overwriting.
- Verification of the existence of specified base classes.
- Automatic capitalization for class naming consistency.

---

## Dynamic Method Extension (Q3-b)

This advanced script allows users to dynamically extend methods of classes within a specified Python file by injecting user-provided code snippets.

**Steps to Run:**

1. Execute the script.
2. Provide the name of the target Python file.
3. Input the desired Python code snippet to be added to the class methods.

**Defensive Programming Features:**

- File extension validation to ensure `.py` files.
- File existence verification.
- Code snippet length limitation and risky function call detection.
