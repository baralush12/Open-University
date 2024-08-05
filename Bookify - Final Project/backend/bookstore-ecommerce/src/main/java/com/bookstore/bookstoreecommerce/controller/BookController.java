package com.bookstore.bookstoreecommerce.controller;

import com.bookstore.bookstoreecommerce.dao.ProductRepository;
import com.bookstore.bookstoreecommerce.entity.BookRequest;
import com.bookstore.bookstoreecommerce.entity.Product;
import com.bookstore.bookstoreecommerce.service.CheckoutService;
import com.bookstore.bookstoreecommerce.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.HttpClientErrorException;

import java.awt.print.Book;

@CrossOrigin("http://localhost:4200")
@RestController
@RequestMapping("/api")
public class BookController {

    private final ProductService productService;

    @Autowired
    public BookController(ProductService productService) {
        this.productService = productService;
    }

    @PostMapping("book")
    @ResponseStatus(HttpStatus.CREATED)
    public ResponseEntity<Product> addBook(@RequestBody BookRequest b, @RequestParam String user, @RequestParam String password) throws Exception{
        if (!user.equals("admin") || !password.equals("admin")){
            throw new Exception("unauthorized!");
        }

            Product book = new Product();
            book.setName(b.getName());
            book.setDescription(b.getDescription());
            book.setUnitPrice(b.getUnitPrice());
            book.setImageUrl(b.getImageUrl());
            book.setActive(b.isActive());
            book.setUnitsInStock(b.getUnitsInStock());
            Product createdBook = productService.saveBook(book, b.getCategoryId());
            return new ResponseEntity<>(createdBook, HttpStatus.CREATED);

    }
}
