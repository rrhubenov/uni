

fn main() {
    let mut fibs = [0, 1];
    let mut sum = 0;

    while fibs[1] < 4_000_000 {
        if fibs[1] % 2 == 0 {
            sum += fibs[1];
        }
        let temp = fibs[1];
        fibs[1] = fibs[0] + fibs[1];
        fibs[0] = temp;
    }

    println!("{}", sum);
}
