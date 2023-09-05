/*
 * It defines the actions to be taken when the user interacts with the GUI. 
 * The controller manages the HashMap of reminders and persists it to a file.
 */
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import java.util.HashMap;
import java.io.*;

public class ReminderController {

    @FXML
    private ComboBox<Integer> dayBox;
    
    @FXML
    private ComboBox<Integer> monthBox;

    @FXML
    private ComboBox<Integer> yearBox;

    @FXML
    private TextArea reminderArea;
      
    @FXML
    private TextField fileNameField;

    private HashMap<Date, String> reminders = new HashMap<>();
    private String filename = ""; 
    
    @FXML
    private void initialize() {        
        for (int i = 1; i <= 31; i++) {
            dayBox.getItems().add(i);
        }
        for (int i = 1; i <= 12; i++) {
            monthBox.getItems().add(i);
        }
        for (int i = 2020; i <= 2023; i++) {
            yearBox.getItems().add(i);
        }
    }

    // Gets user input from the UI, adds or updates the reminder in the HashMap, and saves it to a file.
    @FXML
    private void saveReminder() {
        String filename = fileNameField.getText().trim();
        if (filename.isEmpty()) {
            Alert alert = new Alert(AlertType.ERROR, "Filename can't be empty");
            alert.showAndWait();
            return;
        }
        this.filename = filename + ".ser";  // set new filename

        Date date = new Date(dayBox.getValue(), monthBox.getValue(), yearBox.getValue());
        String reminder = reminderArea.getText();
        reminders.put(date, reminder);

        // Save to file
        try {
            FileOutputStream fileOut = new FileOutputStream(this.filename);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(reminders);
            out.close();
            fileOut.close();
            Alert alert = new Alert(AlertType.INFORMATION, "Reminder saved successfully");
            alert.showAndWait();
        } catch (IOException e) {
            Alert alert = new Alert(AlertType.ERROR, "Error Saving Reminder: " + e.getMessage());
            alert.showAndWait();
            e.printStackTrace();
        }
    }

    //Retrieves the reminder for a given date from the HashMap and displays it in the UI.
    @FXML
    private void retrieveReminder() {
        Date date = new Date(dayBox.getValue(), monthBox.getValue(), yearBox.getValue());
        String reminder = reminders.getOrDefault(date, "");
        reminderArea.setText(reminder);
    }
    
    //Clears the content of the text area in the UI.
    @FXML
    private void clearReminderArea() {
        reminderArea.clear();
    }

    //Loads the reminders from the file specified by the user.
    @FXML
    private void loadFile() {
        String filename = fileNameField.getText().trim();
        if (filename.isEmpty()) {
            Alert alert = new Alert(AlertType.ERROR, "Filename can't be empty");
            alert.showAndWait();
            return;
        }
        this.filename = filename + ".ser"; // set new filename

        // Clear the TextArea
        reminderArea.clear();

        // Load from file
        try {
            FileInputStream fileIn = new FileInputStream(this.filename);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            reminders = (HashMap<Date, String>) in.readObject();
            in.close();
            fileIn.close();
            Alert alert = new Alert(AlertType.INFORMATION, "File loaded successfully");
            alert.showAndWait();
        } catch (IOException i) {
            Alert alert = new Alert(AlertType.ERROR, "Error Loading File: " + i.getMessage());
            alert.showAndWait();
        } catch (ClassNotFoundException c) {
            Alert alert = new Alert(AlertType.ERROR, "File Not Found: " + c.getMessage());
            alert.showAndWait();
        }
    }
}


