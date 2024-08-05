import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Product } from '../common/product';
import { map } from 'rxjs/operators';
import { ProductCategory } from '../common/product-category';

/**
 * Service to handle product-related operations.
 */
@Injectable({
  providedIn: 'root',
})
export class ProductService {
  // Base URL for products API endpoint
  private baseUrl = 'http://localhost:8080/api/products';

  // Base URL for product categories API endpoint
  private categoryUrl = 'http://localhost:8080/api/product-category';

  constructor(private httpClient: HttpClient) {}

  /**
   * Retrieves a list of products for a given category ID.
   * @param theCategoryId - The category ID to filter products by.
   * @returns An Observable emitting an array of products.
   */
  getProductList(theCategoryId: number = 1): Observable<Product[]> {
    // Build URL based on category ID
    const searchUrl = `${this.baseUrl}/search/findByCategoryId?id=${theCategoryId}`;

    return this.getProducts(searchUrl);
  }

  /**
   * Retrieves a paginated list of products for a given category ID.
   * @param thePage - The current page number.
   * @param thePageSize - The number of items per page.
   * @param theCategoryId - The category ID to filter products by.
   * @returns An Observable emitting the paginated response of products.
   */
  getProductListPaginate(
    thePage: number,
    thePageSize: number,
    theCategoryId: number
  ): Observable<GetResponseProducts> {
    // Build URL based on category ID, page, and sizes
    const searchUrl =
      `${this.baseUrl}/search/findByCategoryId?id=${theCategoryId}` +
      `&page=${thePage}&size=${thePageSize}`;

    return this.httpClient.get<GetResponseProducts>(searchUrl);
  }

  /**
   * Searches for products based on a given keyword.
   * @param theKeyword - The keyword to search for.
   * @returns An Observable emitting an array of products.
   */
  searchProducts(theKeyword: string): Observable<Product[]> {
    // Build URL based on the keyword
    const searchUrl = `${this.baseUrl}/search/findByNameContaining?name=${theKeyword}`;

    return this.getProducts(searchUrl);
  }

  /**
   * Retrieves a paginated list of products based on a given keyword.
   * @param thePage - The current page number.
   * @param thePageSize - The number of items per page.
   * @param theKeyword - The keyword to search for.
   * @returns An Observable emitting the paginated response of products.
   */
  searchProductsPaginate(
    thePage: number,
    thePageSize: number,
    theKeyword: string
  ): Observable<GetResponseProducts> {
    // Build URL based on keyword, page, and size
    const searchUrl =
      `${this.baseUrl}/search/findByNameContaining?name=${theKeyword}` +
      `&page=${thePage}&size=${thePageSize}`;

    return this.httpClient.get<GetResponseProducts>(searchUrl);
  }

  /**
   * Helper method to get products from the given URL.
   * @param searchUrl - The URL to fetch products from.
   * @returns An Observable emitting an array of products.
   */
  private getProducts(searchUrl: string): Observable<Product[]> {
    return this.httpClient
      .get<GetResponseProducts>(searchUrl)
      .pipe(map((response) => response._embedded.products));
  }

  /**
   * Retrieves a list of product categories.
   * @returns An Observable emitting an array of product categories.
   */
  getProductCategories(): Observable<ProductCategory[]> {
    return this.httpClient
      .get<GetResponseProductCategory>(this.categoryUrl)
      .pipe(map((response) => response._embedded.productCategory));
  }

  /**
   * Retrieves product details for a given product ID.
   * @param theProductId - The product ID to retrieve details for.
   * @returns An Observable emitting the product details.
   */
  getProduct(theProductId: number): Observable<Product> {
    // Build URL based on product ID
    const productUrl = `${this.baseUrl}/${theProductId}`;

    return this.httpClient.get<Product>(productUrl);
  }
}

/**
 * Interface for the response from the products API.
 */
interface GetResponseProducts {
  _embedded: {
    products: Product[];
  };
  page: {
    size: number; // Size of the current page
    totalElements: number; // Grand total of all elements in the db.
    totalPages: number; // Total pages available
    number: number; // current page number
  };
}

/**
 * Interface for the response from the product categories API.
 */
interface GetResponseProductCategory {
  _embedded: {
    productCategory: ProductCategory[];
  };
}
