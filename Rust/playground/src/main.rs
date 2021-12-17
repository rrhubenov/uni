

#[derive(Debug, Copy, Clone)]
struct SomeStruct {
    integer: i32
}

fn takes_ownership(x: SomeStruct) {
    
}

fn main() {
    let a = SomeStruct { integer: 3_i32 };

    takes_ownership(a);

    println!("{:?}", a);
}
