use crate::adventofcode::AdventOfCode;

pub struct Day;

const X: u8 = b'X';
const M: u8 = b'M';
const A: u8 = b'A';
const S: u8 = b'S';
const XMAS: [u8; 4] = [X, M, A, S];

struct Board {
    board: Vec<u8>,
    num_rows: usize,
    num_cols: usize,
}

impl Board {
    fn at(&self, r: usize, c: usize) -> u8 {
        self.board[r * self.num_cols + c]
    }
    fn is_valid(&self, r: usize, c: usize) -> bool {
        r < self.num_rows && c < self.num_cols
    }
}

// Part 1
fn count_xmas(board: &Board) -> usize {
    let mut count: usize = 0;
    for (r, c) in itertools::iproduct!(0..board.num_rows, 0..board.num_cols) {
        if board.at(r, c) != XMAS[0] {
            continue;
        }
        for (dr, dc) in itertools::iproduct!(-1..2_isize, -1..2_isize) {
            if (dr, dc) == (0, 0) {
                continue;
            }
            let mut r_next: usize = r;
            let mut c_next: usize = c;
            count += (1..4).all(|i| {
                r_next = (r_next as isize + dr) as usize;
                c_next = (c_next as isize + dc) as usize;
                board.is_valid(r_next, c_next) && board.at(r_next, c_next) == XMAS[i]
            }) as usize;
        }
    }
    count
}

fn is_mas(board: &Board, r: usize, c: usize, dr: isize, dc: isize) -> bool {
    (1..4).all(|i| {
        let r_next: usize = (r as isize - dr * (i - 2)) as usize;
        let c_next: usize = (c as isize - dc * (i - 2)) as usize;
        board.is_valid(r_next, c_next) && board.at(r_next, c_next) == XMAS[i as usize]
    }) || (1..4).all(|i| {
        let r_next: usize = (r as isize + dr * (i - 2)) as usize;
        let c_next: usize = (c as isize + dc * (i - 2)) as usize;
        board.is_valid(r_next, c_next) && board.at(r_next, c_next) == XMAS[i as usize]
    })
}

// Part 2
fn count_x_mas(board: &Board) -> usize {
    let mut count: usize = 0;
    for (r, c) in itertools::iproduct!(0..board.num_rows, 0..board.num_cols) {
        if board.at(r, c) != A {
            continue;
        }
        for (dr, dc) in itertools::iproduct!(0..2_isize, 0..2_isize) {
            if dr == 0 || dc == 0 {
                continue;
            }
            count += (is_mas(board, r, c, dr, dc) && is_mas(board, r, c, dc, -dr)) as usize;
        }
    }
    count
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let rows: Vec<String> = Day::input_lines(2024, 4)?;
        let num_rows: usize = rows.len();
        let num_cols: usize = rows[0].len();
        let board: Vec<u8> = rows.into_iter().flat_map(|row| row.into_bytes()).collect();
        assert_eq!(board.len(), num_rows * num_cols);
        let board = Board {
            board,
            num_rows,
            num_cols,
        };

        let count: usize = count_xmas(&board);
        println!("{count}");

        let count: usize = count_x_mas(&board);
        println!("{count}");

        Ok(())
    }
}
