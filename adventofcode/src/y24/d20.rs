use crate::adventofcode::AdventOfCode;

use std::collections::{HashSet, VecDeque};

pub struct Day;

// This solution is not optimized, but fast enough for AOC, especially with --release

type Position = (usize, usize);

const START: char = 'S';
const END: char = 'E';
const WALL: char = '#';
// const EMPTY: char = '.';

fn distances_no_cheats(racetrack: &Vec<Vec<char>>, start: Position) -> Vec<Vec<usize>> {
    let mut distances: Vec<Vec<usize>> = (0..racetrack.len())
        .map(|_| vec![usize::MAX; racetrack[0].len()])
        .collect();
    distances[start.0][start.1] = 0;
    let mut queue: VecDeque<(Position, usize)> = VecDeque::from(vec![(start, 0)]);
    while let Some((position, distance)) = queue.pop_front() {
        for (dr, dc) in itertools::iproduct!(-1..=1, -1..=1) {
            if (dr == 0) == (dc == 0) {
                continue;
            }
            let position_ = (
                (position.0 as isize + dr) as usize,
                (position.1 as isize + dc) as usize,
            );
            if position_.0 >= racetrack.len()
                || position_.1 >= racetrack[0].len()
                || racetrack[position_.0][position_.1] == WALL
                || distances[position_.0][position_.1] != usize::MAX
            {
                continue;
            }
            distances[position_.0][position_.1] = distance + 1;
            queue.push_back((position_, distance + 1));
        }
    }
    distances
}

fn num_faster_ways(
    racetrack: &Vec<Vec<char>>,
    distances_to_end: &Vec<Vec<usize>>,
    start: Position,
    num_consecutive_cheats: usize,
) -> usize {
    let (num_rows, num_cols): (usize, usize) = (racetrack.len(), racetrack[0].len());
    let num_steps_start_to_end: usize = distances_to_end[start.0][start.1];
    let mut seen_positions: Vec<bool> = vec![false; num_rows * num_cols];
    let mut seen_positions_: Vec<bool> = vec![false; num_rows * num_cols];
    seen_positions[start.0 * num_cols + start.1] = true;
    let mut states: VecDeque<(Position, usize)> = VecDeque::from(vec![(start, 0)]);
    let mut states_: VecDeque<(Position, usize)> = VecDeque::new();
    let mut num_ways: usize = 0;

    while let Some((position, num_steps)) = states.pop_front() {
        assert!(seen_positions[position.0 * num_cols + position.1]);
        // Subroutine of trying cheats
        seen_positions_.fill(false);
        seen_positions_[position.0 * num_cols + position.1] = true;
        states_.clear();
        states_.push_back((position, 0));
        while let Some((position_, num_steps_)) = states_.pop_front() {
            for (dr, dc) in itertools::iproduct!(-1..=1, -1..=1) {
                if (dr == 0) == (dc == 0) {
                    continue;
                }
                let position__ = (
                    (position_.0 as isize + dr) as usize,
                    (position_.1 as isize + dc) as usize,
                );
                if position__.0 >= num_rows
                    || position__.1 >= num_cols
                    || seen_positions_[position__.0 * num_cols + position__.1]
                {
                    continue;
                }
                if num_steps_ + 1 < num_consecutive_cheats {
                    states_.push_back((position__, num_steps_ + 1));
                }
                if racetrack[position__.0][position__.1] == WALL {
                    seen_positions_[position__.0 * num_cols + position__.1] = true;
                    continue;
                }
                if num_steps_ == 0 && !seen_positions[position__.0 * num_cols + position__.1] {
                    seen_positions[position__.0 * num_cols + position__.1] = true;
                    states.push_back((position__, num_steps + 1));
                }
                seen_positions_[position__.0 * num_cols + position__.1] = true;
                if num_steps + num_steps_ + 1 + distances_to_end[position__.0][position__.1] + 100
                    <= num_steps_start_to_end
                {
                    num_ways += 1;
                }
            }
        }
    }
    num_ways
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let racetrack: Vec<Vec<char>> = Day::input_lines(2024, 20)?
            .iter()
            .map(|line| line.chars().collect())
            .collect();
        assert!(racetrack.iter().all(|row| row.len() == racetrack[0].len()));
        let start: Position = itertools::iproduct!(0..racetrack.len(), 0..racetrack[0].len())
            .find(|&(row, col)| racetrack[row][col] == START)
            .unwrap();
        let end: Position = itertools::iproduct!(0..racetrack.len(), 0..racetrack[0].len())
            .find(|&(row, col)| racetrack[row][col] == END)
            .unwrap();
        let distances: Vec<Vec<usize>> = distances_no_cheats(&racetrack, end);
        let num_ways: usize = num_faster_ways(&racetrack, &distances, start, 2);
        println!("{}", num_ways);
        let num_ways: usize = num_faster_ways(&racetrack, &distances, start, 20);
        println!("{}", num_ways);

        Ok(())
    }
}
