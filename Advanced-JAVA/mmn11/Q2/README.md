# Weather Visualization Application

This JavaFX application visualizes average monthly temperatures for different years using bar charts.

## Overview

The application provides a graphical representation of average temperatures for each month from the years 2017 to 2022. The user can navigate through different years to view the temperature distribution.

## Components

### 1. Graphic.fxml

This XML file defines the layout of the application. It contains:

- A **Button** to navigate to the next year.
- A **Canvas** to draw the bar chart.

### 2. Graphic

This is the main class that initializes and launches the JavaFX application.

### 3. GraphicController

This class handles the logic and rendering of the bar chart.

- **Attributes**:

  - `temperatures`: A 2D array containing average temperatures for each month from 2017 to 2022.
  - `months`: An array of month numbers.
  - `maxTemp` and `minTemp`: Constants representing the maximum and minimum temperatures.
  - `currYear`: Keeps track of the current year being displayed.
  - `tempRange`: The range of temperatures.
  - `canv`: The canvas where the bar chart is drawn.
  - `gc`: Graphics context for drawing on the canvas.

- **Methods**:
  - `initialize()`: Initializes the graphics context and creates the initial bar chart.
  - `createBar()`: Renders the bar chart for the current year.
  - `nextYear()`: Updates the `currYear` and redraws the bar chart.

## Features

- **Dynamic Visualization**: The bar chart updates dynamically as the user navigates through different years.
- **Color-coded Bars**: The bars are color-coded based on temperature values. The highest temperature is represented in red, the lowest in blue, and others in gray.
- **Year and Month Labels**: The chart displays labels for years and months for better clarity.

## How to Run

1. Ensure you have JavaFX set up in your development environment.
2. Compile and run the `Graphic` class.
3. Use the "Next Year" button to navigate through different years and view the temperature distribution.
