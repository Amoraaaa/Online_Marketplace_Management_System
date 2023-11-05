#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Define the structures for Seller, Product, Customer, and Cart
struct Seller {
    int id;
    string name;
    string email;
    string password;
};

struct Product {
    int id;
    string name;
    double price;
    string category;
    string description;
    int sellerId;
};

struct Customer {
    int id;
    string name;
    string address;
    string phoneNumber;
    string email;
    string password;
    vector<Product> cart;
};

// Function to display the available product categories
void displayCategories(const vector<string>& categories) {
    cout << "Available Categories: ";
    for (const string& category : categories) {
        cout << category << " ";
    }
    cout << endl;
}

// Function to register a new seller
void registerSeller(vector<Seller>& sellers, ofstream& sellersFile) {
    Seller seller;
    cout << "Enter seller information:" << endl;
    cout << "ID: ";
    cin >> seller.id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, seller.name);
    cout << "Email: ";
    getline(cin, seller.email);
    cout << "Password: ";
    getline(cin, seller.password);
    sellers.push_back(seller);
    sellersFile << seller.id << " " << seller.name << " " << seller.email << " " << seller.password << endl;
    cout << "Seller registered successfully!" << endl;
}

// Function to register a new customer
void registerCustomer(vector<Customer>& customers, ofstream& customersFile) {
    Customer customer;
    cout << "Enter customer information:" << endl;
    cout << "ID: ";
    cin >> customer.id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, customer.name);
    cout << "Address: ";
    getline(cin, customer.address);
    cout << "Phone Number: ";
    getline(cin, customer.phoneNumber);
    cout << "Email: ";
    getline(cin, customer.email);
    cout << "Password: ";
    getline(cin, customer.password);
    customers.push_back(customer);
    customersFile << customer.id << " " << customer.name << " " << customer.address << " " << customer.phoneNumber << " " << customer.email << " " << customer.password << endl;
    cout << "Customer registered successfully!" << endl;
}

// Function to add a new product
void addProduct(vector<Product>& products, ofstream& productsFile, const Seller& seller) {
    Product product;
    cout << "Enter product information:" << endl;
    cout << "ID: ";
    cin >> product.id;
    cin.ignore();
    cout << "Name: ";
    getline(cin, product.name);
    cout << "Price: $";
    cin >> product.price;
    cin.ignore();
    cout << "Category: ";
    getline(cin, product.category);
    cout << "Description: ";
    getline(cin, product.description);
    product.sellerId = seller.id;
    products.push_back(product);
    productsFile << product.id << " " << product.name << " " << product.price << " " << product.category << " " << product.description << " " << product.sellerId << endl;
    cout << "Product added successfully!" << endl;
}

// Function to view all products
void viewAllProducts(const vector<Product>& products) {
    cout << "All Products:" << endl;
    for (const Product& product : products) {
        cout << "ID: " << product.id << " Name: " << product.name << " Price: $" << product.price << " Category: " << product.category << " Description: " << product.description << endl;
    }
}

// Function to validate login credentials for sellers
bool sellerLogin(const vector<Seller>& sellers, const string& email, const string& password) {
    for (const Seller& seller : sellers) {
        if (seller.email == email && seller.password == password) {
            return true;
        }
    }
    return false;
}

// Function to validate login credentials for customers
bool customerLogin(const vector<Customer>& customers, const string& email, const string& password) {
    for (const Customer& customer : customers) {
        if (customer.email == email && customer.password == password) {
            return true;
        }
    }
    return false;
}

// Function to load seller data from files
void loadSellerData(vector<Seller>& sellers, ifstream& sellersFile) {
    Seller seller;
    while (sellersFile >> seller.id) {
        sellersFile.ignore();
        getline(sellersFile, seller.name);
        getline(sellersFile, seller.email);
        getline(sellersFile, seller.password);
        sellers.push_back(seller);
    }
}

// Function to load customer data from files
void loadCustomerData(vector<Customer>& customers, ifstream& customersFile) {
    Customer customer;
    while (customersFile >> customer.id) {
        customersFile.ignore();
        getline(customersFile, customer.name);
        getline(customersFile, customer.address);
        getline(customersFile, customer.phoneNumber);
        getline(customersFile, customer.email);
        getline(customersFile, customer.password);
        customers.push_back(customer);
    }
}

// Function to load product data from files
void loadProductData(vector<Product>& products, ifstream& productsFile) {
    Product product;
    while (productsFile >> product.id) {
        productsFile.ignore();
        getline(productsFile, product.name);
        productsFile >> product.price;
        productsFile.ignore();
        getline(productsFile, product.category);
        getline(productsFile, product.description);
        productsFile >> product.sellerId;
        productsFile.ignore();
        products.push_back(product);
    }
}

// Function to save seller data to files
void saveSellerData(const vector<Seller>& sellers, ofstream& sellersFile) {
    for (const Seller& seller : sellers) {
        sellersFile << seller.id << " " << seller.name << " " << seller.email << " " << seller.password << endl;
    }
}

// Function to save customer data to files
void saveCustomerData(const vector<Customer>& customers, ofstream& customersFile) {
    for (const Customer& customer : customers) {
        customersFile << customer.id << " " << customer.name << " " << customer.address << " " << customer.phoneNumber << " " << customer.email << " " << customer.password << endl;
    }
}

// Function to save product data to files
void saveProductData(const vector<Product>& products, ofstream& productsFile) {
    for (const Product& product : products) {
        productsFile << product.id << " " << product.name << " " << product.price << " " << product.category << " " << product.description << " " << product.sellerId << endl;
    }
}

// Function to add a product to a customer's cart
void addProductToCart(Customer& customer, const Product& product) {
    customer.cart.push_back(product);
    cout << product.name << " added to your cart." << endl;
}

// Function to view a customer's cart
void viewCart(const Customer& customer) {
    if (customer.cart.empty()) {
        cout << "Your cart is empty." << endl;
    }
    else {
        cout << "Your Cart:" << endl;
        for (const Product& product : customer.cart) {
            cout << "Name: " << product.name << " Price: $" << product.price << endl;
        }
    }
}

// Function to checkout a customer's cart
void checkout(Customer& customer) {
    if (customer.cart.empty()) {
        cout << "Your cart is empty. Nothing to checkout." << endl;
    }
    else {
        double totalPrice = 0.0;
        cout << "Your Cart:" << endl;
        for (const Product& product : customer.cart) {
            cout << "Name: " << product.name << " Price: $" << product.price << endl;
            totalPrice += product.price;
        }
        cout << "Total Price: $" << totalPrice << endl;
        cout << "Checkout successful!" << endl;
        customer.cart.clear(); // Clear the cart after checkout
    }
}

int main() {
    // Create and open files for storing data
    ofstream sellersFile("sellers.txt");
    ofstream productsFile("products.txt");
    ofstream customersFile("customers.txt");

    // Load existing seller, customer, and product data from files
    ifstream sellerData("sellers.txt");
    ifstream customerData("customers.txt");
    ifstream productData("products.txt");

    // Initialize data structures to store seller, product, and customer data
    vector<Seller> sellers;
    vector<Product> products;
    vector<Customer> customers;

    // Load existing data from files
    if (sellerData.is_open()) {
        loadSellerData(sellers, sellerData);
    }

    if (customerData.is_open()) {
        loadCustomerData(customers, customerData);
    }

    if (productData.is_open()) {
        loadProductData(products, productData);
    }

    // Initialize available product categories
    vector<string> categories = { "Electronics", "Clothing", "Books", "Home Appliances" };

    // Display the initial menu for registration or login
    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Register as a Seller" << endl;
        cout << "2. Register as a Customer" << endl;
        cout << "3. Seller Login" << endl;
        cout << "4. Customer Login" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            registerSeller(sellers, sellersFile);
            saveSellerData(sellers, sellersFile);
        }
        else if (choice == 2) {
            registerCustomer(customers, customersFile);
            saveCustomerData(customers, customersFile);
        }
        else if (choice == 3) {
            string email, password;
            cout << "Enter seller email: ";
            getline(cin, email);
            cout << "Enter seller password: ";
            getline(cin, password);
            if (sellerLogin(sellers, email, password)) {
                cout << "Seller login successful!" << endl;
                // Perform seller-related actions
                while (true) {
                    cout << "Seller Menu:" << endl;
                    cout << "1. Add Product" << endl;
                    cout << "2. View Products" << endl;
                    cout << "3. Logout" << endl;
                    int sellerChoice;
                    cin >> sellerChoice;
                    cin.ignore();
                    if (sellerChoice == 1) {
                        addProduct(products, productsFile, sellers.back());
                        saveProductData(products, productsFile);
                    }
                    else if (sellerChoice == 2) {
                        viewAllProducts(products);
                    }
                    else if (sellerChoice == 3) {
                        cout << "Seller logout." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice. Please choose a valid option." << endl;
                    }
                }
            }
            else {
                cout << "Seller login failed. Invalid email or password." << endl;
            }
        }
        else if (choice == 4) {
            string email, password;
            cout << "Enter customer email: ";
            getline(cin, email);
            cout << "Enter customer password: ";
            getline(cin, password);
            if (customerLogin(customers, email, password)) {
                cout << "Customer login successful!" << endl;
                // Perform customer-related actions
                while (true) {
                    cout << "Customer Menu:" << endl;
                    cout << "1. Browse Products" << endl;
                    cout << "2. Add Product to Cart" << endl;
                    cout << "3. View Cart" << endl;
                    cout << "4. Checkout" << endl;
                    cout << "5. Logout" << endl;
                    int customerChoice;
                    cin >> customerChoice;
                    cin.ignore();
                    if (customerChoice == 1) {
                        viewAllProducts(products);
                    }
                    else if (customerChoice == 2) {
                        cout << "Enter the ID of the product you want to add to your cart: ";
                        int productId;
                        cin >> productId;
                        cin.ignore();

                        bool found = false;
                        for (const Product& product : products) {
                            if (product.id == productId) {
                                addProductToCart(customers.back(), product);
                                found = true;
                                cout << product.name << " added to your cart." << endl;
                                break;
                            }
                        }

                        if (!found) {
                            cout << "Product not found with the given ID." << endl;
                        }
                    }
                    else if (customerChoice == 3) {
                        viewCart(customers.back());
                    }
                    else if (customerChoice == 4) {
                        checkout(customers.back());
                    }
                    else if (customerChoice == 5) {
                        cout << "Customer logout." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice. Please choose a valid option." << endl;
                    }
                }
            }
            else {
                cout << "Customer login failed. Invalid email or password." << endl;
            }
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    // Close the data files
    sellersFile.close();
    productsFile.close();
    customersFile.close();

    return 0;
}
