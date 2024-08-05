import { Address } from './address';
import { Customer } from './customer';
import { Order } from './order';
import { OrderItem } from './order-item';

/**
 * Represents a purchase with customer, shipping and billing addresses, order, and order items.
 */

export class Purchase {
  customer!: Customer;
  shippingAddress!: Address;
  billingAddress!: Address;
  order!: Order;
  orderItems!: OrderItem[];
}
