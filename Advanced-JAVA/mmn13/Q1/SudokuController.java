/*
 * Manages user interactions and UI updates.
 */

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;

public class SudokuController {
    private final Sudoku sudoku = new Sudoku();
    private boolean setButtonPressed = false;
    final int SIZE = 3;
    final int CELL = 40;
    
    @FXML
    private GridPane grid;

    @FXML
    private Button setButton;

    @FXML
    private Button clearButton;

    @FXML
    public void initialize() {
        createBoard();
    }

    private void createBoard() {
        for (int row = 0; row < SIZE * SIZE; row++) {
            for (int col = 0; col < SIZE * SIZE; col++) {
                TextField textField = new TextField();
                textField.setPrefWidth(CELL);
                textField.setPrefHeight(CELL);
                textField.setMaxWidth(CELL);
                textField.setMaxHeight(CELL);
                textField.setStyle("-fx-padding: 0; -fx-alignment: center;");

                textField.setStyle("-fx-padding: 0; -fx-alignment: center;" +
                        " -fx-background-color: " + getBackgroundColor(row, col) + ";");
                
                int finalRow = row;
                int finalCol = col;
                textField.setOnAction(event -> handleInput(finalRow, finalCol, textField));
                grid.add(textField, col, row);
            }
        }
    }
    
    private String getBackgroundColor(int row, int col) {
        int blockRow = row / SIZE;
        int blockCol = col / SIZE;
        return (blockRow % 2 == blockCol % 2) ? "#F0F0F0" : "#D0D0D0";
    }

    private void handleInput(int row, int col, TextField textField) {
    	 if (setButtonPressed) {
    	        showAlert("Error", "You cannot change the initial numbers.");
    	        textField.setText(String.valueOf(sudoku.getCell(row, col))); // Revert to the old value
    	        return;
    	    }
        int value;
        try {
            value = Integer.parseInt(textField.getText());
        } catch (NumberFormatException e) {
            value = 0;
        }

        if (value < 1 || value > SIZE * SIZE || !sudoku.isAllowed(row, col, value)) {
            textField.setText("");
            showAlert("Invalid Number", "The number you entered is not allowed.");
        } else {
            sudoku.setCell(row, col, value);
        }
    }

    @FXML
    private void handleSetButton() {
        setButton.setDisable(true);
        clearButton.setDisable(false);
        setButtonPressed = true;

        for (int row = 0; row < SIZE * SIZE; row++) {
            for (int col = 0; col < SIZE * SIZE; col++) {
                TextField textField = (TextField) grid.getChildren().get(row * SIZE + col);
                if (!textField.getText().isEmpty()) {
                    textField.setStyle("-fx-text-fill: blue;");
                }
            }
        }
    }

    @FXML
    private void handleClearButton() {
        setButton.setDisable(false);
        clearButton.setDisable(true);
        setButtonPressed = false;
        sudoku.clearBoard();

        for (int row = 0; row < SIZE * SIZE ; row++) {
            for (int col = 0; col < SIZE * SIZE; col++) {
                TextField textField = (TextField) grid.getChildren().get(row * SIZE * SIZE + col);
                textField.setText("");
                textField.setStyle("-fx-text-fill: black;");
            }
        }
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}