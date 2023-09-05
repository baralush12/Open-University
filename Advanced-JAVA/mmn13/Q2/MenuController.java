/*
 * Controls the behavior of the UI, including loading the menu, adding Items to the order, and handling the "Order" button click event.
 */

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.geometry.Pos;
import java.io.*;
import java.util.*;

public class MenuController {

    @FXML
    private VBox vbox;

    private Order order = new Order();
    private Menu menu = new Menu();

    @FXML
    public void initialize() {
        try {
            loadMenu("menu.txt");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void loadMenu(String filename) throws FileNotFoundException {
        File file = new File(filename);
        Scanner scanner = new Scanner(file);

        while (scanner.hasNext()) {
            String line = scanner.nextLine();
            // If the line does not contain a comma, it is a category.
            if (!line.contains(",")) {
                Label categoryLabel = new Label(line);
                categoryLabel.setStyle("-fx-font-weight: bold; -fx-font-size: 18;"); // Styling the categoryLabel
                vbox.getChildren().add(categoryLabel);
                continue;
            }

            String[] parts = line.split(",");
            String name = parts[0];
            String description = parts[1];
            String type = parts[2];
            double price = Double.parseDouble(parts[3]);

            Item item = new Item(name, description, type, price);
            menu.addItem(item);

            // Create CheckBox and ComboBox for this item
            CheckBox checkBox = new CheckBox(item.getName() + " - $" + item.getPrice());
            ComboBox<Integer> comboBox = new ComboBox<>();
            for (int i = 1; i <= 10; i++) {
                comboBox.getItems().add(i);
            }
            comboBox.setDisable(true);

            // Add listener to CheckBox
            checkBox.selectedProperty().addListener((observable, oldValue, newValue) -> {
                if (newValue) {
                    comboBox.setDisable(false);
                    order.addItem(item, 1);
                    comboBox.setValue(1);
                } else {
                    comboBox.setDisable(true);
                    order.removeItem(item);
                }
            });

            // Add listener to ComboBox
            comboBox.valueProperty().addListener((observable, oldValue, newValue) -> {
                if (checkBox.isSelected()) {
                    order.addItem(item, newValue);
                }
            });

            // Create a VBox for each item
            VBox itemBox = new VBox();
            itemBox.setAlignment(Pos.CENTER); // This will center the items

            // Add CheckBox and ComboBox to the itemBox
            itemBox.getChildren().addAll(checkBox, comboBox);

            // Add the itemBox to the main vbox
            vbox.getChildren().add(itemBox);
        }
        
        scanner.close();
    }
    @FXML
    public void handleOrderButton() {
        // Create a dialog with Approve, Update, and Cancel buttons
        Dialog<ButtonType> dialog = new Dialog<>();
        ButtonType updateButtonType = new ButtonType("Update", ButtonBar.ButtonData.OTHER);
        dialog.getDialogPane().getButtonTypes().addAll(ButtonType.APPLY, updateButtonType, ButtonType.CANCEL);
        dialog.setTitle("Order Details");
        dialog.setHeaderText("Please review your order");

        // Add a TextArea to display the order details
        TextArea textArea = new TextArea(order.toString());
        textArea.setEditable(false);
        dialog.getDialogPane().setContent(textArea);

        // Show dialog and get result
        Optional<ButtonType> result = dialog.showAndWait();
        if (result.isPresent()) {
            ButtonType button = result.get();

            if (button == ButtonType.APPLY) {
                // Create a second dialog to ask for the user's name and ID
            	DialogPane dialogPane = new DialogPane();
            	Label nameLabel = new Label("Name: ");
            	TextField nameField = new TextField();
            	Label idLabel = new Label("ID: ");
            	TextField idField = new TextField();
            	dialogPane.setContent(new VBox(nameLabel, nameField, idLabel, idField));
                Dialog<ButtonType> secondDialog = new Dialog<>();
                secondDialog.setDialogPane(dialogPane);
                secondDialog.getDialogPane().getButtonTypes().add(ButtonType.OK);
                secondDialog.showAndWait();

                // Set the user's name and ID
                order.setUserName(nameField.getText());
                order.setUserID(idField.getText());

                try {
                    saveOrder(order);
                } catch (IOException e) {
                    e.printStackTrace();
                }

                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Order Placed");
                alert.setHeaderText("Order has been placed!");
                alert.setContentText("Thank you for your order, " + order.getUserName());
                alert.showAndWait();

                // Clear the order and the VBox
                order.clear();
                vbox.getChildren().clear();

                // Reload the menu
                try {
                    loadMenu("menu.txt");
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            } else if (button == ButtonType.CANCEL) {
                // Clear the order and the VBox, and reload the menu
                order.clear();
                vbox.getChildren().clear();

                try {
                    loadMenu("menu.txt");
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            } else if (button == updateButtonType) {
                // If Update is clicked, just close the dialog
                // The user can change the order in the main window
            }
        }
    }
    public void saveOrder(Order order) throws IOException {
        PrintWriter writer = new PrintWriter(order.getUserName() + "_" + order.getUserID() + ".txt", "UTF-8");
        for (Map.Entry<Item, Integer> entry : order.getItems().entrySet()) {
            writer.println(entry.getKey().getName() + ", " + entry.getValue());
        }
        writer.println("Total: $" + order.calculateTotal());
        writer.close();
    }
    
}