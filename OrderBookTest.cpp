#include <iostream>
#include <thread>
#include <vector>
#include "OrderBook.h"
#include "OrderBookB.h"

using namespace std;

int main()
{
    OrderBookB ob;

    

    ob.submitOrderRequest(OrderType::Limit, MarketSide::Sell, 5, 2);
    ob.submitOrderRequest(OrderType::Limit, MarketSide::Buy, 5, 1);
    ob.submitOrderRequest(OrderType::Limit, MarketSide::Buy, 5, 1);
    ob.submitOrderRequest(OrderType::Limit, MarketSide::Sell, 5, 1);
    ob.submitOrderRequest(OrderType::Limit, MarketSide::Buy, 5, 1);

    
    ob.printTradeHistory();
    return 0;
}
//g++ OrderBookTest.cpp -o OrderBookTest