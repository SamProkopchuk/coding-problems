use crate::adventofcode::AdventOfCode;

use std::collections::{HashSet, VecDeque};

pub struct Day;

#[derive(Debug)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

impl Direction {
    fn opposite(&self) -> Direction {
        match self {
            Direction::Up => Direction::Down,
            Direction::Down => Direction::Up,
            Direction::Left => Direction::Right,
            Direction::Right => Direction::Left,
        }
    }
}

const OBSTACLE: char = '#';
const EMPTY: char = '.';
const BOX: char = 'O';
const ROBOT: char = '@';
const L2B: char = '[';
const R2B: char = ']';

fn next_pos(i: usize, j: usize, dir: &Direction) -> (usize, usize) {
    match dir {
        Direction::Up => (i - 1, j),
        Direction::Down => (i + 1, j),
        Direction::Left => (i, j - 1),
        Direction::Right => (i, j + 1),
    }
}

fn try_move_2b_lr(board: &mut Vec<Vec<char>>, i: usize, j: usize, dir: &Direction) -> bool {
    assert!(board[i][j] == L2B || board[i][j] == R2B);
    assert!(matches!(dir, Direction::Left | Direction::Right));
    let (mut i, mut j) = next_pos(i, j, dir);
    while board[i][j] == L2B || board[i][j] == R2B {
        (i, j) = next_pos(i, j, dir);
    }
    if board[i][j] != EMPTY {
        return false;
    }
    let reverse_dir = dir.opposite();
    let (mut i_, mut j_) = next_pos(i, j, &reverse_dir);
    while board[i_][j_] == L2B || board[i_][j_] == R2B {
        board[i][j] = board[i_][j_];
        board[i_][j_] = EMPTY;
        (i, j) = (i_, j_);
        (i_, j_) = next_pos(i_, j_, &reverse_dir);
    }
    true
}

fn try_move_2b_ud(board: &mut Vec<Vec<char>>, i: usize, j: usize, dir: &Direction) -> bool {
    assert!(board[i][j] == L2B || board[i][j] == R2B);
    assert!(matches!(dir, Direction::Up | Direction::Down));
    let (i, j) = if board[i][j] == L2B {
        (i, j)
    } else {
        (i, j - 1)
    };
    let mut to_check_queue: VecDeque<(usize, usize)> = VecDeque::new();
    to_check_queue.push_back((i, j));
    let mut to_move_stack: Vec<(usize, usize)> = vec![(i, j)];
    let mut seen: HashSet<(usize, usize)> = HashSet::new();
    while let Some((i, j)) = to_check_queue.pop_front() {
        assert!(board[i][j] == L2B);
        let (i_, j_) = next_pos(i, j, dir);
        if board[i_][j_] == OBSTACLE || board[i_][j_ + 1] == OBSTACLE {
            return false;
        }
        if board[i_][j_] == L2B && !seen.contains(&(i_, j_)) {
            to_check_queue.push_back((i_, j_));
            to_move_stack.push((i_, j_));
            seen.insert((i_, j_));
        } else {
            if board[i_][j_] == R2B && !seen.contains(&(i_, j_ - 1)) {
                assert!(board[i_][j_ - 1] == L2B);
                to_check_queue.push_back((i_, j_ - 1));
                to_move_stack.push((i_, j_ - 1));
                seen.insert((i_, j_ - 1));
            }
            if board[i_][j_ + 1] == L2B && !seen.contains(&(i_, j_ + 1)) {
                assert!(board[i_][j_ + 2] == R2B);
                to_check_queue.push_back((i_, j_ + 1));
                to_move_stack.push((i_, j_ + 1));
                seen.insert((i_, j_ + 1));
            }
        }
    }
    for (i, j) in to_move_stack.iter().rev() {
        let (i, j) = (*i, *j);
        assert!(board[i][j] == L2B && board[i][j + 1] == R2B);
        let (i_, j_) = next_pos(i, j, dir);
        assert!(board[i_][j_] == EMPTY && board[i_][j_ + 1] == EMPTY);
        board[i_][j_] = L2B;
        board[i_][j_ + 1] = R2B;
        board[i][j] = EMPTY;
        board[i][j + 1] = EMPTY;
    }
    true
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let lines: Vec<String> = Day::input_lines(2024, 15)?;
        let sep_index = lines.iter().position(|line| line.is_empty()).unwrap();
        let mut board: Vec<Vec<char>> = lines[0..sep_index]
            .iter()
            .map(|line| line.chars().collect())
            .collect();
        assert!(board.iter().all(|row| row.len() == board[0].len()));
        let (i, j): (usize, usize) = itertools::iproduct!(0..board.len(), 0..board[0].len())
            .find(|&(i, j)| board[i][j] == ROBOT)
            .unwrap();
        board[i][j] = EMPTY;
        let movements: Vec<Direction> = lines[sep_index + 1..]
            .iter()
            .flat_map(|line| {
                line.chars().map(|c| match c {
                    '^' => Direction::Up,
                    'v' => Direction::Down,
                    '<' => Direction::Left,
                    '>' => Direction::Right,
                    _ => unreachable!(),
                })
            })
            .collect();
        movements.iter().fold((i, j), |(i, j), dir| {
            let (new_i, new_j) = next_pos(i, j, dir);
            if board[new_i][new_j] == EMPTY {
                return (new_i, new_j);
            } else if board[new_i][new_j] == BOX {
                let (mut i_, mut j_) = next_pos(new_i, new_j, dir);
                while board[i_][j_] == BOX {
                    (i_, j_) = next_pos(i_, j_, dir);
                }
                if board[i_][j_] == EMPTY {
                    board[i_][j_] = BOX;
                    board[new_i][new_j] = EMPTY;
                    return (new_i, new_j);
                }
            }
            (i, j)
        });
        let gps_coordinate_sum = itertools::iproduct!(0..board.len(), 0..board[0].len())
            .filter(|&(i, j)| board[i][j] == BOX)
            .map(|(i, j)| 100 * i + j)
            .sum::<usize>();
        println!("{}", gps_coordinate_sum);
        let mut board: Vec<Vec<char>> = lines[0..sep_index]
            .iter()
            .map(|line| {
                line.chars()
                    .map(|c| match c {
                        ROBOT => "@.",
                        EMPTY => "..",
                        OBSTACLE => "##",
                        BOX => "[]",
                        _ => unreachable!(),
                    })
                    .flat_map(|s| s.chars())
                    .collect()
            })
            .collect();

        let (i, j): (usize, usize) = itertools::iproduct!(0..board.len(), 0..board[0].len())
            .find(|&(i, j)| board[i][j] == ROBOT)
            .unwrap();
        board[i][j] = EMPTY;
        movements.iter().fold((i, j), |(i, j), dir| {
            let (i_, j_) = next_pos(i, j, dir);
            match dir {
                Direction::Up | Direction::Down => {
                    if board[i_][j_] == L2B || board[i_][j_] == R2B {
                        if try_move_2b_ud(&mut board, i_, j_, dir) {
                            return (i_, j_);
                        } else {
                            return (i, j);
                        }
                    } else if board[i_][j_] == EMPTY {
                        return (i_, j_);
                    } else {
                        return (i, j);
                    }
                }
                Direction::Left | Direction::Right => {
                    if board[i_][j_] == L2B || board[i_][j_] == R2B {
                        if try_move_2b_lr(&mut board, i_, j_, dir) {
                            return (i_, j_);
                        } else {
                            return (i, j);
                        }
                    } else if board[i_][j_] == EMPTY {
                        return (i_, j_);
                    } else {
                        return (i, j);
                    }
                }
            }
        });
        let gps_coordinate_sum = itertools::iproduct!(0..board.len(), 0..board[0].len())
            .filter(|&(i, j)| board[i][j] == L2B)
            .map(|(i, j)| (100 * i + j) as usize)
            .sum::<usize>();
        println!("{}", gps_coordinate_sum);

        Ok(())
    }
}
