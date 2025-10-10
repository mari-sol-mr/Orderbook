
#include "OrderBookTypes.h"
#include <vector>
#include <map>

// Generic max heap and min heap templates
#include <queue>
#include <functional>



class OrderBook
{
public:
    OrderBook()
    : totalOrders_ { 0 }
    { }

    void submitOrderRequest(OrderType orderType, MarketSide marketSide, Price price, Quantity quantity)
    {
        OrderPointer newOrder = createOrder(orderType, marketSide, price, quantity);

        logOrder(newOrder);

    }

    OrderPointer createOrder(OrderType orderType, MarketSide marketSide, Price price, Quantity quantity)
    {
        OrderId orderId = totalOrders_ + 1;

        return std::make_shared<Order>(orderId, orderType, marketSide, price, quantity);
    }

    void logOrder(OrderPointer order)
    {
        orderHistory_.push_back(order);
    }

    // NEXT STEP: finish match and print trade ( what orders were matched and  how much was traded for each)
    void matchOrder(OrderPointer order)
    {
        // TradePointers trades = nullptr;

        // switch (order->getMarketSide())
        // {
        //     case MarketSide::Buy:
        //     {
        //         while (!asks_.empty() && order->getRemainingQuantity() > 0)
        //         {
        //             // get best ask at that price
        //             OrderPointer bestAsk = asks_[order->getPrice()].front();

        //             Quantity quantityToTrade = min(order->getRemainingQuantity(), bestAsk->getRemainingQuantity());
        //             bestAsk->fillOrder(quantityToTrade);
        //             order->fillOrder(quantityToTrade);

        //             if (bestAsk->getRemainingQuantity() == 0)
        //             {
        //                 asks_[order->getPrice()];
        //             }


        //         }
        //     }

        //     // case MarketSide::Sell:

        // }

    }


private:
    int totalOrders_;
    OrderPointers orderHistory_;
    std::map<Price, OrderPointers, std::less<Price>> asks_; // todo: refactor to unfilledAsks and unfilledBids_
    std::map<Price, OrderPointers, std::greater<Price>> bids_;
};


    

// g++ OrderBook.cpp -o OrderBook