# Cash Register System

This project simulates a cash register system with functionalities to manage items, purchases, and transactions.

## Classes Overview

### 1. CashReg

This class represents the main cash register system.

- **Attributes**:
  - `cashTotal`: Represents the total amount of cash in the register.
  - `currentPurchaseTotal`: Represents the total cost of the current purchase.
  - `currentPurchase`: A list of `LineInInvoice` objects representing the current purchase.
  - `allPurchases`: A list of `LineInInvoice` objects representing all purchases in the cash register.

### 2. Item

This class represents an item that can be purchased.

- **Attributes**:
  - `name`: Name of the item.
  - `price`: Price of the item.

### 3. LineInInvoice

This class represents a single line item in an invoice.

- **Attributes**:
  - `item`: An object representing the item being purchased.
  - `quantity`: Represents the number of units of the item being purchased.

### 4. Main

This class demonstrates the functionality of the cash register system, allowing the user to interact with the system, make purchases, and view their cart.

## Features

- **List Available Items**: Displays a list of available items for purchase.
- **Add Items to Cart**: Allows users to add items to their cart.
- **View Cart**: Displays the items in the user's cart.
- **Make Payment**: Allows users to make a payment and calculates the change to be returned.
- **View Invoice**: Displays the invoice details for the user's purchase.
- **View Total Register Amount**: Displays the total amount in the cash register.

## How to Run

1. Initialize the `CashReg` object.
2. Use the `addItem` method to add items to the current purchase.
3. Use the `getPayment` method to process the payment and get the change.
4. Use the `getInvoiceDetails` method to view the invoice details.
5. Use the `getCashTotal` method to view the total amount in the cash register.
