package com.bookstore.bookstoreecommerce.controller;

import com.bookstore.bookstoreecommerce.dao.ContactRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import com.bookstore.bookstoreecommerce.entity.Contact;

@CrossOrigin("http://localhost:4200")
@RestController
@RequestMapping("/api/contacts")
public class ContactController {

    private final ContactRepository contactRepository;

    public ContactController(ContactRepository contactRepository) {
        this.contactRepository = contactRepository;
    }

    @PostMapping("/save")
    public Contact saveContact(@RequestBody Contact contact) {
        return contactRepository.save(contact);
    }
}