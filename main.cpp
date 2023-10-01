#include <string>
#include <queue>
#include <iostream>
#include <ctime>
#include <priority_queque.h>

struct Order{
    int orderID;
    std::string traderID;
    char orderType;
    bool buy;
    bool sell;
    int quantity;
    double price;
    time_t timestamp;
};
std::priority_queue<Order, std::vector<Order>, buy_greater> buyOrders;
std::priority_queue<Order, std::vector<Order>, sell_greater> sellOrders;
struct buy_greater{                                                      
    bool greater(const Order& a, const Order& b){
        return a.price > b.price;
    }
};
struct sell_greater{                                                    
    bool greater(const Order& a, const Order& b){
        return a.price < b.price;
    }
};
void executeOrder(Order* ptr){
    Order ord = *ptr;
    if(ord.sell){
        if(buyOrders.top().quantity == ord.quantity){
            buyOrders.pop();
            std::cout<<"Order "<<buyOrders.top().orderID <<" has been matched with  order "<<ord.orderID<<std::endl;
            std::cout<<"now storing data in the databse"<<std::endl;
        }else if(buyOrders.top().quantity > ord.quantity){
            Order temp = buyOrders.top();
            buyOrders.pop();
            temp.quantity -= ord.quantity;
            buyOrders.push(temp);
        }else{
            int temp = ord.quantity;
            while (0 < temp){
                if (buyOrders.top().quantity > temp){
                    Order t = buyOrders.top();
                    buyOrders.pop();
                    t.quantity -= temp;
                    temp = 0;
                    buyOrders.push(t);
                }else{
                    temp -= buyOrders.top().quantity;
                    buyOrders.pop();
                }
            }
            std::cout<<"Order "<<buyOrders.top().orderID <<" has been matched with  order "<<ord.orderID<<std::endl;
            std::cout<<"now storing data in the databse"<<std::endl;
        }
    }else if (ord.buy){
        if(sellOrders.top().quantity == ord.quantity){
            std::cout<<"Order "<<sellOrders.top().orderID<<" has been matched with "<<ord.orderID<<std::endl;
            std::cout<<"now storing data in the databse"<<std::endl;
        }else if(sellOrders.top().quantity > ord.quantity){
                Order t = sellOrders.top();
                sellOrders.pop();
                t.quantity -= ord.quantity;
                sellOrders.push(t);
        }else{
            int temp = ord.quantity;
            while( temp > 0){    
                if(sellOrders.top().quantity > temp){
                    Order t = sellOrders.top();
                    sellOrders.pop();
                    t.quantity -= temp;
                    temp = 0;
                    sellOrders.push(t);
                }else{
                    temp -= sellOrders.top().quantity;
                    sellOrders.pop();
                }
            }
            std::cout<<"Order "<<sellOrders.top().orderID<<" has been matched with "<<ord.orderID<<std::endl;
            std::cout<<"Now storing data in the database"<<std::endl;
        }
    }
}
std::vector<Order> matchOrder(Order newOrder){
    if (newOrder.orderType == 'L'){
        if(newOrder.buy && newOrder.sell){
            std::cout<<"Invalid order!!"<<std::endl;
        }
        else if(newOrder.buy){
            if(newOrder.price <= 0 || newOrder.quantity <= 0){
                std::cout<<"Invalid order!!"<<std::endl;
            }else{
                buyOrders.push(newOrder);
            }
        }else if(newOrder.sell){
            if(newOrder.price <= 0 || newOrder.quantity <= 0){
                std::cout<<"Invalid order"<<std::endl;
            }else{
                sellOrders.push(newOrder);
            }
        }
    }else if(newOrder.orderType == 'M'){
        if(newOrder.sell && newOrder.buy){
            std::cout<<"Invalid order!!"<<std::endl;
        }
        else if(newOrder.buy){
            executeOrder(&newOrder);
        }
        else if(newOrder.sell){
            executeOrder(&newOrder);
        }
    }
}

class OrderBook{
    private:
    std::priority_queue<Order, std::vector<Order>, buy_greater> buyOrders;
    std::priority_queue<Order, std::vector<Order>, sell_greater> sellOrders;
    priority_queque marketOrd;
    public:
    OrderBook(){}
    std::vector<Order> matchOrder(Order newOrder);
    void cancelOrder(Order ord){
        if(ord.orderType == 'M'){
            int found = marketOrd.binSearch(ord);
            if(found >= 0){
                marketOrd.erase(found);
                std::cout<<"Order has been cancelled!"<<std::endl;
            }else{
                std::cout<<"Order has been executed and cannot be cancelled!"<<std::endl;
            }
        }else if(ord.orderType == 'L'){
            NULL;
        }
    }
};
