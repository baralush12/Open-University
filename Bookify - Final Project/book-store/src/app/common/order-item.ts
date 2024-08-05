/**
 * Represents an item in an order.
 */
export class OrderItem {
  constructor(
    public imageUrl: string,
    public unitPrice: number,
    public quantity: number,
    public productId: string
  ) {}
}
