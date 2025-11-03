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

fn main() {
    println!("Hello, world!");
    // let duck1 = Duck();
    let t = Trade {price: 1, ask_order_id: 2, bid_order_id: 2, quantity: 5};
    println!("{}", t.get_price());
    println!("{}", t.get_quantity());
    println!("{}", t.get_bid_order_id());
    println!("{}", t.get_ask_order_id());
}




