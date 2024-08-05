import { Component, OnInit } from '@angular/core';
import { ProductService } from '../../services/product.service';
import { Product } from '../../common/product';
import { CartService } from '../../services/cart.service';
import { CartItem } from '../../common/cart-item';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ContactService } from '../../services/contact.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
})
export class HomeComponent implements OnInit {
  products: Product[] = [];
  contactForm: FormGroup;

  constructor(
    private productService: ProductService,
    private cartService: CartService,
    private fb: FormBuilder,
    private contactService: ContactService
  ) {
    this.contactForm = this.fb.group({
      name: ['', Validators.required],
      email: ['', [Validators.required, Validators.email]],
      book: ['', Validators.required],
    });
  }

  ngOnInit(): void {
    this.loadFeaturedProducts();
  }

  loadFeaturedProducts() {
    this.productService.getProductList(1).subscribe(
      // Assuming category ID 1 for featured products
      (data) => {
        this.products = data.slice(0, 4); // Assuming you want to show the first 4 products
      }
    );
  }

  addToCart(product: Product) {
    const cartItem = new CartItem(product);
    this.cartService.addToCart(cartItem);
  }

  onSubmit() {
    if (this.contactForm.valid) {
      this.contactService
        .saveContactDetails(this.contactForm.value)
        .subscribe((response) => {
          alert('Thank you for your message. We will contact you shortly.');
          this.contactForm.reset();
        });
    }
  }
}
