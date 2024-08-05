package com.bookstore.bookstoreecommerce.dto;

import com.bookstore.bookstoreecommerce.entity.Address;
import com.bookstore.bookstoreecommerce.entity.Customer;
import com.bookstore.bookstoreecommerce.entity.Order;
import com.bookstore.bookstoreecommerce.entity.OrderItem;
import lombok.Data;

import java.util.Set;

@Data
public class Purchase {

    private Customer customer;
    private Address shippingAddress;
    private Address billingAddress;
    private Order order;
    private Set<OrderItem> orderItems;
}
