#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
    
public:
    User() : username(""), password("") {}
    
    User(const string& username, const string& password) : username(username), password(password) {}
    
    bool authenticate(const string& inputPassword) {
        return password == inputPassword;
    }
    
    string getUsername() const {
        return username;
    }
};

class Owner : public User {
public:
    Owner() : User() {}
    
    Owner(const string& username, const string& password) : User(username, password) {}
};

class Customer : public User {
private:
    string address;
    
public:
    Customer() : User(), address("") {}
    
    Customer(const string& username, const string& password, const string& address = "") 
        : User(username, password), address(address) {}
    
    void setAddress(const string& newAddress) {
        address = newAddress;
    }
    
    string getAddress() const {
        return address;
    }
};

class Item {
private:
    int id;
    string name;
    float price;
    bool available;
    
public:
    Item() : id(0), name(""), price(0), available(true) {}
    
    Item(int itemId, const string& itemName, float itemPrice) 
        : id(itemId), name(itemName), price(itemPrice), available(true) {}
    
    void addItem(int itemId) {
        id = itemId;
        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter price: Rs.";
        cin >> price;
        available = true;
    }
    
    void displayItem() const {
        cout << id << ". " << name << " - Rs." << price;
        cout << " (" << (available ? "Available" : "Out of Stock") << ")" << endl;
    }
    
    void updateItem() {
        cout << "Current details:" << endl;
        displayItem();
        float newPrice;
        cout << "Enter new price: Rs.";
        while(!(cin >> newPrice)) {
            cout << "Invalid input. Please enter a number: Rs.";
            cin.clear();
            cin.ignore();
        }
        price = newPrice;
        cout << "Item updated successfully!" << endl;
    }
    
    void setAvailability(bool status) {
        available = status;
    }
    
    int getId() const { 
        return id; 
    }    
    
    string getName() const { 
        return name; 
    }
    
    float getPrice() const { 
        return price; 
    }
    
    bool isAvailable() const { 
        return available; 
    }
};

class OrderItem {
private:
    string name;
    float price;
    int quantity;
    
public:
    OrderItem() : name(""), price(0), quantity(0) {}
    
    OrderItem(const string& itemName, float itemPrice, int itemQuantity)
        : name(itemName), price(itemPrice), quantity(itemQuantity) {}
    
    float getTotalPrice() const {
        return price * quantity;
    }
    
    void display() const {
        cout << name << " x" << quantity << " - Rs." << getTotalPrice() << endl;
    }
    
    string getName() const {
        return name;
    }
    
    float getPrice() const {
        return price;
    }
    
    int getQuantity() const {
        return quantity;
    }
};

enum PaymentType {
    cashOnDelivery,
    creditCard
};

class Payment {
private:
    PaymentType type;
    string cardNumber; 
    
public:
    Payment() : type(cashOnDelivery), cardNumber("") {}
    
    Payment(PaymentType payType, const string& card = "") 
        : type(payType), cardNumber(card) {}
    
    string getMethod() const {
        if (type == cashOnDelivery) {
            return "Cash on Delivery";
        } else if (type == creditCard) {
            return "Credit Card";
        }
        return "Unknown";
    }
    
    bool processPayment(float amount) {
        if (type == cashOnDelivery) {
            cout << "Payment of Rs." << amount << " will be collected upon delivery." << endl;
            return true;
        } else if (type == creditCard) {
            cout << "Processing payment of Rs." << amount << " with card ending in " 
                 << cardNumber.substr(cardNumber.length() - 4) << endl;
            return true;
        }
        return false;
    }
};

class Order {
private:
    static const int maxItems = 10;
    OrderItem items[maxItems];
    int itemCount;
    string customerAddress;
    Payment payment;
    
public:
    Order() : itemCount(0), customerAddress("") {}
    
    bool addOrderItem(const string& name, float price, int quantity) {
        if (itemCount >= maxItems) {
            cout << "Cannot add more items to this order." << endl;
            return false;
        }
        
        items[itemCount] = OrderItem(name, price, quantity);
        itemCount++;
        return true;
    }
    
    void setDeliveryInfo(const string& address) {
        customerAddress = address;
    }
    
    void setPaymentMethod(PaymentType type, const string& cardNumber = "") {
        payment = Payment(type, cardNumber);
    }
    
    float getTotalAmount() const {
        float total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i].getTotalPrice();
        }
        return total;
    }
    
    bool processPayment() {
        return payment.processPayment(getTotalAmount());
    }
    
    void displayOrderSummary() const {
        cout << "=== Order Summary ===" << endl;
        for (int i = 0; i < itemCount; i++) {
            items[i].display();
        }
        cout << "------------------------" << endl;
        cout << "Total Amount: Rs." << getTotalAmount() << endl;
        cout << "Delivery Address: " << customerAddress << endl;
        cout << "Payment Method: " << payment.getMethod() << endl;
    }
};

class Restaurant {
private:
    static const int maxItems = 50;
    Item menu[maxItems];
    int itemCount;
    
    void initializeDefaultMenu() {
        menu[0] = Item(1, "Margherita Pizza", 299.00);
        menu[1] = Item(2, "Chicken Burger", 199.00);
        menu[2] = Item(3, "French Fries", 99.00);
        menu[3] = Item(4, "Coca Cola", 49.00);
        menu[4] = Item(5, "Chicken Biryani", 249.00);
        menu[5] = Item(6, "Ice Cream", 79.00);
        menu[6] = Item(7, "Garlic Bread", 149.00);
        menu[7] = Item(8, "Pasta", 199.00);
        menu[8] = Item(9, "Green Salad", 129.00);
        menu[9] = Item(10, "Coffee", 89.00);
        itemCount = 10;
    }
    
public:
    Restaurant() : itemCount(0) {
        initializeDefaultMenu();
    }
    
    bool addMenuItem() {
        if (itemCount >= maxItems) {
            cout << "Menu is full!" << endl;
            return false;
        }
        
        menu[itemCount].addItem(itemCount + 1);
        itemCount++;
        cout << "Item added successfully!" << endl;
        return true;
    }

    void displayMenu() const {
        cout << "=== Our Menu ===" << endl;
        cout << "----------------------------------------" << endl;
        
        cout << "Regular Menu:" << endl;
        for (int i = 0; i < 10 && i < itemCount; i++) {  
            menu[i].displayItem();
        }
        
        if (itemCount > 10) {
            cout << "Special Items:" << endl;
            for (int i = 10; i < itemCount; i++) {
                menu[i].displayItem();
            }
        }
        cout << "----------------------------------------" << endl;
    }
    
    void updateItem() {
        displayMenu();
        int id;
        cout << "Enter item ID to update: ";
        while (!(cin >> id)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (menu[i].getId() == id) {
                menu[i].updateItem();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Item not found!" << endl;
        }
    }
    
    void deleteItem() {
        displayMenu();
        int id;
        cout << "Enter item ID to delete: ";
        cin >> id;
        
        if (id <= 10) {
            cout << "Cannot delete items from regular menu!" << endl;
            return;
        }
        
        int foundIndex = -1;
        for (int i = 0; i < itemCount; i++) {
            if (menu[i].getId() == id) {
                foundIndex = i;
                break;
            }
        }
        
        if (foundIndex != -1) {
            for (int i = foundIndex; i < itemCount - 1; i++) {
                menu[i] = menu[i + 1];
            }
            itemCount--;
            cout << "Item deleted successfully!" << endl;
        } else {
            cout << "Item not found!" << endl;
        }
    }
    
    Order* placeOrder(const string& customerAddress) {
        Order* newOrder = new Order();
        char addMore;
        
        do {
            displayMenu();
            int id, quantity;
            cout << "Enter item ID to order: ";
            cin >> id;
            
            bool found = false;
            for (int i = 0; i < itemCount; i++) {
                if (menu[i].getId() == id && menu[i].isAvailable()) {
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    newOrder->addOrderItem(menu[i].getName(), menu[i].getPrice(), quantity);
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                cout << "Item not found or not available!" << endl;
            }
            
            cout << "Add more items? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
        
        newOrder->setDeliveryInfo(customerAddress);
        return newOrder;
    }
};

class AuthManager {
private:
    static const int maxUsers = 10;
    Owner owners[maxUsers];
    int ownerCount;
    Customer customers[maxUsers];
    int customerCount;
    
public:
    AuthManager() : ownerCount(0), customerCount(0) {
        owners[0] = Owner("admin", "owner123");
        ownerCount = 1;
    }
    
    User* login(const string& role) {
        string username, password;
        cout << "--- " << role << " Login ---" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        if (role == "Owner") {
            for (int i = 0; i < ownerCount; i++) {
                if (owners[i].getUsername() == username && owners[i].authenticate(password)) {
                    return &owners[i];
                }
            }
        } else if (role == "Customer") {
            for (int i = 0; i < customerCount; i++) {
                if (customers[i].getUsername() == username && customers[i].authenticate(password)) {
                    return &customers[i];
                }
            }
        }
        return nullptr;
    }
    
    Customer* registerCustomer() {
        if (customerCount >= maxUsers) {
            cout << "Maximum number of customers reached." << endl;
            return nullptr;
        }
        
        string username, password, address;
        cout << "--- Customer Registration ---" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cin.ignore();
        cout << "Enter address: ";
        getline(cin, address);
        
        customers[customerCount] = Customer(username, password, address);
        customerCount++;
        return &customers[customerCount - 1];
    }
};

class FoodOrderSystem {
private:
    Restaurant restaurant;
    AuthManager authManager;
    
public:
    void ownerMenu() {
        User* user = authManager.login("Owner");
        if (!user) {
            cout << "Login failed!" << endl;
            return;
        }
        
        int choice;
        do {
            cout << "=== Owner Menu ===" << endl;
            cout << "Enter 1 to Add Item" << endl;
            cout << "Enter 2 to Display Menu" << endl;
            cout << "Enter 3 to Update Item" << endl;
            cout << "Enter 4 to Delete Item" << endl;
            cout << "Enter 5 to Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: 
                    restaurant.addMenuItem(); 
                    break;
                case 2: 
                    restaurant.displayMenu(); 
                    break;
                case 3: 
                    restaurant.updateItem(); 
                    break;
                case 4: 
                    restaurant.deleteItem(); 
                    break;
                case 5: 
                    cout << "Exiting..." << endl; 
                    break;
                default: 
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 5);
    }
    
    void customerMenu() {
        Customer* customer = nullptr;
        string address;
        
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        int loginChoice;
        cout << "Enter choice: ";
        cin >> loginChoice;
        
        if (loginChoice == 1) {
            User* user = authManager.login("Customer");
            if (!user) {
                cout << "Login failed!" << endl;
                return;
            }
            customer = (Customer*)user;
            address = customer->getAddress();
        } else {
            customer = authManager.registerCustomer();
            if (!customer) {
                return;
            }
            address = customer->getAddress();
        }
        
        int choice;
        cout << "Welcome, " << customer->getUsername() << "! You now have access to the customer menu.\n";
        do {
            cout << "=== Customer Menu ===" << endl;
            cout << "Enter 1 to View Menu" << endl;
            cout << "Enter 2 to Place Order" << endl;
            cout << "Enter 3 to Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    restaurant.displayMenu();
                    break;
                case 2: {
                    Order* order = restaurant.placeOrder(address);
                    
                    cout << "Select payment method:" << endl;
                    cout << "1. Cash on Delivery" << endl;
                    cout << "2. Credit Card" << endl;
                    int paymentChoice;
                    do {
                        cout << "Enter choice (1-2): ";
                        cin >> paymentChoice;
                        
                        if (paymentChoice == 1) {
                            order->setPaymentMethod(cashOnDelivery);
                            break;
                        } else if (paymentChoice == 2) {
                            string cardNumber;
                            cout << "Enter credit card number: ";
                            cin >> cardNumber;
                            order->setPaymentMethod(creditCard, cardNumber);
                            break;
                        } else {
                            cout << "Invalid choice!" << endl;
                        }
                    } while (true);
                    
                    order->processPayment();
                    order->displayOrderSummary();
                    delete order;
                    break;
                }
                case 3:
                    cout << "Thank you for visiting!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 3);
    }
    
    void run() {
        int choice;
        
        do {
            cout << "=== Food Ordering System ===" << endl;
            cout << "Enter 1 to login as Owner" << endl;
            cout << "Enter 2 to continue as Customer" << endl;
            cout << "Enter 3 to Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    ownerMenu();
                    break;
                case 2:
                    customerMenu();
                    break;
                case 3:
                    cout << "Thank You!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 3);
    }
};

int main() {
    FoodOrderSystem system;
    system.run();
    return 0;
}