package com.bookstore.bookstoreecommerce.dao;
import com.bookstore.bookstoreecommerce.entity.Customer;
import org.springframework.data.jpa.repository.JpaRepository;

public interface CustomerRepository extends JpaRepository<Customer, Long> {
}
