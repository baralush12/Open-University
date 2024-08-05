package com.bookstore.bookstoreecommerce.dao;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import com.bookstore.bookstoreecommerce.entity.Contact;

@Repository
public interface ContactRepository extends JpaRepository<Contact, Long> {
}
