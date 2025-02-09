#include<iostream>
using namespace std;

class MenuItem{
    protected:
        string id, name, category;
        int price;
    public:
        void displayItem(){

        }    
};

class Menu{
    public:
        void addItem(){

        }
        void removeItem(){

        }
        void displayMenu(){
            
        }
        void getItemByID(){

        }
};

class User{
    protected:
        string username, password;
    public:
        void login(){

        }   
        void logout(){

        } 
};

class Customer : public User{
    protected:
        string orderHistory;
    public:
        void placeOrder(){

        }   
        void viewOrderHistory(){

        } 
};

class Admin : public User{
    public:
        void addMenuItem(){

        }
        void removeMenuItem(){

        }
        void modifyMenuItem(){

        }
        void viewAllOrders(){
            
        }
};

int main(){
    
}