fn main() {
    let res = fib(10);
    println!("{}", res);
}

pub fn fib(n: u32) -> u32 {
    
    let mut darray: [u32; 2] = [0, 1];

    if n == 0 || n == 1 {
        return darray[n as usize];
    }

    for _ in 2..n+1 {
        let c = darray[0] + darray[1];
        darray[0] = darray[1];
        darray[1] = c;
    }
    
    darray[1]
}
