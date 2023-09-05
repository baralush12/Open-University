/*
 * Represents a single item on the restaurant menu, with a name, description, type, and price.
 */

public class Item {
    private String name;
    private String description;
    private String type;
    private double price;

    public Item(String name, String description, String type, double price) {
        this.name = name;
        this.description = description;
        this.type = type;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public String getType() {
        return type;
    }

    public double getPrice() {
        return price;
    }
}
