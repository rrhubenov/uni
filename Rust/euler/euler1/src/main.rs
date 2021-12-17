

fn is_divisible_by_3(x: i32) -> bool {
    x % 3 == 0
}

fn is_divisible_by_5(x: i32) -> bool {
    x % 5 == 0
}

fn main() {
    let mut sum = 0;
    for i in 3..1000 {
        if is_divisible_by_3(i) || is_divisible_by_5(i) {
            sum += i;
        }
    }

    println!("{}", sum);
}
