/*
 * Class represent an item that can be purchased with two attributes.
 */
package Q1;


/*Attributes*/
public class Item {
	private String name;//Name of item
	private double price;//Price of item


/*Constructor that set the name and price of given item*/
	public Item(String name, double price) {
		this.name = name;
		this.price = price;
	}
/*getter and setter which return the values of the 'name' and 'price'*/	
	public String getName() {
		return name;
	}
	public double getPrice() {
		return price;
	}

}
