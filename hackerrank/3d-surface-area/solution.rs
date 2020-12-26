use std::io;
use std::str::FromStr;

fn main() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).unwrap();
    let mut it = input
        .trim()
        .split_whitespace()
        .map(|x| usize::from_str(x).unwrap());
    let (h, w) = (it.next().unwrap(), it.next().unwrap());

    let mut board : Vec<Vec<i32>> = vec![];
    let mut sa = (2 * h * w) as i32;
    for row in 0..h {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        board.push(input
            .trim()
            .split_whitespace()
            .map(|x| i32::from_str(x).unwrap())
            .collect::<Vec<i32>>());
        for col in 0..w {
            sa += if row == 0 { board[row][col] } else { (board[row][col] - board[row - 1][col]).abs() };
            sa += if col == 0 { board[row][col] } else { (board[row][col] - board[row][col - 1]).abs() };
            if row == (h - 1) { sa += board[row][col] };
            if col == (w - 1) { sa += board[row][col] };
        }
    }
    println!("{}", sa);
}
