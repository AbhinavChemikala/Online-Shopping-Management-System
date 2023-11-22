#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool searchCustomerByUsername(const std::string& username) {
    std::ifstream infile("customer_data.txt");
    int id;
    std::string name, address, contact, customerUsername, password;
    while (infile >> id >> name >> address >> contact >> customerUsername >> password) {
        if (customerUsername == username) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}
class Customer {
private:
    int customerId;
    std::string customerName;
    std::string customerAddress;
    std::string customerContact;
    std::string customerPassword; // New member variable to store customer's password

public:
    // Constructor to create a new customer
    Customer(int id, const std::string& name, const std::string& address, const std::string& contact, const std::string& password)
        : customerId(id), customerName(name), customerAddress(address), customerContact(contact), customerPassword(password) {}

    // Function to get the customer ID
    int getCustomerId() const {
        return customerId;
    }

    // Function to get the customer name
    std::string getCustomerName() const {
        return customerName;
    }

    // Function to get the customer address
    std::string getCustomerAddress() const {
        return customerAddress;
    }

    // Function to get the customer contact number
    std::string getCustomerContact() const {
        return customerContact;
    }

    // Function to get the customer password
    std::string getCustomerPassword() const {
        return customerPassword;
    }
};
class LoggedInCustomer {
private:
    Customer customer;

public:
    LoggedInCustomer(const Customer& customer)
        : customer(customer) {}

    // Function to get the logged-in customer
    Customer getCustomer() const {
        return customer;
    }
};

// Product class representing a product entity
class Product {
private:
    int productId;
    std::string productName;
    double productRate;

public:
    // Constructor to create a new product
    Product(int id, const std::string& name, double rate)
        : productId(id), productName(name), productRate(rate) {}

    // Function to get the product ID
    int getProductId() const {
        return productId;
    }

    // Function to get the product name
    std::string getProductName() const {
        return productName;
    }

    // Function to get the product rate
    double getProductRate() const {
        return productRate;
    }
};
class ManagerAuthentication {
private:
    std::vector<std::string> managers;

public:
    // Constructor to read managers' credentials from the file
    ManagerAuthentication() {
        std::ifstream infile("managers.txt");
        std::string username, password;
        while (infile >> username >> password) {
            managers.push_back(username + " " + password);
        }
        infile.close();
    }

    // Function to check manager credentials
    bool checkManagerCredentials(const std::string& username, const std::string& password) const {
        for (const auto& manager : managers) {
            if (manager == (username + " " + password)) {
                return true;
            }
        }
        return false;
    }
};
class CustomerAuthentication {
private:
    std::vector<Customer> customers;

public:
    CustomerAuthentication() {
        std::ifstream infile("customer_data.txt");
        int id;
        std::string name, address, contact, password;
        while (infile >> id >> name >> address >> contact >> password) {
            customers.push_back(Customer(id, name, address, contact, password));
        }
        infile.close();
    }

    LoggedInCustomer checkCustomerCredentials(const std::string& username, const std::string& password) const {
        for (const auto& customer : customers) {
            if (customer.getCustomerName() == username && customer.getCustomerPassword() == password) {
                return LoggedInCustomer(customer);
            }
        }
        return LoggedInCustomer(Customer(-1, "", "", "", ""));
    }

    // Function to access the customers vector
    const std::vector<Customer>& getCustomers() const {
        return customers;
    }
};

// Order class representing an order entity
class Order {
private:
    int orderId;
    int customerId;
    std::vector<Product> orderItems;

public:
    // Constructor to create a new order
    Order(int id, int customerID)
        : orderId(id), customerId(customerID) {}

    // Function to get the order ID
    int getOrderId() const {
        return orderId;
    }

    // Function to get the customer ID associated with the order
    int getCustomerId() const {
        return customerId;
    }

    // Function to add a product to the order
    void addProductToOrder(const Product& product) {
        orderItems.push_back(product);
    }

    // Function to get the total order amount
    double getTotalOrderAmount() const {
        double totalAmount = 0.0;
        for (const auto& product : orderItems) {
            totalAmount += product.getProductRate();
        }
        return totalAmount;
    }
};
    void searchProductByID(int productId) {
        // Search for the product in the products.txt file
        std::ifstream infile("products.txt");
        int id;
        std::string name;
        double rate;
        bool found = false;
        while (infile >> id >> name >> rate) {
            if (id == productId) {
                std::cout << "Product found!\n";
                std::cout << "ID: " << id << ", Name: " << name << ", Rate: " << rate << "\n";
                found = true;
                break;
            }
        }
        infile.close();

        if (!found) {
            std::cout << "Product not found.\n";
        }
    }

    std::vector<Product> cart;
    // Function to add a product to the customer's cart
    void addToCart(const Product& product) {
        cart.push_back(product);
        std::cout << "Product added to the cart!\n";
    }

    // Function to display the bill for the items in the cart
    void displayBill() {
        std::cout << "==============\n";
        std::cout << "|Bill Details|\n";
        std::cout << "==============\n";
        double totalAmount = 0.0;
        for (const auto& product : cart) {
            std::cout << "*Product: " << product.getProductName() << ", Rate: $" << product.getProductRate() << "\n";
            totalAmount += product.getProductRate();
        }
        std::cout << "*Total Amount: $" << totalAmount << "\n";
    }
Product searchProducts(int productId);
Product searchProducts(int productId) {
    std::ifstream infile("products.txt");
    int id;
    std::string name;
    double rate;
    while (infile >> id >> name >> rate) {
        if (id == productId) {
            infile.close();
            return Product(id, name, rate);
        }
    }
    infile.close();
    return Product(-1, "", 0.0); // Return a default-constructed product if not found
}

// Function to add a new product
void addProduct() {
    int productId;
    std::string productName;
    double productRate;

    std::cout << "\nEnter new product ID: ";
    std::cin >> productId;

    // Check if the product ID already exists
    if (searchProducts(productId).getProductId() != -1) {
        std::cout << "Product with ID " << productId << " already exists. Please enter a unique product ID.\n";
        return; // Return without adding the product
    }

    std::cout << "Enter new product name: ";
    std::cin.ignore();
    std::getline(std::cin, productName);
    std::cout << "Enter new product rate: ";
    std::cin >> productRate;

    // Create a new Product object and add it to the products.txt file
    Product newProduct(productId, productName, productRate);
    std::ofstream outfile("products.txt", std::ios_base::app);
    outfile << newProduct.getProductId() << " " << newProduct.getProductName() << " " << newProduct.getProductRate() << "\n";
    outfile.close();

    std::cout << "New product added successfully!\n";
}

// Function to delete an existing product
void deleteProduct() {
    int productId;
    std::cout << "\nEnter the ID of the product to delete: ";
    std::cin >> productId;

    // Search for the product in the products.txt file
    Product productToDelete = searchProducts(productId);

    if (productToDelete.getProductId() == -1) {
        std::cout << "Product with ID " << productId << " does not exist.\n";
    } else {
        // Open the products.txt file to read the existing products
        std::ifstream infile("products.txt");
        std::vector<Product> products;
        int id;
        std::string name;
        double rate;
        while (infile >> id >> name >> rate) {
            if (id != productId) {
                products.push_back(Product(id, name, rate));
            }
        }
        infile.close();

        // Write the updated list of products back to the products.txt file
        std::ofstream outfile("products.txt");
        for (const auto& product : products) {
            outfile << product.getProductId() << " " << product.getProductName() << " " << product.getProductRate() << "\n";
        }
        outfile.close();

        std::cout << "Product deleted successfully!\n";
    }
}


// Function to edit an existing product
void editProduct() {
    int productId;
    std::cout << "\nEnter the ID of the product to edit: ";
    std::cin >> productId;

    // Search for the product in the products.txt file
    Product productToEdit = searchProducts(productId);

    if (productToEdit.getProductId() == -1) {
        std::cout << "Product with ID " << productId << " does not exist.\n";
    } else {
        // Prompt the user for new product details
        std::string newName;
        double newRate;
        std::cout << "Enter new product name: ";
        std::cin.ignore();
        std::getline(std::cin, newName);
        std::cout << "Enter new product rate: ";
        std::cin >> newRate;

        // Open the products.txt file to read the existing products
        std::ifstream infile("products.txt");
        std::vector<Product> products;
        int id;
        std::string name;
        double rate;
        while (infile >> id >> name >> rate) {
            if (id == productId) {
                products.push_back(Product(id, newName, newRate));
            } else {
                products.push_back(Product(id, name, rate));
            }
        }
        infile.close();

        // Write the updated list of products back to the products.txt file
        std::ofstream outfile("products.txt");
        for (const auto& product : products) {
            outfile << product.getProductId() << " " << product.getProductName() << " " << product.getProductRate() << "\n";
        }
        outfile.close();

        std::cout << "Product updated successfully!\n";
    }
}
// Function to view all products
void viewProducts() {
    std::cout << "\nList of Products:\n";
    std::ifstream infile("products.txt");
    int id;
    std::string name;
    double rate;
    while (infile >> id >> name >> rate) {
        std::cout << "ID: " << id << ", Name: " << name << ", Rate: " << rate << "\n";
    }
    infile.close();
}
// Function to search for a product
void searchProducts() {
    int productId;
    std::cout << "\nEnter the ID of the product to search: ";
    std::cin >> productId;

    // Open the products.txt file to read the existing products
    std::ifstream infile("products.txt");
    int id;
    std::string name;
    double rate;
    bool found = false;
    while (infile >> id >> name >> rate) {
        if (id == productId) {
            std::cout << "Product found!\n";
            std::cout << "ID: " << id << ", Name: " << name << ", Rate: " << rate << "\n";
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Product not found.\n";
    }
}

void addOrder() {
    int orderId, customerId;
    std::cout << "\nEnter new order ID: ";
    std::cin >> orderId;

    // Open the orders.txt file to check if the order ID already exists
    std::ifstream infile("orders.txt");
    int id;
    while (infile >> id >> customerId) {
        if (id == orderId) {
            std::cout << "Order with ID " << orderId << " already exists. Please enter a unique order ID.\n";
            return; // Return without adding the order
        }
    }
    infile.close();

    std::cout << "Enter customer ID for the order: ";
    std::cin >> customerId;

    // Create a new Order object
    Order newOrder(orderId, customerId);

    // Add products to the order
    int productId;
    char addMore;
    do {
        std::cout << "Enter product ID to add to the order: ";
        std::cin >> productId;

        // Search for the product with the given ID in the products.txt file
        Product productToAdd = searchProducts(productId);
        if (productToAdd.getProductId() != -1) {
            newOrder.addProductToOrder(productToAdd);
        } else {
            std::cout << "Product not found. Please enter a valid product ID.\n";
        }

        std::cout << "Add more products to the order? (Y/N): ";
        std::cin >> addMore;
    } while (addMore == 'Y' || addMore == 'y');

    // Calculate and display the total order amount
    std::cout << "Order added successfully!\n";
    double totalAmount = newOrder.getTotalOrderAmount();
    std::cout << "Total Order Amount: $" << totalAmount << "\n";

    // Save the order details to the orders.txt file
    std::ofstream outfile("orders.txt", std::ios_base::app);
    outfile << newOrder.getOrderId() << " " << newOrder.getCustomerId() << " " << totalAmount << "\n";
    outfile.close();
}


// Function to delete an existing order
void deleteOrder() {
    int orderId;
    std::cout << "\nEnter the ID of the order to delete: ";
    std::cin >> orderId;

    // Open the orders.txt file to read the existing orders
    std::ifstream infile("orders.txt");
    std::vector<std::string> orders;
    int id, customerId;
    double totalAmount;
    bool found = false; // Add a flag to track whether the order is found or not
    while (infile >> id >> customerId >> totalAmount) {
        if (id != orderId) {
            orders.push_back(std::to_string(id) + " " + std::to_string(customerId) + " " + std::to_string(totalAmount));
        } else {
            found = true;
        }
    }
    infile.close();

    // Write the updated list of orders back to the orders.txt file
    std::ofstream outfile("orders.txt");
    for (const auto& order : orders) {
        outfile << order << "\n";
    }
    outfile.close();

    if (found) {
        std::cout << "Order deleted successfully!\n";
    } else {
        std::cout << "Order with ID " << orderId << " does not exist.\n";
    }
}


// Function to edit an existing order
// Function to edit an existing order
void editOrder() {
    int orderId;
    std::cout << "\nEnter the ID of the order to edit: ";
    std::cin >> orderId;

    // Open the orders.txt file to read the existing orders
    std::ifstream infile("orders.txt");
    std::vector<std::string> orders;
    int id, customerId;
    double totalAmount;
    bool found = false; // Add a flag to track whether the order is found or not
    while (infile >> id >> customerId >> totalAmount) {
        if (id == orderId) {
            // Prompt the user for new order details
            int newCustomerId;
            double newTotalAmount;
            std::cout << "Enter new customer ID for the order: ";
            std::cin >> newCustomerId;
            std::cout << "Enter new total order amount: ";
            std::cin >> newTotalAmount;

            // Append the updated order details to the orders vector
            orders.push_back(std::to_string(id) + " " + std::to_string(newCustomerId) + " " + std::to_string(newTotalAmount));
            found = true;
        } else {
            // Add other orders as they are to the orders vector
            orders.push_back(std::to_string(id) + " " + std::to_string(customerId) + " " + std::to_string(totalAmount));
        }
    }
    infile.close();

    // Write the updated list of orders back to the orders.txt file
    std::ofstream outfile("orders.txt");
    for (const auto& order : orders) {
        outfile << order << "\n";
    }
    outfile.close();

    if (found) {
        std::cout << "Order updated successfully!\n";
    } else {
        std::cout << "Order with ID " << orderId << " does not exist.\n";
    }
}
// Function to view all orders
void viewOrders() {
    std::cout << "\nList of Orders:\n";
    std::ifstream infile("orders.txt");
    int id, customerId;
    double totalAmount;
    while (infile >> id >> customerId >> totalAmount) {
        std::cout << "Order ID: " << id << ", Customer ID: " << customerId << ", Total Amount: $" << totalAmount << "\n";
    }
    infile.close();
}

// Function to search for an order
void searchOrders() {
    int orderId;
    std::cout << "\nEnter the ID of the order to search: ";
    std::cin >> orderId;

    // Open the orders.txt file to read the existing orders
    std::ifstream infile("orders.txt");
    int id, customerId;
    double totalAmount;
    bool found = false;
    while (infile >> id >> customerId >> totalAmount) {
        if (id == orderId) {
            std::cout << "Order found!\n";
            std::cout << "Order ID: " << id << ", Customer ID: " << customerId << ", Total Amount: $" << totalAmount << "\n";
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Order not found.\n";
    }
}

// Function to add a new manager
void addManager() {
    std::string managerUsername, managerPassword;
    std::cout << "\nEnter new manager's username: ";
    std::cin >> managerUsername;
    std::cout << "Enter new manager's password: ";
    std::cin >> managerPassword;

    // Append the new manager's credentials to the managers.txt file
    std::ofstream outfile("managers.txt", std::ios_base::app);
    outfile << managerUsername << " " << managerPassword << "\n";
    outfile.close();

    std::cout << "New manager added successfully!\n";
}
void editManager() {
    std::string managerUsername;
    std::cout << "\nEnter the username of the manager to edit: ";
    std::cin >> managerUsername;

    // Open the managers.txt file to read the existing managers
    std::ifstream infile("managers.txt");
    std::vector<std::string> managers;
    std::string username, password;
    bool found = false;
    while (infile >> username >> password) {
        if (username != managerUsername) {
            managers.push_back(username + " " + password);
        } else {
            found = true;

            // Prompt the user for the new manager password
            std::string newManagerPassword;
            std::cout << "Enter new password for the manager: ";
            std::cin >> newManagerPassword;

            // Append the updated manager's credentials to the managers vector
            managers.push_back(username + " " + newManagerPassword);
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Manager with username " << managerUsername << " does not exist.\n";
        return;
    }

    // Write the updated list of managers back to the managers.txt file
    std::ofstream outfile("managers.txt");
    for (const auto& manager : managers) {
        outfile << manager << "\n";
    }
    outfile.close();

    std::cout << "Manager password updated successfully!\n";
}
// Function to delete an existing manager
void deleteManager() {
    std::string managerUsername;
    std::cout << "\nEnter the username of the manager to delete: ";
    std::cin >> managerUsername;

    // Open the managers.txt file to read the existing managers
    std::ifstream infile("managers.txt");
    std::vector<std::string> managers;
    std::string username, password;
    bool found = false;
    while (infile >> username >> password) {
        if (username != managerUsername) {
            managers.push_back(username + " " + password);
        } else {
            found = true;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Manager with username " << managerUsername << " does not exist.\n";
        return;
    }

    // Write the updated list of managers back to the managers.txt file
    std::ofstream outfile("managers.txt");
    for (const auto& manager : managers) {
        outfile << manager << "\n";
    }
    outfile.close();

    std::cout << "Manager deleted successfully!\n";
}


// Function to display all managers
void viewManagers() {
    std::cout << "\nList of Managers:\n";
    std::ifstream infile("managers.txt");
    std::string username, password;
    while (infile >> username >> password) {
        std::cout << "Username: " << username << ", Password: " << password << "\n";
    }
    infile.close();
}
std::vector<Customer> customers; // Vector to store the customers
// Function to add a new customer
void addCustomer() {
    int customerId;
    std::string customerName, customerAddress, customerContact, customerPassword; // Add password input variable

    std::cout << "\nEnter new customer ID: ";
    std::cin >> customerId;

    // Check if the customer ID already exists
    for (const auto& customer : customers) {
        if (customer.getCustomerId() == customerId) {
            std::cout << "Customer with ID " << customerId << " already exists. Please enter a unique customer ID.\n";
            return; // Return without adding the customer
        }
    }

    std::cout << "Enter new customer name: ";
    std::cin.ignore();
    std::getline(std::cin, customerName);

    std::cout << "Enter new customer address: ";
    std::getline(std::cin, customerAddress);

    std::cout << "Enter new customer contact number: ";
    std::getline(std::cin, customerContact);

    // Get customer password from input
    std::cout << "Enter new customer password: ";
    std::cin >> customerPassword;

    // Create a new Customer object and add it to the customers vector
    Customer newCustomer(customerId, customerName, customerAddress, customerContact, customerPassword);
    customers.push_back(newCustomer);

    // Save the new customer data to the "customer_data.txt" file
    std::ofstream outfile("customer_data.txt", std::ios_base::app);
    outfile << newCustomer.getCustomerId() << " " << newCustomer.getCustomerName() << " "
            << newCustomer.getCustomerAddress() << " " << newCustomer.getCustomerContact()
            << " " << newCustomer.getCustomerPassword() << "\n";
    outfile.close();

    std::cout << "New customer added successfully!\n";
}
// Function to edit an existing customer's password
void editCustomer(const std::string& customerUsername) {
    // Open the customer_data.txt file to read the existing customers
    std::ifstream infile("customer_data.txt");
    std::vector<Customer> customers;
    int id;
    std::string name, address, contact, username, password;
    bool found = false;
    while (infile >> id >> name >> address >> contact >> username >> password) {
        if (username != customerUsername) {
            customers.push_back(Customer(id, name, address, contact, password));
        } else {
            // Prompt the user for the new customer password
            std::string newCustomerPassword;
            std::cout << "Enter new password for the customer: ";
            std::cin >> newCustomerPassword;

            // Append the updated customer's data to the customers vector
            customers.push_back(Customer(id, name, address, contact, newCustomerPassword));
            found = true;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Customer with username " << customerUsername << " does not exist.\n";
        return;
    }

    // Write the updated list of customers back to the customer_data.txt file
    std::ofstream outfile("customer_data.txt");
    for (const auto& customer : customers) {
        outfile << customer.getCustomerId() << " " << customer.getCustomerName() << " "
                << customer.getCustomerAddress() << " " << customer.getCustomerContact()
                << " " << customer.getCustomerName() << " " << customer.getCustomerPassword() << "\n";
    }
    outfile.close();

    std::cout << "Customer password updated successfully!\n";
}


// Function to delete an existing customer
// Function to delete an existing customer
void deleteCustomer(const std::string& customerUsername) {
    // Open the customer_data.txt file to read the existing customers
    std::ifstream infile("customer_data.txt");
    std::vector<Customer> customers;
    int id;
    std::string name, address, contact, username, password;
    bool found = false;
    while (infile >> id >> name >> address >> contact >> username >> password) {
        if (username != customerUsername) {
            customers.push_back(Customer(id, name, address, contact, password));
        } else {
            found = true;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Customer with username " << customerUsername << " does not exist.\n";
        return;
    }

    // Write the updated list of customers back to the customer_data.txt file
    std::ofstream outfile("customer_data.txt");
    for (const auto& customer : customers) {
        outfile << customer.getCustomerId() << " " << customer.getCustomerName() << " "
                << customer.getCustomerAddress() << " " << customer.getCustomerContact()
                << " " << customer.getCustomerName() << " " << customer.getCustomerPassword() << "\n";
    }
    outfile.close();

    std::cout << "Customer deleted successfully!\n";
}


// Function to display all customers
// Function to display all customers
void viewCustomers() {
    CustomerAuthentication customerAuth;
    const std::vector<Customer>& customers = customerAuth.getCustomers();

    if (customers.empty()) {
        std::cout << "No customers found.\n";
        return;
    }

    std::cout << "\nList of Customers:\n";
    for (const auto& customer : customers) {
        std::cout << "ID: " << customer.getCustomerId()
                  << ", Name: " << customer.getCustomerName()
                  << ", Address: " << customer.getCustomerAddress()
                  << ", Contact: " << customer.getCustomerContact() << "\n";
    }
}
// Function to search for a manager
void searchManager() {
    std::string managerUsername;
    std::cout << "\nEnter the username of the manager to search: ";
    std::cin >> managerUsername;

    // Open the managers.txt file to read the existing managers
    std::ifstream infile("managers.txt");
    std::string username, password;
    bool found = false;
    while (infile >> username >> password) {
        if (username == managerUsername) {
            std::cout << "Manager found!\n";
            std::cout << "Username: " << username << ", Password: " << password << "\n";
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Manager with username " << managerUsername << " does not exist.\n";
    }
}
// Function to search for a customer
// Function to search for a customer
void searchCustomer(const std::string& customerUsername) {
    std::ifstream infile("customer_data.txt");
    int id;
    std::string name, address, contact, username, password;
    bool found = false;
    while (infile >> id >> name >> address >> contact >> username >> password) {
        if (username == customerUsername) {
            std::cout << "Customer found!\n";
            std::cout << "ID: " << id << ", Name: " << name << ", Address: " << address
                      << ", Contact: " << contact << ", Username: " << username << ", Password: " << password << "\n";
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        std::cout << "Customer with username " << customerUsername << " does not exist.\n";
    }
}




// Admin functionality menu
// Admin functionality menu
void adminFunctionality() {
    int choice;
    do {
        std::cout << "|--------------------------|\n";
        std::cout << "|      Admin Panel         |\n";     
        std::cout << "|--------------------------|\n";
        std::cout << "|1. Add Manager            |\n";
        std::cout << "|2. Edit Manager Password  |\n";
        std::cout << "|3. Delete Manager         |\n";
        std::cout << "|4. View Managers          |\n";
        std::cout << "|5. Search Manager         |\n"; // Option to search for a manager
        std::cout << "|6. Add Customer           |\n";
        std::cout << "|7. Edit Customer Password |\n";
        std::cout << "|8. Delete Customer        |\n";
        std::cout << "|9. View Customers         |\n";
        std::cout << "|10. Search Customer       |\n"; // Option to search for a customer
        std::cout << "|11. Back                  |\n";
        std::cout << "|--------------------------|\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: // Add Manager
                addManager();
                break;
            case 2: // Edit Manager Password
                editManager();
                break;
            case 3: // Delete Manager
                deleteManager();
                break;
            case 4: // View Managers
                viewManagers();
                break;
            case 5: // Search Manager
                searchManager();
                break;
            case 6: // Add Customer
                addCustomer();
                break;
            case 7: // Edit Customer Password
                {
                    std::string customerUsername;
                    std::cout << "Enter the username of the customer to edit: ";
                    std::cin >> customerUsername;
                    editCustomer(customerUsername);
                }
                break;
            case 8: // Delete Customer
                {
                    std::string customerUsername;
                    std::cout << "Enter the username of the customer to delete: ";
                    std::cin >> customerUsername;
                    deleteCustomer(customerUsername);
                }
                break;
            case 9: // View Customers
                viewCustomers();
                break;
            case 10: // Search Customer
                {
                    std::string customerUsername;
                    std::cout << "Enter the username of the customer to search: ";
                    std::cin >> customerUsername;
                    searchCustomer(customerUsername);
                }
                break;
            case 11: // Exit Admin Functionality
                std::cout << "Exiting\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);
}

// Manager functionality menu
void managerFunctionality() {
    // Initialize the manager authentication object with the managers' credentials
    ManagerAuthentication managerAuth;

    int choice;
    do {
        std::cout << "|----------------------------------|\n";
        std::cout << "|           Manager Panel          |\n";
        std::cout << "|----------------------------------|\n";
        std::cout << "|1.  Product: Add                  |\n";
        std::cout << "|2.  Product: Delete               |\n";
        std::cout << "|3.  Product: Edit                 |\n";
        std::cout << "|4.  Product: View                 |\n";
        std::cout << "|5.  Product: Search               |\n";
        std::cout << "|6.  Order: Add                    |\n";
        std::cout << "|7.  Order: Delete                 |\n";
        std::cout << "|8.  Order: Edit                   |\n";
        std::cout << "|9.  Order: View                   |\n";
        std::cout << "|10. Order: Search                 |\n";
        std::cout << "|11. Back                          |\n";
        std::cout << "|----------------------------------|\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: // Product: Add
                addProduct();
                break;
            case 2: // Product: Delete
                deleteProduct();
                break;
            case 3: // Product: Edit
                editProduct();
                break;
            case 4: // Product: View
                viewProducts();
                break;
            case 5: // Product: Search
                searchProducts();
                break;
            case 6: // Order: Add
                addOrder();
                break;
            case 7: // Order: Delete
                deleteOrder();
                break;
            case 8: // Order: Edit
                editOrder();
                break;
            case 9: // Order: View
                viewOrders();
                break;
            case 10: // Order: Search
                searchOrders();
                break;
            case 11: // Exit Manager Functionality
                std::cout << "Exiting Manager Functionality.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);
}
// Customer functionality menu
void customerFunctionality() {
    std::string username, password;
    std::cout << "Enter your customer username: ";
    std::cin >> username;
    std::cout << "Enter your customer password: ";
    std::cin >> password;

    // Check customer credentials using CustomerAuthentication
    CustomerAuthentication customerAuth;
    LoggedInCustomer loggedInCustomer = customerAuth.checkCustomerCredentials(username, password);

    if (loggedInCustomer.getCustomer().getCustomerId() != -1) {
        std::cout << "Customer login successful.\n";
        Customer customer = loggedInCustomer.getCustomer();

        int choice;
        do {
            std::cout << "|--------------------------|\n";
            std::cout << "|     Customer Panel       |\n";
            std::cout << "|--------------------------|\n";
            std::cout << "|1. Search Product         |\n";
            std::cout << "|2. Add Product to Cart    |\n";
            std::cout << "|3. Display Bill           |\n";
            std::cout << "|4. Back                   |\n";
            std::cout << "|--------------------------|\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1: // Search Product
                    int productId;
                    std::cout << "Enter the ID of the product to search: ";
                    std::cin >> productId;
                    searchProductByID(productId);
                    break;
                case 2: // Add Product to Cart
                    std::cout << "Enter the ID of the product to add to the cart: ";
                    std::cin >> productId;
                    {
                        Product productToAdd = searchProducts(productId);
                        if (productToAdd.getProductId() != -1) {
                            addToCart(productToAdd);
                        } else {
                            std::cout << "Product not found. Please enter a valid product ID.\n";
                        }
                    }
                    break;
                case 3: // Display Bill
                    displayBill();
                    break;
                case 4: // Exit Customer Functionality
                    std::cout << "Exiting Customer Functionality.\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    } else {
        std::cout << "Invalid credentials. Customer login failed!\n";
    }
}



class Authentication {
private:
    std::string adminUsername;
    std::string adminPassword;
    bool isAdminLoggedIn;

public:
    Authentication(const std::string& adminUsername, const std::string& adminPassword)
        : adminUsername(adminUsername), adminPassword(adminPassword), isAdminLoggedIn(false) {}

    bool checkAdminCredentials(const std::string& username, const std::string& password) {
        return (username == adminUsername && password == adminPassword);
    }

    void adminLogin() {
        std::string username, password;
        std::cout << "\nEnter Admin Username: ";
        std::cin >> username;
        std::cout << "Enter Admin Password: ";
        std::cin >> password;

        if (checkAdminCredentials(username, password)) {
            isAdminLoggedIn = true;
            std::cout << "Admin login successful!\n";
        } else {
            std::cout << "Invalid credentials. Admin login failed!\n";
        }
    }

    bool getIsAdminLoggedIn() const {
        return isAdminLoggedIn;
    }
};
ManagerAuthentication managerAuth;

int main() {
    // Authentication information
    std::string adminUsername = "admin";
    std::string adminPassword = "admin";
    Authentication auth(adminUsername, adminPassword);

    while (true) {
        int choice;
        std::cout << "|************************************************|\n";
        std::cout << "|Welcome to the Online Shopping Management System|\n";
        std::cout << "|************************************************|\n";
        std::cout << "|1. Admin Login                                  |\n";
        std::cout << "|2. Manager Login                                |\n";
        std::cout << "|3. Customer Login                               |\n";
        std::cout << "|4. Exit                                         |\n";
        std::cout << "|------------------------------------------------|\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string username, password;
            std::cout << "Enter your admin username: ";
            std::cin >> username;
            std::cout << "Enter your admin password: ";
            std::cin >> password;

            // Check if admin login is successful
            if (auth.checkAdminCredentials(username, password)) {
                std::cout << "Admin login successful.\n";
                adminFunctionality(); // Call the admin functionality
            } else {
                std::cout << "Invalid username or password.\n";
            }
        } else if (choice == 2) {
            std::string username, password;
            std::cout << "Enter your manager username: ";
            std::cin >> username;
            std::cout << "Enter your manager password: ";
            std::cin >> password;

            // Check if manager login is successful
            if (managerAuth.checkManagerCredentials(username, password)) {
                std::cout << "Manager login successful.\n";
                managerFunctionality(); // Call the manager functionality
            } else {
                std::cout << "Invalid username or password.\n";
            }
            std::cout << "Manager login\n";
        } else if (choice == 3) {
            customerFunctionality();
            std::cout << "Customer login\n";
        } else if (choice == 4) {
            std::cout << "Thank you for using the Online Shopping Management System. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
