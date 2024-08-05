import { Product } from './product';
/**
 * Represents an item in the shopping cart.
 */

export class CartItem {
  id: string;
  name: string;
  imageUrl: string;
  unitPrice: number;
  quantity: number;

  /**
   * Creates an instance of CartItem.
   * @param {Product} product - The product to create a cart item from.
   */
  constructor(product: Product) {
    this.id = product.id;
    this.name = product.name;
    this.imageUrl = product.imageUrl;
    this.unitPrice = product.unitPrice;

    this.quantity = 1;
  }
}
