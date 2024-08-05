import { Injectable } from '@angular/core';
import { CartItem } from '../common/cart-item';
import { BehaviorSubject, Subject } from 'rxjs';

/**
 * Service to manage the shopping cart functionality.
 */
@Injectable({
  providedIn: 'root',
})
export class CartService {
  // Array to store the items in the cart
  cartItems: CartItem[] = [];

  // BehaviorSubject to hold the current total price of the cart
  totalPrice: Subject<number> = new BehaviorSubject<number>(0);

  // BehaviorSubject to hold the current total quantity of items in the cart
  totalQuantity: Subject<number> = new BehaviorSubject<number>(0);

  constructor() {}

  /**
   * Adds a product to the cart. If the product already exists, increments its quantity.
   * @param theCartItem - The cart item to be added.
   */
  addToCart(theCartItem: CartItem) {
    // check if we already have the item in our cart
    let alreadyExistsInCart: boolean = false;
    let existingCartItem: CartItem = undefined!;

    if (this.cartItems.length > 0) {
      // Find the item in the cart based on item ID
      existingCartItem = this.cartItems.find(
        (tempCartItem) => tempCartItem.id === theCartItem.id
      )!;

      // check if we found it
      alreadyExistsInCart = existingCartItem != undefined;
    }

    if (alreadyExistsInCart) {
      // If it exists, increment the quantity
      existingCartItem.quantity++;
    } else {
      // Otherwise, add the new item to the cart
      this.cartItems.push(theCartItem);
    }

    // Recompute the cart totals
    this.computeCartTotals();
  }

  /**
   * Computes the total price and total quantity of the items in the cart.
   */
  computeCartTotals() {
    let totalPriceValue: number = 0;
    let totalQuantityValue: number = 0;

    // Calculate the total price and total quantity
    for (let currentCartItem of this.cartItems) {
      totalPriceValue += currentCartItem.quantity * currentCartItem.unitPrice;
      totalQuantityValue += currentCartItem.quantity;
    }

    // Publish the new values to all subscribers
    this.totalPrice.next(totalPriceValue);
    this.totalQuantity.next(totalQuantityValue);
  }

  /**
   * Decreases the quantity of a given cart item. If the quantity reaches zero, removes the item.
   * @param theCartItem - The cart item to decrement.
   */
  decrementQuantity(theCartItem: CartItem) {
    theCartItem.quantity--;
    // If the quantity reaches zero, remove the item from the cart
    if (theCartItem.quantity === 0) {
      this.remove(theCartItem);
      // Otherwise, recompute the cart totals
    } else {
      this.computeCartTotals();
    }
  }

  /**
   * Removes a cart item from the cart.
   * @param theCartItem - The cart item to remove.
   */
  remove(theCartItem: CartItem) {
    // Get the index of the item in the array
    const itemIndex = this.cartItems.findIndex(
      (tempCartItem) => tempCartItem.id === theCartItem.id
    );

    // If found, remove the item from the array at the given index
    if (itemIndex > -1) {
      this.cartItems.splice(itemIndex, 1);

      // Recompute the cart totals after removing the item
      this.computeCartTotals();
    }
  }
}
