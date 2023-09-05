/*Class represents the cash register system with four attributes*/

package Q1;
import java.util.ArrayList; // import the ArrayList class

/*Attributes*/
public class CashReg {
	private double cashTotal;//Representing the total amount of cash in the register.
	private double currentPurchaseTotal;//Representing the total cost of current purchase.
	private ArrayList<LineInInvoice> currentPurchase;//Array list of 'LineInInvoice' object which represent current purchase.
	private ArrayList<LineInInvoice> allPurchases;//Array list of 'LineInInvoice' object which represent all purchases in the cash register.
	//List of current available items.
	private final static int NUMOFITEMS = 4;
    private static final Item[] listItems = new Item [] {
    		new Item("banana",5),
    		new Item("apple", 10),
    	    new Item("orange", 15),
    	    new Item("carrot", 20)
	};
	
	/*private static Item[] listItems() { 
		Item[] items = new Item[NUMOFITEMS]; 	
		items[0] = new Item("banana", 5.0);
		items[1] = new Item("apple", 10.0);
		items[2] = new Item("orange", 15.0);
		items[3] = new Item("carrot", 20.0);
		return items;
	}*/
	
    public void getListItems() {
    	for(int i=0; i< NUMOFITEMS; i++) {
    		System.out.println("Item " + (i+1) + ": " + listItems[i].getName() + ", Price: " + listItems[i].getPrice());
    	}	
    }
    public static Item[] getAllItems() {
        return listItems;
    }
/*Empty constructor which create empty cash register*/	
	public CashReg() {
		this.cashTotal = 0.0;
		this.currentPurchaseTotal = 0.0;
		this.currentPurchase = new ArrayList<LineInInvoice>();
		this.allPurchases = new ArrayList<LineInInvoice>();
	}
/*Constructor which initialize amount to cashTotal*/	
	public CashReg(double initialAmount) {
		this();
		this.cashTotal = initialAmount;
	}
/*Methods which adds a line item to the current purchase*/	
	public void addItem(Item item, int quantity) {
		LineInInvoice line = new LineInInvoice(item, quantity);
		currentPurchase.add(line);
		currentPurchaseTotal += line.getTotal();
	}

/*Prints all the details of current purchase*/
	public void getInvoiceDetails() {
		for(LineInInvoice line : currentPurchase) {
			System.out.println(line.toString());
		}
	}

/*Returns the values of total price on current purchase*/	
	public double getCurrentPurchaseTotal() {
		return currentPurchaseTotal;
	}
/*Method which get payment from customer and subtracting the current price and give back change*/	
	public double getPayment(double pay) {
		double change = pay - currentPurchaseTotal;
		cashTotal += currentPurchaseTotal;
		allPurchases.addAll(currentPurchase);
		currentPurchaseTotal = 0.0;
		currentPurchase.clear();
		return change;		
	}
/*Returns the value of the cash total */	
	public double getCashTotal() {
		return cashTotal;
	}

}
