use crate::adventofcode::AdventOfCode;

use std::collections::{HashSet, VecDeque};

pub struct Day;

fn get_score(board: &Vec<Vec<i32>>, i: usize, j: usize, skip_seen: bool) -> usize {
    let mut score: usize = 0;
    let mut seen: HashSet<(usize, usize)> = HashSet::new();
    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    seen.insert((i, j));
    queue.push_back((i, j));
    while !queue.is_empty() {
        let (i, j) = queue.pop_front().unwrap();
        if board[i][j] == 9 {
            score += 1;
        }
        const DIRECTIONS: [(isize, isize); 4] = [(0, -1), (0, 1), (-1, 0), (1, 0)];
        for (di, dj) in DIRECTIONS.iter() {
            let i_: usize = (i as isize + di) as usize;
            let j_: usize = (j as isize + dj) as usize;
            if i_ < board.len()
                && j_ < board[i_].len()
                && board[i_][j_] == board[i][j] + 1
                && (skip_seen || !seen.contains(&(i_, j_)))
            {
                seen.insert((i_, j_));
                queue.push_back((i_, j_));
            }
        }
    }
    score
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let board: Vec<Vec<i32>> = Day::input_lines(2024, 10)?
            .iter()
            .map(|line| {
                line.chars()
                    .map(|c| c.to_digit(10).unwrap() as i32)
                    .collect()
            })
            .collect();
        let score = itertools::iproduct!(0..board.len(), 0..board[0].len())
            .map(|(i, j)| {
                if board[i][j] == 0 {
                    get_score(&board, i, j, false)
                } else {
                    0
                }
            })
            .sum::<usize>();
        println!("{:?}", score);
        let score = itertools::iproduct!(0..board.len(), 0..board[0].len())
            .map(|(i, j)| {
                if board[i][j] == 0 {
                    get_score(&board, i, j, true)
                } else {
                    0
                }
            })
            .sum::<usize>();
        println!("{:?}", score);

        Ok(())
    }
}
