import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

/**
 * Service to handle contact-related operations.
 */
@Injectable({
  providedIn: 'root',
})
export class ContactService {
  // Base URL to the contact API endpoint
  private baseUrl = 'http://localhost:8080/api/contacts';

  constructor(private httpClient: HttpClient) {}

  /**
   * Saves the contact details by sending them to the backend.
   * @param contact - The contact details to be saved.
   * @returns An Observable that emits the response from the backend.
   */
  saveContactDetails(contact: any): Observable<any> {
    return this.httpClient.post(`${this.baseUrl}/save`, contact);
  }
}
