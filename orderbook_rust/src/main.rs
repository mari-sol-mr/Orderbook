// trait Quack {
//     fn quack(&self);
// }

// struct Duck (); hgfg

// impl Quack for Duck {
//     fn quack(&self) {
//         println!("quack!");
//     }
// }



enum MarketSide
{
    Buy,
    Sell
}

enum OrderType
{
    Limit,
    Market
}

type Price = i32;
type Quantity = u32;
type OrderId = u64;

// trait GetPrice {
//     fn getPrice(&self) -> Price;
// }

struct Trade {
    price : Price,
    ask_order_id: OrderId,
    bid_order_id: OrderId,
    quantity: Quantity
}

impl Trade {
    fn get_price(&self) -> Price {
        self.price
    }

    fn get_quantity(&self) -> Quantity {
        self.quantity
    }

    fn get_ask_order_id(&self) -> OrderId {
        self.ask_order_id
    }

    fn get_bid_order_id(&self) -> OrderId {
        self.bid_order_id
    }
}

struct Order {
    order_id: OrderId,
    order_type: OrderType,
    market_side: MarketSide,
    price: Price,
    initial_quantity: Quantity,
    remaining_quantity: Quantity
}

impl Order {
    fn get_order_id(&self) -> OrderId {
        self.order_id
    }

    fn get_price(&self) -> Price {
        self.price
    }

    fn get_remaining_quantity(&self) -> Quantity {
        self.remaining_quantity
    }

    fn get_market_side(&self) -> &MarketSide {
        &self.market_side
    }

    fn is_filled(&self) -> bool {
        self.remaining_quantity == 0
    }

    fn fill_order(&mut self, quantity: Quantity) -> () {
        self.remaining_quantity -= quantity;
    }
}

struct OrderBook {
    total_orders: u64
}

impl Default for OrderBook {
    fn default() -> Self {
        Self { total_orders: 0 }
    }
}

impl OrderBook {
    fn submit_market_order_request(&self, market_side: MarketSide, price: Price, quantity: Quantity) -> () {
        let new_order = Order { order_id: self.total_orders + 1, order_type: OrderType::Market, market_side: market_side,
             price: price, initial_quantity: quantity, remaining_quantity: quantity };
    }



}



fn main() {
    println!("Hello, world!");
    // let duck1 = Duck();
    let t = Trade {price: 1, ask_order_id: 2, bid_order_id: 2, quantity: 5};
    println!("{}", t.get_price());
    println!("{}", t.get_quantity());
    println!("{}", t.get_bid_order_id());
    println!("{}", t.get_ask_order_id());


    let ob = OrderBook::default();

}




