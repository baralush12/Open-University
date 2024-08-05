package com.bookstore.bookstoreecommerce.service;

import com.bookstore.bookstoreecommerce.dto.Purchase;
import com.bookstore.bookstoreecommerce.dto.PurchaseResponse;

public interface CheckoutService {

    PurchaseResponse placeOrder(Purchase purchase);
}
