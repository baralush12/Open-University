/*Class which create four items and represent how the process work*/
package Q1;
import java.util.Scanner;

public class Main {
	public static void main(String[]args) {
		Scanner scan = new Scanner(System.in);
		int indexItem;
		int quantityItem;
/*Create cash register object and adds the given items to the current purchase*/		
		CashReg cashReg = new CashReg();
		Item[] items = CashReg.getAllItems();

		System.out.println("Welcome - Please click what kind products and which amount would you like:\n");
		System.out.println("Here are the list of the products:");
		cashReg.getListItems();

		int index = 0;
		while (index != 1 && index != 5) {
			index = 0;
			System.out.println("\nEnter the index of the item you want");
			indexItem = scan.nextInt() - 1;
			System.out.println(items[indexItem].getName() + " " + "has chosen.\n");
			System.out.println("Please enter how many" + " " + items[indexItem].getName() + " " + "would you like");
			quantityItem = scan.nextInt();
			System.out.println("\nAdded to cart:" + " " + quantityItem +"X" + " " + items[indexItem].getName());
			cashReg.addItem(items[indexItem], quantityItem);
			while (index != 1 && index !=2 && index != 5) {
			System.out.println("\nIf you want to pay please Enter '1'\nIf you want to add more items Enter '2'\nIf you want to see your current cart Enter '3'\nIf you want to see your total amount please Enter '4'\nFor EXIT Enter 5");
			index = scan.nextInt();
			System.out.println(index);
			switch (index){
				case 1: double tmp;
						System.out.println("Here your invoice details:\n");
						cashReg.getInvoiceDetails();
						System.out.println("Please write your payment amount:");
						tmp = scan.nextDouble();
						double change = cashReg.getPayment(tmp);//get payment from the customer and give him back a change.
						System.out.println("Your Change Is: " + change);
						break;
				case 2:	cashReg.getListItems();
						break;
				case 3: System.out.println("current purcehase total amount: ");
						cashReg.getInvoiceDetails();
						break;
				case 4: System.out.println("current purcehase total amount: " + cashReg.getCurrentPurchaseTotal());
						break;
				case 5: break;
			}
		}
	}
		System.out.println("\nThank You, Have A Good Day!");
		System.out.println("Total register amount: " + cashReg.getCashTotal());

	}

}
