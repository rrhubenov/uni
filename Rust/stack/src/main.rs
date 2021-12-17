
mod stack;
use crate::stack::*;

fn main() {
    let mut stack: StaticStack<SomeStruct> = StaticStack::new();

    for i in 0..10 {
        stack.push(
    SomeStruct { 
                data: vec![1, 2, i] 
            }
        )
    }

    while !stack.is_empty() {
        stack.pop();
    }

}
