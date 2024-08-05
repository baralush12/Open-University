package com.bookstore.bookstoreecommerce.dao;

import com.bookstore.bookstoreecommerce.entity.ShopUser;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository

public interface UserRepository extends JpaRepository<ShopUser,Long> {
}
