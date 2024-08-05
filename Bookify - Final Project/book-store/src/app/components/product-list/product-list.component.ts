import { Component } from '@angular/core';
import { Product } from '../../common/product';
import { ProductService } from '../../services/product.service';
import { ActivatedRoute } from '@angular/router';
import { CartService } from '../../services/cart.service';
import { CartItem } from '../../common/cart-item';
import { Router } from '@angular/router';

/**
 * Component to display a list of products in a specific category.
 * It supports pagination and adding products to the cart.
 */
@Component({
  selector: 'app-product-list',
  templateUrl: './product-list.component.html',
  styleUrl: './product-list.component.css',
})
export class ProductListComponent {
  products: Product[] = [];
  currentCategoryId: number = 1;
  previousCategoryId: number = 1;
  currentCategoryName: string = '';
  searchMode: boolean = false;

  // new properties for pagination
  thePageNumber: number = 1;
  thePageSize: number = 5;
  theTotalElements: number = 0;

  previousKeyword: string = '';

  constructor(
    private productService: ProductService,
    private cartService: CartService,
    private route: ActivatedRoute,
    private router: Router
  ) {}

  /**
   * OnInit lifecycle hook to initialize the component.
   * It subscribes to route parameters and lists products.
   */
  ngOnInit() {
    this.route.paramMap.subscribe(() => {
      this.listProducts();
    });
  }

  /**
   * Lists products based on the current route parameters.
   */
  listProducts() {
    this.searchMode = this.route.snapshot.paramMap.has('keyword');

    if (this.searchMode) {
      this.handleSearchProducts();
    } else {
      this.handleListProducts();
    }
  }

  /**
   * Handles searching products based on a keyword.
   */
  handleSearchProducts() {
    const theKeyword: string = this.route.snapshot.paramMap.get('keyword')!;

    // If we have a different keyword than the previous one, reset the page number to 1
    if (this.previousKeyword != theKeyword) {
      this.thePageNumber = 1;
    }

    this.previousKeyword = theKeyword;

    // Search for products using the keyword
    this.productService
      .searchProductsPaginate(
        this.thePageNumber - 1,
        this.thePageSize,
        theKeyword
      )
      .subscribe(this.processResult());
  }

  /**
   * Handles listing products in a category.
   */
  handleListProducts() {
    // Check if "id" parameter is available
    const hasCategoryId: boolean = this.route.snapshot.paramMap.has('id');

    if (hasCategoryId) {
      // Get the "id" param string and convert it to a number
      this.currentCategoryId = +this.route.snapshot.paramMap.get('id')!;
      // Get the category name
      this.currentCategoryName = this.route.snapshot.paramMap.get('name')!;
    } else {
      // Default to category id 1 if not available
      this.currentCategoryId = 1;
      this.currentCategoryName = 'Default';
    }

    // If we have a different category id than the previous one, reset the page number to 1
    if (this.previousCategoryId != this.currentCategoryId) {
      this.thePageNumber = 1;
    }

    this.previousCategoryId = this.currentCategoryId;

    // Get the products for the given category id
    this.productService
      .getProductListPaginate(
        this.thePageNumber - 1,
        this.thePageSize,
        this.currentCategoryId
      )
      .subscribe(this.processResult());
  }

  /**
   * Updates the page size and resets the page number to 1.
   * @param pageSize - the new page size
   */
  updatePageSize(pageSize: string) {
    this.thePageSize = +pageSize;
    this.thePageNumber = 1;
    this.listProducts();
  }

  /**
   * Processes the result from the product service and updates the component state.
   * @returns a function to process the result
   */
  processResult() {
    return (data: any) => {
      this.products = data._embedded.products;
      this.thePageNumber = data.page.number + 1;
      this.thePageSize = data.page.size;
      this.theTotalElements = data.page.totalElements;
    };
  }

  /**
   * Adds a product to the cart.
   * @param theProduct - the product to add to the cart
   */
  addToCart(theProduct: Product) {
    const theCartItem = new CartItem(theProduct);
    this.cartService.addToCart(theCartItem);
  }
  /**
   * Navigates to the search results page based on the search input.
   * @param value - The search query entered by the user
   */
  doSearch(value: string) {
    if (value) {
      this.router.navigateByUrl(`/search/${encodeURIComponent(value)}`);
    } else {
      this.router.navigateByUrl(`/products`);
      this.listProducts();
    }
  }
}
