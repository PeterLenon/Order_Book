#ifndef PRIORITY_QUEQUE_H
#define PRIORITY_QUEQUE_H

template <typename T>
class priority_queue{
    private:
    void mergeSort();
    public:
    priority_queue();
    void push(T value1);
    T top();
    void pop();
};
#endif