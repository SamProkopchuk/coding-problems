use std::io;
use std::str::FromStr;

fn main() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).unwrap();
    let mut it = input
        .trim()
        .split_whitespace()
        .map(|x| usize::from_str(x).unwrap());
    let h = it.next().unwrap();
    let w = it.next().unwrap();

    let mut board = vec![vec![0; w]; h];
    let mut sa = (2 * h * w) as i32;
    for row in 0..h {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let mut it = input
            .trim()
            .split_whitespace()
            .map(|x| i32::from_str(x).unwrap());
        for col in 0..w {
            let v = it.next().unwrap();
            board[row][col] = v;
            sa += if row == 0 { v } else { (v - board[row - 1][col]).abs() };
            sa += if col == 0 { v } else { (v - board[row][col - 1]).abs() };
            if row == (h - 1) { sa += v };
            if col == (w - 1) { sa += v };
        }
    }
    println!("{}", sa);
}
