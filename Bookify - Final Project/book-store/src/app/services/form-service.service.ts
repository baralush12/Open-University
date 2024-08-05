import { Injectable } from '@angular/core';
import { Observable, of } from 'rxjs';

/**
 * Service to handle form-related operations, such as retrieving credit card months and years.
 */
@Injectable({
  providedIn: 'root',
})
export class FormService {
  constructor() {}

  /**
   * Retrieves a list of credit card expiration months starting from the given month.
   * @param startMonth - The month to start from (1-12).
   * @returns An Observable emitting an array of months from the start month to December.
   */
  getCreditCardMonths(startMonth: number): Observable<number[]> {
    let data: number[] = [];

    // Generate months from the start month to December
    for (let theMonth = startMonth; theMonth <= 12; theMonth++) {
      data.push(theMonth);
    }

    // Return the data as an observable
    return of(data);
  }

  /**
   * Retrieves a list of credit card expiration years starting from the current year.
   * @returns An Observable emitting an array of years from the current year to 10 years in the future.
   */
  getCreditCardYears(): Observable<number[]> {
    let data: number[] = [];

    const startYear: number = new Date().getFullYear();
    const endYear: number = startYear + 10;

    // Generate years from the current year to the end year
    for (let theYear = startYear; theYear <= endYear; theYear++) {
      data.push(theYear);
    }

    // Return the data as an observable
    return of(data);
  }
}
