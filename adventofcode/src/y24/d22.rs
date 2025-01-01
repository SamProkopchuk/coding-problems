use crate::adventofcode::AdventOfCode;

use std::collections::HashMap;

pub struct Day;

type Number = u64;

const PRUNE: Number = 16777216;

fn next_number(n: Number) -> Number {
    // Step 1:
    let n: Number = (n ^ (n * 64)) % PRUNE;
    // Step 2:
    let n: Number = (n ^ (n / 32)) % PRUNE;
    // Step 3:
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
        let mut last_numbers: (Number, Number, Number, Number, Number) = (0, 0, 0, 0, 0);
        let mut last_digits: (i8, i8, i8, i8, i8) = (0, 0, 0, 0, 0);
        let mut last_deltas: (i8, i8, i8, i8) = (0, 0, 0, 0);
        let mut total_bananas_by_sequence: HashMap<(i8, i8, i8, i8), Number> = HashMap::new();
        let mut bananas_by_sequence: HashMap<(i8, i8, i8, i8), Number> = HashMap::new();
        for initial_secret_number in initial_secret_numbers {
            last_numbers.4 = initial_secret_number;
            last_digits.4 = (last_numbers.4 % 10) as i8;
            for days_gone_by in 1..=2000 {
                last_numbers.0 = last_numbers.1;
                last_numbers.1 = last_numbers.2;
                last_numbers.2 = last_numbers.3;
                last_numbers.3 = last_numbers.4;
                last_numbers.4 = next_number(last_numbers.4);
                last_digits.0 = last_digits.1;
                last_digits.1 = last_digits.2;
                last_digits.2 = last_digits.3;
                last_digits.3 = last_digits.4;
                last_digits.4 = (last_numbers.4 % 10) as i8;
                last_deltas.0 = last_deltas.1;
                last_deltas.1 = last_deltas.2;
                last_deltas.2 = last_deltas.3;
                last_deltas.3 = last_digits.4 - last_digits.3;
                if days_gone_by >= 4 {
                    let bananas: Number = last_digits.4 as Number;
                    if !bananas_by_sequence.contains_key(&last_deltas) {
                        bananas_by_sequence.insert(last_deltas, bananas);
                    }
                }
            }
            for (sequence, bananas) in bananas_by_sequence.drain() {
                total_bananas_by_sequence
                    .entry(sequence)
                    .and_modify(|b| *b += bananas)
                    .or_insert(bananas);
            }
            next_day_secret_numbers_sum += last_numbers.4;
        }
        println!("{}", next_day_secret_numbers_sum);
        println!("{}", total_bananas_by_sequence.values().max().unwrap());

        Ok(())
    }
}
