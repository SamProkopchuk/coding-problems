use crate::adventofcode::AdventOfCode;
use bitvec::vec::BitVec;

pub struct Day;

const OBSTACLE: u8 = b'#';
const EMPTY: u8 = b'.';
const UP: u8 = b'^';
const DOWN: u8 = b'v';
const LEFT: u8 = b'<';
const RIGHT: u8 = b'>';

#[derive(Debug, Clone, Copy)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

impl Direction {
    fn next(&self) -> Direction {
        match self {
            Direction::Up => Direction::Right,
            Direction::Down => Direction::Left,
            Direction::Left => Direction::Up,
            Direction::Right => Direction::Down,
        }
    }
    fn as_usize(&self) -> usize {
        match self {
            Direction::Up => 0,
            Direction::Down => 1,
            Direction::Left => 2,
            Direction::Right => 3,
        }
    }
}

#[derive(Debug, Clone, Copy)]
struct Pos {
    row: usize,
    col: usize,
    dir: Direction,
}

impl Pos {
        fn next(&self) -> Pos {
        let (dr, dc): (isize, isize) = match self.dir {
            Direction::Up => (-1, 0),
            Direction::Down => (1, 0),
            Direction::Left => (0, -1),
            Direction::Right => (0, 1),
        };
        Pos {
            row: (self.row as isize + dr) as usize,
            col: (self.col as isize + dc) as usize,
            dir: self.dir,
        }
    }
}

struct Board {
    board: Vec<u8>,
    num_rows: usize,
    num_cols: usize,
}

impl Board {
    fn raw_index(&self, pos: &Pos) -> usize {
        pos.row * self.num_cols + pos.col
    }
    fn at(&self, pos: &Pos) -> u8 {
        self.board[self.raw_index(&pos)]
    }
    fn is_valid(&self, pos: &Pos) -> bool {
        pos.row < self.num_rows && pos.col < self.num_cols
    }
}

fn ways_loop(board: &Board, start: &Pos) -> usize {
    let mut ways: usize = 0;

    let num_elem: usize = board.num_rows * board.num_cols;
    let mut been: BitVec = BitVec::repeat(false, num_elem * 4);
    for (obs_row, obs_col) in itertools::iproduct!(0..board.num_rows, 0..board.num_cols) {
        if board.board[obs_row * board.num_cols + obs_col] == OBSTACLE
            || (obs_row, obs_col) == (start.row, start.col)
        {
            continue;
        }
        let mut pos: Pos = *start;
        while board.is_valid(&pos) {
            let raw_index: usize = board.raw_index(&pos) * 4 + pos.dir.as_usize();
            if been[raw_index] {
                ways += 1;
                break;
            }
            been.set(raw_index, true);
            let next_pos = pos.next();
            if !board.is_valid(&next_pos) {
                break;
            } else if board.at(&next_pos) == OBSTACLE
                || (next_pos.row, next_pos.col) == (obs_row, obs_col)
            {
                pos.dir = pos.dir.next();
            } else {
                pos = next_pos;
            }
        }
        been.fill(false);
    }
    ways
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let rows: Vec<String> = Day::input_lines(2024, 6)?;
        let num_rows: usize = rows.len();
        let num_cols: usize = rows[0].len();
        let mut board: Vec<u8> = rows.into_iter().flat_map(|row| row.into_bytes()).collect();
        assert_eq!(board.len(), num_rows * num_cols);
        let (row, col, dir): (usize, usize, Direction) =
            itertools::iproduct!(0..num_rows, 0..num_cols)
                .find_map(|(r, c)| match board[r * num_cols + c] {
                    UP => Some((r, c, Direction::Up)),
                    DOWN => Some((r, c, Direction::Down)),
                    LEFT => Some((r, c, Direction::Left)),
                    RIGHT => Some((r, c, Direction::Right)),
                    _ => None,
                })
                .unwrap();
        board[row * num_cols + col] = EMPTY;
        let start: Pos = Pos {
            row: row,
            col: col,
            dir: dir,
        };
        let mut pos = start;
        let board = Board {
            board: board,
            num_rows: num_rows,
            num_cols: num_cols,
        };
        let mut been: BitVec = BitVec::repeat(false, num_rows * num_cols);
        while board.is_valid(&pos) {
            been.set(board.raw_index(&pos), true);
            let next_pos = pos.next();
            if !board.is_valid(&next_pos) {
                break;
            } else if board.at(&next_pos) == OBSTACLE {
                pos.dir = pos.dir.next();
            } else {
                pos = next_pos;
            }
        }
        let num_been: usize = been.count_ones();
        println!("{num_been}");

        let ways: usize = ways_loop(&board, &start);
        println!("{ways}");

        Ok(())
    }
}
