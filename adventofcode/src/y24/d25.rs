use crate::adventofcode::AdventOfCode;

pub struct Day;

#[derive(Debug)]
enum LockOrKey {
    Lock([u8; 5]),
    Key([u8; 5]),
}

const NUM_ROWS: usize = 7;
const NUM_COLS: usize = 5;
const EMPTY: char = '.';
const FILLED: char = '#';

fn parse_lock_or_key(schematic: &[Vec<char>]) -> LockOrKey {
    let is_lock: bool = schematic[0].iter().all(|c| *c == FILLED);
    match is_lock {
        true => {
            let v: Vec<u8> = (0..NUM_COLS)
                .map(|i| {
                    (0..NUM_ROWS)
                        .rev()
                        .take_while(|j| schematic[*j][i] == EMPTY)
                        .count() as u8
                })
                .collect();
            LockOrKey::Lock(v.try_into().unwrap())
        }
        false => {
            let v: Vec<u8> = (0..NUM_COLS)
                .map(|i| {
                    (0..NUM_ROWS)
                        .rev()
                        .take_while(|j| schematic[*j][i] == FILLED)
                        .count() as u8
                })
                .collect();
            LockOrKey::Key(v.try_into().unwrap())
        }
    }
}

fn fits(lock: &[u8; 5], key: &[u8; 5]) -> bool {
    (0..5).all(|i| lock[i] >= key[i])
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let schematics: Vec<Vec<Vec<char>>> = Day::input_lines(2024, 25)?
            .split(|line| line.is_empty())
            .map(|group| group.iter().map(|line| line.chars().collect()).collect())
            .collect();
        let lock_or_keys: Vec<LockOrKey> = schematics
            .iter()
            .map(|schematic| parse_lock_or_key(schematic))
            .collect();
        let locks: Vec<[u8; 5]> = lock_or_keys
            .iter()
            .filter_map(|lock_or_key| match lock_or_key {
                LockOrKey::Lock(lock) => Some(*lock),
                _ => None,
            })
            .collect();
        let keys: Vec<[u8; 5]> = lock_or_keys
            .iter()
            .filter_map(|lock_or_key| match lock_or_key {
                LockOrKey::Key(key) => Some(*key),
                _ => None,
            })
            .collect();
        // Just brute force...
        let ans: usize = locks
            .iter()
            .map(|lock| keys.iter().filter(|key| fits(lock, key)).count())
            .sum();
        println!("{}", ans);

        Ok(())
    }
}
