/*Class represents a single line item in an invoice with two attributes 'item' and 'quantity'*/
package Q1;

/*Attributes*/
public class LineInInvoice {
	private Item item;//Object representing the item being purchased.
	private int quantity;//Representing the number of units of the item being purchased.

/*Constructor that set the item and quantity of given line*/
	public LineInInvoice(Item item, int quantity) {
		this.item = item;
		this.quantity = quantity;
	}
/*getter which returns 'Item' object*/	
	public Item getItem() {
		return item;
	}
	
/*getter which returns quantity values*/		
	public int getQuantity() {
		return quantity;
	}
/*getter which returns the total price of item in one line*/	
	public double getTotal() {
		return quantity * item.getPrice();
	}
/*Override - returns a string representation of the line item*/	
	public String toString() {
		return item.getName() + "\t" + quantity + "\t" + getTotal();
	}
	
}



