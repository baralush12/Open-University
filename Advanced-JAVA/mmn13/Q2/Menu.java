/*
 * Stores a collection of Items to represent the entire restaurant menu.
 */

import java.util.ArrayList;
import java.util.List;

public class Menu {
    private List<Item> items;

    public Menu() {
        this.items = new ArrayList<>();
    }

    public void addItem(Item item) {
        this.items.add(item);
    }

    public List<Item> getItems() {
        return this.items;
    }
}