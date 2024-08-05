import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Purchase } from '../common/purchase';

/**
 * Service to handle checkout-related operations.
 */
@Injectable({
  providedIn: 'root',
})
export class CheckoutService {
  // URL to the checkout API endpoint
  private purchaseUrl = 'http://localhost:8080/api/checkout/purchase';

  constructor(private httpClient: HttpClient) {}

  /**
   * Places an order by sending the purchase details to the backend.
   * @param purchase - The purchase details to be sent.
   * @returns An Observable that emits the response from the backend.
   */
  placeOrder(purchase: Purchase): Observable<any> {
    return this.httpClient.post<Purchase>(this.purchaseUrl, purchase);
  }
}
