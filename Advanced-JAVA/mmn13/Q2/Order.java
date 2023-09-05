/*
 * Stores the current user's order, including their name, ID, and a map of Items to quantities.
 */

import java.util.HashMap;
import java.util.Map;

public class Order {
    private Map<Item, Integer> items;  // Item and quantity
    private String userName;
    private String userID;

    public Order() {
        this.items = new HashMap<>();
    }

    public void addItem(Item item, int quantity) {
        this.items.put(item, quantity);
    }

    public void removeItem(Item item) {
        this.items.remove(item);
    }

    public double calculateTotal() {
        double total = 0;
        for (Map.Entry<Item, Integer> entry : items.entrySet()) {
            total += entry.getKey().getPrice() * entry.getValue();
        }
        return total;
    }

    public void clear() {
        this.items.clear();
    }

    public Map<Item, Integer> getItems() {
        return this.items;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Map.Entry<Item, Integer> entry : items.entrySet()) {
            sb.append(entry.getKey().getName())
                    .append(", Quantity: ")
                    .append(entry.getValue())
                    .append(", Price: $")
                    .append(entry.getKey().getPrice())
                    .append("\n");
        }
        sb.append("Total: $").append(calculateTotal());
        return sb.toString();
    }
}
