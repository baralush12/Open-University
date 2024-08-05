package com.bookstore.bookstoreecommerce.entity;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import lombok.Data;

@Entity
@Data
public class ShopUser {
    @Id
    @GeneratedValue
    private Long id;

    private String username;
    private String password;

}
