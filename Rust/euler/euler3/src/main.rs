fn is_prime(x: i64) -> bool {
    // Expects non even numbers
    for i in (3..x).step_by(2) {
        if x % i == 0 {
            return false
        }
    }
    true
}

fn main() {
    let mut max = 0;
    let mut value: i64 = 600851475143;
    for i in (1..value).step_by(2) {
        if value == 1 {
            break;
        }
        if value % i == 0  {
            value = value / i;
            if is_prime(i) {
                max = i;
            }
        }

    }

    println!("{}", max);
}
