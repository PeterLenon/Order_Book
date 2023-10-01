#ifndef PRIORITY_QUEQUE_H
#define PRIORITY_QUEQUE_H

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

class priority_queque{
    private:
    std::vector <Order> marketOrders;
    public:
    priority_queque();
    std::vector<Order> mergeSort(std::vector<Order> arr, int l, int r);
    void push(Order value1);
    Order top();
    void pop();
    int binSearch(Order ord);
    void erase(int i);
};
#endif