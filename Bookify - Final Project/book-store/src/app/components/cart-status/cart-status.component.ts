import { Component, OnInit } from '@angular/core';
import { CartService } from '../../services/cart.service';

/**
 * Component to display the current status of the shopping cart.
 */
@Component({
  selector: 'app-cart-status',
  templateUrl: './cart-status.component.html',
  styleUrls: ['./cart-status.component.css'],
})
export class CartStatusComponent implements OnInit {
  totalPrice: number = 0.0;
  totalQuantity: number = 0;

  constructor(private cartService: CartService) {}

  /**
   * Lifecycle hook that is called after data-bound properties of a directive are initialized.
   */
  ngOnInit(): void {
    this.updateCartStatus();
  }

  /**
   * Updates the cart status by subscribing to total price and quantity changes.
   */
  updateCartStatus() {
    // Subscribe to the cart total price
    this.cartService.totalPrice.subscribe((data) => (this.totalPrice = data));

    // Subscribe to the cart total quantity
    this.cartService.totalQuantity.subscribe(
      (data) => (this.totalQuantity = data)
    );
  }
}
