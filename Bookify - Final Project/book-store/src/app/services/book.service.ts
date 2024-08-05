import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Book } from '../models/book';

@Injectable({
  providedIn: 'root'
})
export class BookService {
  private baseUrl = 'http://localhost:8080/api';
  constructor(private http: HttpClient) { }

  // Method to add a book
  addBook(book: Book, user: string, password: string): Observable<any> {
    // Construct the request headers
    const headers = new HttpHeaders()
      .set('Content-Type', 'application/json');

    // Construct the query parameters
    let params = new HttpParams();
    params = params.append('user', user);
    params = params.append('password', password);

    // Send the POST request to the backend API endpoint
    return this.http.post(`${this.baseUrl}/book`, book, { headers, params });
  }
}
