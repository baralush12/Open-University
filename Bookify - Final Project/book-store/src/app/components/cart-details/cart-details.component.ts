import { Component, OnInit } from '@angular/core';
import { CartItem } from '../../common/cart-item';
import { CartService } from '../../services/cart.service';

/**
 * Component to display the details of the shopping cart.
 */
@Component({
  selector: 'app-cart-details',
  templateUrl: './cart-details.component.html',
  styleUrls: ['./cart-details.component.css'],
})
export class CartDetailsComponent implements OnInit {
  cartItems: CartItem[] = [];
  totalPrice: number = 0;
  totalQuantity: number = 0;

  constructor(private cartService: CartService) {}

  /**
   * Lifecycle hook that is called after data-bound properties of a directive are initialized.
   */
  ngOnInit(): void {
    this.listCartDetails();
  }

  /**
   * Lists the details of the cart by getting cart items and subscribing to cart total price and quantity.
   */
  listCartDetails() {
    // Get a handle to the cart items
    this.cartItems = this.cartService.cartItems;

    // Subscribe to the cart total price
    this.cartService.totalPrice.subscribe((data) => (this.totalPrice = data));

    // Subscribe to the cart totalQuantity
    this.cartService.totalQuantity.subscribe(
      (data) => (this.totalQuantity = data)
    );

    // Compute cart total price and quantity
    this.cartService.computeCartTotals();
  }

  /**
   * Increments the quantity of the given cart item.
   * @param {CartItem} theCartItem - The cart item to increment.
   */
  incrementQuantity(theCartItem: CartItem) {
    this.cartService.addToCart(theCartItem);
  }

  /**
   * Decrements the quantity of the given cart item.
   * @param {CartItem} theCartItem - The cart item to decrement.
   */
  decrementQuantity(theCartItem: CartItem) {
    this.cartService.decrementQuantity(theCartItem);
  }

  /**
   * Removes the given cart item from the cart.
   * @param {CartItem} theCartItem - The cart item to remove.
   */
  remove(theCartItem: CartItem) {
    this.cartService.remove(theCartItem);
  }
}
