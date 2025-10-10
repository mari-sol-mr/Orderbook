
#include "OrderBookTypes.h"
#include <vector>
#include <map>

// Generic max heap and min heap templates
#include <queue>
#include <functional>
#include <thread>



class OrderBookB
{
public:
    OrderBookB()
    : totalOrders_ { 0 }
    { 
        orderHistory_.reserve(100000000);
    }

    void submitOrderRequest(OrderType orderType, MarketSide marketSide, Price price, Quantity quantity)
    {
        OrderPointer newOrder = createOrder(orderType, marketSide, price, quantity);

        logOrder(newOrder);

        matchOrder(newOrder);

    }

    OrderPointer createOrder(OrderType orderType, MarketSide marketSide, Price price, Quantity quantity)
    {
        OrderId orderId = generateOrderId();

        return std::make_shared<Order>(orderId, orderType, marketSide, price, quantity);
    }

    OrderId generateOrderId()
    {
        return ++totalOrders_;
    }

    void logOrder(OrderPointer order)
    {
        orderHistory_.push_back(order);
    }

    void logTrade(TradePointer trade)
    {
        tradeHistory_.push_back(trade);
    }

    TradePointer executeTrade(OrderPointer order1, OrderPointer order2)
    {
        Quantity tradeQuantity = std::min(order1->getRemainingQuantity(), order2->getRemainingQuantity());

        order1->fillOrder(tradeQuantity);
        order2->fillOrder(tradeQuantity);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        return std::make_shared<Trade>(order1->getPrice(), order2->getOrderId(), order1->getOrderId(), tradeQuantity);
    }

    void matchOrder(OrderPointer order)
    {
        OrdersQueue* unfilledOrders = order->getMarketSide() == MarketSide::Buy ? &unfilledAsks_[order->getPrice()] : &unfilledBids_[order->getPrice()]; // todo: refactor. potentialMatches?

        bool matchAvailable = !unfilledOrders->empty();

        while(!order->isFilled() && matchAvailable)
        {
            OrderPointer bestMatch = unfilledOrders->front();

            TradePointer trade = executeTrade(order, bestMatch);
            
            logTrade(trade); // todo: maybe there is some way to optimize this and reserve x space?

            if (bestMatch->isFilled())
            {
                unfilledOrders->pop();
            }

            matchAvailable = !unfilledOrders->empty();
        }

        if (!order->isFilled())
        {
            queueOrder(order);
        }
    }

    void queueOrder(OrderPointer order)
    {
        if (order->getMarketSide() == MarketSide::Buy) 
            unfilledBids_[order->getPrice()].push(order);
        else  
            unfilledAsks_[order->getPrice()].push(order);
    }

    void printTradeHistory()
    {
        std::cout << "printing hist\n";
        for (const auto& trade : tradeHistory_)
        {
            std::cout << "Traded quantity " << trade->getQuantity() << " at price " << trade->getPrice()
            << " with orders " << trade->getAskOrderId() << " and " << trade->getBidOrderId() << "\n"; // todo: create getters
        }
    }


private:
    int totalOrders_;
    OrderPointers orderHistory_; // todo: refactor to orders list
    TradePointers tradeHistory_; // todo: refactor to trades list
    std::map<Price, OrdersQueue, std::less<Price>> unfilledAsks_;
    std::map<Price, OrdersQueue, std::greater<Price>> unfilledBids_;
};


    

// g++ OrderBookB.cpp -o OrderBookB