use std::cmp::max;
use std::collections::HashMap;
use std::io;
use std::str::FromStr;

fn main() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).unwrap();

    let mut uit = input
        .trim()
        .split_whitespace()
        .map(|x| usize::from_str(x).unwrap());
    uit.next();
    let modulo = uit.next().unwrap();

    let mut remcount = HashMap::new();
    for posrem in 0..modulo {
        remcount.insert(posrem, 0);
    }
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    for num in input
        .trim()
        .split_whitespace()
        .map(|x| usize::from_str(x).unwrap())
    {
        *remcount.get_mut(&(num % modulo)).unwrap() += 1;
    }
    let mut res = 0;
    if remcount.get(&0).unwrap() > &0 {
        res += 1;
    }
    if modulo % 2 == 0 && remcount.get(&(modulo / 2)).unwrap() > &0 {
        res += 1;
    }
    for rem in 1..((modulo + 1) / 2) {
        res += max(
            remcount.get(&rem).unwrap(),
            remcount.get(&(modulo - rem)).unwrap(),
        );
    }

    println!("{:?}", res);
}
