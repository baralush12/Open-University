package com.bookstore.bookstoreecommerce;

import com.bookstore.bookstoreecommerce.dao.CustomerRepository;
import com.bookstore.bookstoreecommerce.dao.ProductCategoryRepository;
import com.bookstore.bookstoreecommerce.dao.ProductRepository;
import com.bookstore.bookstoreecommerce.entity.Customer;
import com.bookstore.bookstoreecommerce.entity.Product;
import com.bookstore.bookstoreecommerce.entity.ProductCategory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@SpringBootApplication
public class BookstoreEcommerceApplication {


	@Autowired
	CustomerRepository customerRepository;
	@Autowired
	ProductCategoryRepository productCategoryRepository;
	@Autowired
	ProductRepository productRepository;

	public static void main(String[] args) {
		SpringApplication.run(BookstoreEcommerceApplication.class, args);
	}


	public static class BookData{
		public String title;
		public String author;
		public String imageUrl;

		public ProductCategory category;

		public BookData(String title, String author, String imageUrl, ProductCategory category) {
			this.title = title;
			this.author = author;
			this.imageUrl = imageUrl;
			this.category = category;
		}
	}

	List<BookData> GetBooksData() {
		ProductCategory p1 = new ProductCategory();
		p1.setCategoryName("Fiction");
		ProductCategory p2 = new ProductCategory();
		p2.setCategoryName("Drama");
		ProductCategory p3 = new ProductCategory();
		p3.setCategoryName("Novel");

		productCategoryRepository.save(p1);
		productCategoryRepository.save(p2);
		productCategoryRepository.save(p3);
		List<BookData> l = new ArrayList<BookData>();
		l.add(new BookData("The Mummies of Urumchi","E. J. W. Barber","http://images.amazon.com/images/P/0393045218.01.THUMBZZZ.jpg",p1));
		l.add(new BookData("The Kitchen God's Wife","Amy Tan","http://images.amazon.com/images/P/0399135782.01.THUMBZZZ.jpg",p1));
		l.add(new BookData("Jane Doe","R. J. Kaiser","http://images.amazon.com/images/P/1552041778.01.THUMBZZZ.jpg",p1));
		l.add(new BookData("The Testament","John Grisham","http://images.amazon.com/images/P/0440234743.01.THUMBZZZ.jpg",p2));
		l.add(new BookData("Beloved (Plume Contemporary Fiction)","Toni Morrison","http://images.amazon.com/images/P/0452264464.01.THUMBZZZ.jpg",p2));
		l.add(new BookData("Airframe","Michael Crichton","http://images.amazon.com/images/P/0345402871.01.THUMBZZZ.jpg",p2));
		l.add(new BookData("OUT OF THE SILENT PLANET","C.S. Lewis","http://images.amazon.com/images/P/0684823802.01.THUMBZZZ.jpg",p2));
		l.add(new BookData("Lying Awake","Mark Salzman","http://images.amazon.com/images/P/0375406328.01.THUMBZZZ.jpg",p2));
		l.add(new BookData("To Kill a Mockingbird","Harper Lee","http://images.amazon.com/images/P/0446310786.01.THUMBZZZ.jpg",p3));
		l.add(new BookData("Pride and Prejudice","Jane Austen","http://images.amazon.com/images/P/055321215X.01.THUMBZZZ.jpg",p3));
		l.add(new BookData("Isle of Dogs","Patricia Cornwell","http://images.amazon.com/images/P/0425182908.01.THUMBZZZ.jpg",p3));
		
		return l;
	}
	@Bean
	CommandLineRunner commandLineRunner(){
		return args -> {
			for (BookData book: GetBooksData()){
				double random = 1.35 + Math.random() * (17.8 - 1.35);
				Product b = new Product();
				b.setUnitPrice(new BigDecimal(random));
				b.setName(book.title);
				b.setActive(true);
				b.setCategory(book.category);
				b.setImageUrl(book.imageUrl);
				b.setDescription("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.");
				b.setUnitsInStock(12);
				b.setDateCreated(new Date());
				productRepository.save(b);
			}
		};
	}
}
