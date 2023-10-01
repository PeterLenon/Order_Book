#ifndef PRIORITY_QUEQUE_H
#define PRIORITY_QUEQUE_H

template <typename T>
class priority_queque{
    private:
    vector <T> marketOrders;

    public:
    priority_queque();
    template <typename T>
    vector<T> mergeSort(vector<T> arr, int l, int r);
    void push(T value1);
    T top();
    void pop();
    int binSearch(T ord);
    void erase(int i);
};
#endif