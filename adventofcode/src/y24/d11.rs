use crate::adventofcode::AdventOfCode;

use std::collections::HashMap;

pub struct Day;

type StoneDay = (u128, u32);

fn num_digits(n: u128) -> u32 {
    itertools::iterate(n, |x| x / 10)
        .take_while(|&x| x > 0)
        .count() as u32
}

fn split_digits(n: u128) -> (u128, u128) {
    let digits: String = n.to_string();
    assert!(digits.len() % 2 == 0);
    return (
        digits[..digits.len() / 2].parse::<u128>().unwrap(),
        digits[digits.len() / 2..].parse::<u128>().unwrap(),
    );
}

fn update_cache(cache: &mut HashMap<StoneDay, usize>, stone: u128, day: u32) -> usize {
    if let Some(&val) = cache.get(&(stone, day)) {
        return val;
    } else if day == 0 {
        cache.insert((stone, day), 1);
        return 1;
    } else if stone == 0 {
        let val = update_cache(cache, 1, day - 1);
        cache.insert((stone, day), val);
        return val;
    } else if num_digits(stone) % 2 == 0 {
        let (a, b) = split_digits(stone);
        let val = update_cache(cache, a, day - 1) + update_cache(cache, b, day - 1);
        cache.insert((stone, day), val);
        return val;
    } else {
        let new_stone = stone * 2024;
        let val = update_cache(cache, new_stone, day - 1);
        cache.insert((stone, day), val);
        return val;
    }
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let stones: Vec<u128> = Day::input_raw(2024, 11)?
            .trim()
            .split_whitespace()
            .map(|x| x.parse::<u128>().unwrap())
            .collect();
        let mut cache: HashMap<StoneDay, usize> = HashMap::new();
        let num_stones: usize = stones
            .iter()
            .map(|&stone| update_cache(&mut cache, stone, 25))
            .sum();
        println!("{:?}", num_stones);
        let num_stones: usize = stones
            .iter()
            .map(|&stone| update_cache(&mut cache, stone, 75))
            .sum();
        println!("{:?}", num_stones);

        Ok(())
    }
}
