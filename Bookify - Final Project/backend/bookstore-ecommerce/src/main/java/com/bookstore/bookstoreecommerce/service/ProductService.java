package com.bookstore.bookstoreecommerce.service;

import com.bookstore.bookstoreecommerce.dao.ProductCategoryRepository;
import com.bookstore.bookstoreecommerce.dao.ProductRepository;
import com.bookstore.bookstoreecommerce.entity.Product;
import com.bookstore.bookstoreecommerce.entity.ProductCategory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service

public class ProductService {
    private final ProductRepository productRepository;
    private final ProductCategoryRepository productCategoryRepository;

    @Autowired
    public ProductService(ProductRepository productRepository,ProductCategoryRepository productCategoryRepository) {
        this.productRepository = productRepository;
        this.productCategoryRepository = productCategoryRepository;
    }

    public Product saveBook(Product book,Long categoryId) {
        if(categoryId == null){
            categoryId = Long.valueOf(1);
        }
        ProductCategory category = findCategoryById(categoryId);
        book.setCategory(category);
        return productRepository.save(book);
    }

    private ProductCategory findCategoryById(Long categoryId) {
        ProductCategory c = productCategoryRepository.getById(categoryId);
        System.out.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
        return  c;
    }
}
