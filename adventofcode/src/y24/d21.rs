use crate::adventofcode::AdventOfCode;

use std::collections::HashMap;

pub struct Day;

type Position = (usize, usize);
type Direction = (isize, isize);
type NumInstructions = u128;

const EMPTY: char = '.';
const EMPTY_NUMERIC_KEYPAD_POSITION: Position = (3, 0);
const EMPTY_DIRECTIONAL_KEYPAD_POSITION: Position = (0, 0);

fn get_numeric_keypad_char_position(c: char) -> Position {
    match c {
        '7' => (0, 0),
        '8' => (0, 1),
        '9' => (0, 2),
        '4' => (1, 0),
        '5' => (1, 1),
        '6' => (1, 2),
        '1' => (2, 0),
        '2' => (2, 1),
        '3' => (2, 2),
        '0' => (3, 1),
        'A' => (3, 2),
        _ => panic!("Invalid character: {}", c),
    }
}

fn get_directional_keypad_char_position(c: char) -> Position {
    match c {
        '^' => (0, 1),
        'A' => (0, 2),
        '<' => (1, 0),
        'v' => (1, 1),
        '>' => (1, 2),
        _ => panic!("Invalid character: {}", c),
    }
}

fn get_directional_commands(d: Direction) -> Vec<char> {
    assert!((d.0 == 0) || (d.1 == 0));
    let (c, n) = match d {
        (_, dc) if dc < 0 => ('<', -dc as usize),
        (_, dc) if dc > 0 => ('>', dc as usize),
        (dr, _) if dr < 0 => ('^', -dr as usize),
        (dr, _) if dr > 0 => ('v', dr as usize),
        (0, 0) => (EMPTY, 0),
        _ => panic!("Invalid direction: {:?}", d),
    };
    vec![c; n]
}

fn get_min_num_directional_instructions(
    target_instructions: Vec<char>,
    depth: usize,
    cache: &mut HashMap<(Position, char, usize), NumInstructions>,
) -> NumInstructions {
    if depth == 0 {
        return target_instructions.len() as NumInstructions;
    }
    let mut current_position = get_directional_keypad_char_position('A');
    let mut num_instructions: NumInstructions = 0;
    for c in target_instructions {
        let next_position = get_directional_keypad_char_position(c);
        if let Some(&cached_num_instructions) = cache.get(&(current_position, c, depth)) {
            num_instructions += cached_num_instructions;
            current_position = next_position;
            continue;
        }
        let (dr, dc): (isize, isize) = (
            next_position.0 as isize - current_position.0 as isize,
            next_position.1 as isize - current_position.1 as isize,
        );
        let mut commands: Vec<Vec<char>> = Vec::new();
        for delta_pair_pair in vec![((dr, 0), (0, dc)), ((0, dc), (dr, 0))] {
            let d1 = delta_pair_pair.0;
            let d2 = delta_pair_pair.1;
            let next_position: Position = (
                (current_position.0 as isize + d1.0) as usize,
                (current_position.1 as isize + d1.1) as usize,
            );
            if next_position == EMPTY_DIRECTIONAL_KEYPAD_POSITION {
                continue;
            }
            commands.push(
                get_directional_commands(d1)
                    .into_iter()
                    .chain(get_directional_commands(d2))
                    .into_iter()
                    .chain(std::iter::once('A'))
                    .collect(),
            );
        }
        let num_instructions_delta: NumInstructions = commands
            .into_iter()
            .map(|c| get_min_num_directional_instructions(c, depth - 1, cache))
            .min()
            .unwrap();
        cache.insert((current_position, c, depth), num_instructions_delta);
        num_instructions += num_instructions_delta;
        current_position = next_position;
    }
    num_instructions
}

fn get_min_num_instructions(target_instructions: &Vec<char>, depth: usize) -> NumInstructions {
    let mut current_position: Position = get_numeric_keypad_char_position('A');
    let mut num_instructions: NumInstructions = 0;
    let mut cache: HashMap<(Position, char, usize), NumInstructions> = HashMap::new();
    for c in target_instructions {
        let next_position = get_numeric_keypad_char_position(*c);
        let (dr, dc): (isize, isize) = (
            next_position.0 as isize - current_position.0 as isize,
            next_position.1 as isize - current_position.1 as isize,
        );
        let mut commands: Vec<Vec<char>> = Vec::new();
        for delta_pair_pair in vec![((dr, 0), (0, dc)), ((0, dc), (dr, 0))] {
            let d1 = delta_pair_pair.0;
            let d2 = delta_pair_pair.1;
            let next_position: Position = (
                (current_position.0 as isize + d1.0) as usize,
                (current_position.1 as isize + d1.1) as usize,
            );
            if next_position == EMPTY_NUMERIC_KEYPAD_POSITION {
                continue;
            }
            commands.push(
                get_directional_commands(d1)
                    .into_iter()
                    .chain(get_directional_commands(d2))
                    .into_iter()
                    .chain(std::iter::once('A'))
                    .collect(),
            );
        }
        num_instructions += commands
            .into_iter()
            .map(|c| get_min_num_directional_instructions(c, depth, &mut cache))
            .min()
            .unwrap();
        current_position = next_position;
    }
    num_instructions
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let cases: Vec<Vec<char>> = Day::input_lines(2024, 21)?
            .iter()
            .map(|line| line.chars().collect())
            .collect();
        let total_complexity = cases
            .iter()
            .map(|c| {
                let s = c
                    .iter()
                    .collect::<String>()
                    .trim_start_matches('0')
                    .trim_end_matches('A')
                    .to_string();
                s.parse::<NumInstructions>().unwrap() * get_min_num_instructions(c, 2)
            })
            .sum::<NumInstructions>();
        println!("{}", total_complexity);
        let total_complexity = cases
            .iter()
            .map(|c| {
                let s = c
                    .iter()
                    .collect::<String>()
                    .trim_start_matches('0')
                    .trim_end_matches('A')
                    .to_string();
                s.parse::<NumInstructions>().unwrap() * get_min_num_instructions(c, 25)
            })
            .sum::<NumInstructions>();
        println!("{}", total_complexity);
        Ok(())
    }
}
