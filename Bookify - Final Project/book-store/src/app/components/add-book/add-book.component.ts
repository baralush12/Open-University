import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { BookService } from '../../services/book.service';
import { Book } from '../../models/book';
import { ToastrService } from 'ngx-toastr';

@Component({
  selector: 'app-add-book',
  templateUrl: './add-book.component.html',
  styleUrls: ['./add-book.component.css']
})
export class AddBookComponent {
  book: Book = new Book();
  user: string = '';
  password: string = '';

  constructor(private bookService: BookService, private router: Router,private toastr: ToastrService) { }

        // Method to show success toast
      showSuccess() {
        this.toastr.success('Book added successfully!', 'Success');
      }
  
      // Method to show error toast
      showError() {
        this.toastr.error('Failed to add book!', 'Error');
      }

  onSubmit(): void {
    // Construct request body with book information
    const requestBody = {
      book: this.book,
      user: this.user,
      password: this.password
    };

    // Send request to add book API endpoint with request body and query parameters
    this.bookService.addBook(this.book, this.user, this.password).subscribe(
      response => {
        this.showSuccess();
        console.log('Book added successfully!', response);
        // Optionally, reset the form or navigate to another page
        this.book = new Book();
        this.user = '';
        this.password = '';
      },
      error => {
        console.error('There was an error adding the book!', error);
        this.showError();
      }
    );
  }
}
