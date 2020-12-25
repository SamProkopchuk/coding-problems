use std::io;
use std::str::FromStr;

fn main() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).unwrap();
    let tests = <i32>::from_str(&input.trim()).unwrap();

    for _ in 0..tests {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        input = input.trim().to_string();
        let mut s: Vec<char> = input.chars().collect();
        let mut isbreak = false;
        for (idx, c) in input
            .chars()
            .collect::<Vec<char>>()
            .iter()
            .enumerate()
            .rev()
        {
            if idx != s.len() - 1 && c < &s[idx + 1] {
                let swapidx = &s[idx + 1..]
                    .iter()
                    .enumerate()
                    .filter(|(_, &value)| value > s[idx])
                    .min_by_key(|(_, &value)| value)
                    .map(|(i, _)| i)
                    .unwrap()
                    + idx
                    + 1;
                s.swap(idx, swapidx);
                s[idx + 1..].sort();
                println!("{}", s.iter().collect::<String>());
                isbreak = true;
                break;
            }
        }
        if !isbreak {
            println!("no answer");
        }
    }
}
