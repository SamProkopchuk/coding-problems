use std::io;
use std::str::FromStr;

fn main() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let mut scores: Vec<i32> = input
        .trim()
        .split_whitespace()
        .map(|x| i32::from_str(x).unwrap())
        .collect();
    scores.dedup();

    io::stdin().read_line(&mut input).unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    for ascore in input
        .trim()
        .split_whitespace()
        .map(|x| i32::from_str(x).unwrap())
        .collect::<Vec<i32>>()
    {
        while !scores.is_empty() && scores.last().unwrap() <= &ascore {
            scores.pop();
        }
        println!("{}", scores.len() + 1);
    }
}
