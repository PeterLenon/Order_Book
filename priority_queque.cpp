#include "priority_queque.h"
#include <vector>
#include <string>

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

priority_queque<Order>::priority_queque(){
    std::vector<Order> marketOrders = (std::vector<Order>){};
}

std::vector<Order> priority_queque<Order>::mergeSort(std::vector<Order> arr, int l, int r){
    if (r - l >= 1){
        int mid = (r+l)/2;
        std::vector <Order> left = mergeSort(arr, l, mid);
        std::vector <Order> right = mergeSort(arr, mid+1,r);
        int le =0;
        int ri = 0;
        std::vector<Order> temp;
        while(le < left.size() && ri < right.size()){
            if (left[le].timestamp >= right[ri].timestamp){
                arr[l] = left[le];
                temp.push_back(arr[l]);
                le++;
                l++;
            }else{
                arr[l] = right[ri];
                temp.push_back(arr[l]);
                ri++;
                l++;
            }
        }
        while(le < left.size()){
            arr[l] = left[le];
            temp.push_back(arr[l]);
            le++;
            l++;
        }
        while(ri < right.size()){
            arr[l] = right[ri];
            temp.push_back(arr[l]);
            ri++;
            l++;
        }
        return temp;
    }else{
        return (std::vector<Order>){arr[(r+l)/2]};
    }
}

void priority_queque<Order>::push(Order o){
    int l = 0;
    int r = marketOrders.size()-1;
    int mid = (l+r)/2;
    if(marketOrders[l].timestamp < o.timestamp){
        marketOrders.insert(marketOrders.begin()+0, o);
    }else if(marketOrders[r].timestamp > o.timestamp){
        marketOrders.push_back(o);
    }else{
        while (l <r){
            if(marketOrders[mid].timestamp > o.timestamp && marketOrders[mid+1].timestamp < o.timestamp){
                marketOrders.insert(marketOrders.begin()+mid +1, o);
            }else if(marketOrders[mid].timestamp > o.timestamp && marketOrders[mid+1].timestamp > o.timestamp){
                l = mid + 1;
            }else if(marketOrders[mid].timestamp < o.timestamp && marketOrders[mid - 1].timestamp > o.timestamp){
                marketOrders.insert(marketOrders.begin()+mid, o);
            }else if(marketOrders[mid].timestamp < o.timestamp && marketOrders[mid-1].timestamp < o.timestamp){
                r = mid -1;
            }
        }
    }
   
}

Order priority_queque<Order>::top(){
    return marketOrders[0];
}

void priority_queque<Order>::pop(){
    marketOrders.erase(marketOrders.begin()+0);
}

int priority_queque<Order>::binSearch(Order ord){
    int l =0;
    int r = marketOrders.size()-1;
    int mid = (l+r)/2;
    if (marketOrders[0].timestamp == ord.timestamp){
        mid = 0;
    }else{
        while(r>=l){
            if(marketOrders[mid-1].timestamp> ord.timestamp && marketOrders[mid] == ord.timestamp){
                break;
            }else if(marketOrders[mid-1].timestamp> ord.timestamp && marketOrders[mid] > ord.timestamp){
                l = mid +1;
            }else if(marketOrders[mid-1].timestamp> ord.timestamp && marketOrders[mid] < ord.timestamp){
                return -1;
            }else if(marketOrders[mid-1].timestamp < ord.timestamp && marketOrders[mid] < ord.timestamp){
                r = mid -1;
            }else if(marketOrders[mid-1].timestamp == ord.timestamp && marketOrders[mid] < ord.timestamp){
                r = mid -1;
            }
        }
    }
    if (r>=l){
        while(marketOrders[mid].timestamp == ord.timestamp){
            if(marketOrders[mid].orderID == ord.orderID){
                return mid;
            }
        }
    }
    return -1;
}
void priority_queque<Order>::erase(int index){
    marketOrders.erase(marketOrders.begin()+index);
}
