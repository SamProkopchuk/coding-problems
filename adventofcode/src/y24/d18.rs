use crate::adventofcode::AdventOfCode;

use std::collections::VecDeque;

pub struct Day;

type Position = (usize, usize);

const NUM_Y: usize = 71;
const NUM_X: usize = 71;
const START: Position = (0, 0);
const END: Position = (NUM_X - 1, NUM_Y - 1);

const EMPTY: char = '.';
const WALL: char = '#';

fn get_num_steps_if_path_exists(memory: &Vec<Vec<char>>) -> Option<usize> {
    let mut seen: Vec<Vec<bool>> = (0..NUM_Y).map(|_| vec![false; NUM_X]).collect();
    seen[START.0][START.1] = true;
    let mut queue: VecDeque<(Position, usize)> = VecDeque::from(vec![(START, 0)]);
    while let Some(((x, y), steps)) = queue.pop_front() {
        assert!(seen[y][x]);
        if (x, y) == END {
            return Some(steps);
        }
        for (dy, dx) in itertools::iproduct!(-1..=1, -1..=1) {
            if !((dy == 0) ^ (dx == 0)) {
                continue;
            }
            let x_: usize = (x as isize + dx) as usize;
            let y_: usize = (y as isize + dy) as usize;
            if x_ >= NUM_X || y_ >= NUM_Y || memory[y_][x_] == WALL || seen[y_][x_] {
                continue;
            }
            seen[y_][x_] = true;
            queue.push_back(((x_, y_), steps + 1));
        }
    }
    None
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let positions: Vec<Position> = Day::input_lines(2024, 18)?
            .iter()
            .map(|line| {
                let mut parts = line.split(",");
                (
                    parts.next().unwrap().parse::<usize>().unwrap(),
                    parts.next().unwrap().parse::<usize>().unwrap(),
                )
            })
            .collect();
        let base_memory: Vec<Vec<char>> = (0..NUM_Y).map(|_| vec![EMPTY; NUM_X]).collect();
        let memory: Vec<Vec<char>> = {
            let mut temp: Vec<Vec<char>> = base_memory.clone();
            for (x, y) in positions.iter().take(1024) {
                temp[*y][*x] = WALL;
            }
            temp
        };
        let num_steps: usize = get_num_steps_if_path_exists(&memory).unwrap();
        println!("{}", num_steps);
        let num_positions: Vec<usize> = (1..=positions.len()).collect();
        let first_blocking_index: usize = num_positions
            .binary_search_by(|&n| {
                let mut temp: Vec<Vec<char>> = base_memory.clone();
                for (x, y) in positions.iter().take(n) {
                    temp[*y][*x] = WALL;
                }
                match get_num_steps_if_path_exists(&temp).is_none() {
                    true => return std::cmp::Ordering::Greater,
                    false => return std::cmp::Ordering::Less,
                }
            })
            .unwrap_err();
        let first_blocking_position: Position = positions[first_blocking_index];
        println!(
            "{},{}",
            first_blocking_position.0, first_blocking_position.1
        );

        Ok(())
    }
}
