import { Component, OnInit } from '@angular/core';
import { ProductCategory } from '../../common/product-category';
import { ProductService } from '../../services/product.service';

/**
 * Component to display the product categories menu.
 * It fetches the product categories from the product service and displays them.
 */
@Component({
  selector: 'app-product-category-menu',
  templateUrl: './product-category-menu.component.html',
  styleUrls: ['./product-category-menu.component.css'],
})
export class ProductCategoryMenuComponent implements OnInit {
  productCategories: ProductCategory[] = [];

  constructor(private productService: ProductService) {}

  /**
   * OnInit lifecycle hook to initialize the component.
   * It calls the method to list product categories.
   */
  ngOnInit() {
    this.listProductCategories();
  }

  /**
   * Retrieves the list of product categories from the product service.
   */
  listProductCategories() {
    this.productService.getProductCategories().subscribe((data) => {
      this.productCategories = data;
    });
  }
}
