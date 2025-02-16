#include <iostream>
#include <string>
using namespace std;

class Item{
private:
    string name;
    float price;
    bool available;
    int id;
    
public:
    Item(){
        name = "";
        price = 0;
        available = true;
        id = 0;
    }
    
    
    Item(int itemId, string itemName, float itemPrice){
        id = itemId;
        name = itemName;
        price = itemPrice;
        available = true;
    }
    
    void addItem(int itemId){
        id = itemId;
        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter price: Rs.";
        cin >> price;
        available = true;
    }
    
    void displayItem(){
        cout << id << ". " << name << " - Rs." << price;
        cout << " (" << (available ? "Available" : "Out of Stock") << ")" << endl;
    }
    
    void updateItem(){
        cout << "\nCurrent details:" << endl;
        displayItem();
        float newPrice;
        cout << "Enter new price: Rs.";
        while(!(cin >> newPrice)){
            cout << "Invalid input. Please enter a number: Rs.";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        price = newPrice;
        cout << "Item updated successfully!" << endl;
    }
    
    int getId(){ return id; }
    string getName(){ return name; }
    float getPrice(){ return price; }
    bool isAvailable(){ return available; }
};



class Order{
private:
    static const int MAX_ITEMS = 10;
    string items[MAX_ITEMS];
    float prices[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount;
    float totalAmount;
    string customerAddress;
    string paymentMethod;
    
public:
    Order(){
        itemCount = 0;
        totalAmount = 0;
    }
    
    void addOrderItem(string name, float price, int quantity){
        if (itemCount < MAX_ITEMS){
            items[itemCount] = name;
            prices[itemCount] = price;
            quantities[itemCount] = quantity;
            totalAmount += price * quantity;
            itemCount++;
        }
    }
    
    void setDeliveryInfo(){
        cout << "\nEnter delivery address: ";
        cin.ignore();
        getline(cin, customerAddress);
        
        cout << "\nSelect payment method:" << endl;
        cout << "1. Cash on Delivery" << endl;
        cout << "2. Credit Card" << endl;
        int choice;
        do {
            cout << "Enter choice (1-3): ";
            cin >> choice;
            switch(choice) {
                case 1: paymentMethod = "Cash on Delivery"; break;
                case 2: paymentMethod = "Credit Card"; break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice < 1 || choice > 3);
    }
    
    void displayOrderSummary(){
        cout << "\n=== Order Summary ===" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << items[i] << " x" << quantities[i] << " - Rs." << prices[i] * quantities[i] << endl;
        }
        cout << "------------------------" << endl;
        cout << "Total Amount: Rs." << totalAmount << endl;
        cout << "Delivery Address: " << customerAddress << endl;
        cout << "Payment Method: " << paymentMethod << endl;
    }
};

class Restaurant{
private:
    static const int MAX_ITEMS = 50;
    Item menu[MAX_ITEMS];
    int itemCount;
    
    void initializeDefaultMenu(){
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
    Restaurant(){
        initializeDefaultMenu();
    }
    
    void addMenuItem(){
        if (itemCount < MAX_ITEMS){
            menu[itemCount].addItem(itemCount + 1);
            itemCount++;
            cout << "Item added successfully!" << endl;
        } else{
            cout << "Menu is full!" << endl;
        }
    }

    void displayMenu(){
        cout << "\n=== Our Menu ===" << endl;
        cout << "----------------------------------------" << endl;
        
        cout << "Regular Menu:" << endl;
        for (int i = 0; i < 10; i++) {  
            menu[i].displayItem();
        }
        
        if (itemCount > 10) {
            cout << "\nSpecial Items:" << endl;
            for (int i = 10; i < itemCount; i++) {
                menu[i].displayItem();
            }
        }
        cout << "----------------------------------------" << endl;
    }
    
    void updateItem(){
        displayMenu();
        int id;
        cout << "Enter item ID to update: ";
        while(!(cin >> id)) {
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
        if (!found){
            cout << "Item not found!" << endl;
        }
    }
    
    void deleteItem(){
        displayMenu();
        int id;
        cout << "Enter item ID to delete: ";
        cin >> id;
        
        if (id <= 10){
            cout << "Cannot delete items from regular menu!" << endl;
            return;
        }
        
        for (int i = 0; i < itemCount; i++){
            if (menu[i].getId() == id) {
                for (int j = i; j < itemCount - 1; j++) {
                    menu[j] = menu[j + 1];
                }
                itemCount--;
                cout << "Item deleted successfully!" << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }
    
    Order* placeOrder(){
        Order* newOrder = new Order();
        char addMore;
        
        do{
            displayMenu();
            int id, quantity;
            cout << "Enter item ID to order: ";
            cin >> id;
            
            bool found = false;
            for (int i = 0; i < itemCount; i++){
                if (menu[i].getId() == id && menu[i].isAvailable()){
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    newOrder->addOrderItem(menu[i].getName(), menu[i].getPrice(), quantity);
                    found = true;
                    break;
                }
            }
            
            if (!found){
                cout << "Item not found or not available!" << endl;
            }
            
            cout << "Add more items? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
        
        newOrder->setDeliveryInfo();
        return newOrder;
    }
};


class FoodOrderSystem{
private:
    Restaurant restaurant;
    
public:
    void ownerMenu() {
        int choice;
        do {
            cout << "\n=== Owner Menu ===" << endl;
            cout << "1. Add Item" << endl;
            cout << "2. Display Menu" << endl;
            cout << "3. Update Item" << endl;
            cout << "4. Delete Item" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch(choice) {
                case 1: restaurant.addMenuItem(); break;
                case 2: restaurant.displayMenu(); break;
                case 3: restaurant.updateItem(); break;
                case 4: restaurant.deleteItem(); break;
                case 5: cout << "Exiting..." << endl; break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 5);
    }
    
    void customerMenu() {
        int choice;
        do {
            cout << "\n=== Customer Menu ===" << endl;
            cout << "1. View Menu" << endl;
            cout << "2. Place Order" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            
            switch(choice) {
                case 1:
                    restaurant.displayMenu();
                    break;
                case 2: {
                    Order* order = restaurant.placeOrder();
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
};

int main() {
    FoodOrderSystem system;
    int choice;
    
    do {
        cout << "\n=== Food Ordering System ===" << endl;
        cout << "1. Owner" << endl;
        cout << "2. Customer" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                system.ownerMenu();
                break;
            case 2:
                system.customerMenu();
                break;
            case 3:
                cout << "Thank you for using our system!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);
    
    return 0;
}