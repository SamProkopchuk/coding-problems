use crate::adventofcode::AdventOfCode;

use std::collections::HashMap;

pub struct Day;

type Number = u64;

const PRUNE: Number = 16777216;

fn next_number(n: Number) -> Number {
    let n: Number = (n ^ (n * 64)) % PRUNE;
    let n: Number = (n ^ (n / 32)) % PRUNE;
    let n: Number = (n ^ (n * 2048)) % PRUNE;
    n
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let initial_secret_numbers: Vec<Number> = Day::input_lines(2024, 22)?
            .iter()
            .map(|line| line.parse::<Number>().unwrap())
            .collect();
        let mut next_day_secret_numbers_sum: Number = 0;
        let mut last_numbers: [Number; 5] = [0, 0, 0, 0, 0];
        let mut last_digits: [i8; 5] = [0, 0, 0, 0, 0];
        let mut last_deltas: [i8; 4] = [0, 0, 0, 0];
        let mut total_bananas_by_sequence: HashMap<(i8, i8, i8, i8), Number> = HashMap::new();
        let mut bananas_by_sequence: HashMap<(i8, i8, i8, i8), Number> = HashMap::new();
        for initial_secret_number in initial_secret_numbers {
            last_numbers[0] = initial_secret_number;
            last_digits[0] = (initial_secret_number % 10) as i8;
            for days_gone_by in 1..=2000 {
                last_numbers.rotate_right(1);
                last_numbers[0] = next_number(last_numbers[1]);
                last_digits.rotate_right(1);
                last_digits[0] = (last_numbers[0] % 10) as i8;
                last_deltas.rotate_right(1);
                last_deltas[0] = last_digits[0] - last_digits[1];
                if days_gone_by >= 4 {
                    bananas_by_sequence
                        .entry(last_deltas.into())
                        .or_insert(last_digits[0] as Number);
                }
            }
            for (sequence, bananas) in bananas_by_sequence.drain() {
                total_bananas_by_sequence
                    .entry(sequence)
                    .and_modify(|b| *b += bananas)
                    .or_insert(bananas);
            }
            next_day_secret_numbers_sum += last_numbers[0];
        }
        println!("{}", next_day_secret_numbers_sum);
        println!("{}", total_bananas_by_sequence.values().max().unwrap());

        Ok(())
    }
}
