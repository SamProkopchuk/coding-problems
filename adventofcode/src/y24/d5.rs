use crate::adventofcode::AdventOfCode;
use std::collections::{HashMap, HashSet};

pub struct Day;

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let input_lines: Vec<String> = Day::input_lines(2024, 5)?;
        let mut i: usize = 0;
        let mut comes_after: HashMap<usize, HashSet<usize>> = HashMap::new();
        while i < input_lines.len() {
            let line: &str = &input_lines[i];
            if line.is_empty() || line.trim().is_empty() {
                i += 1;
                break;
            }
            let (x, y) = {
                let mut it = line.split("|");
                (
                    it.next().unwrap().parse::<usize>().unwrap(),
                    it.next().unwrap().parse::<usize>().unwrap(),
                )
            };
            comes_after.entry(x).or_insert(HashSet::new()).insert(y);
            i += 1;
        }
        let mut count_1: usize = 0;
        let mut count_2: usize = 0;
        let mut seen: Vec<usize> = Vec::new();
        while i < input_lines.len() {
            let line: &str = &input_lines[i];
            seen.clear();
            let mut nums: Vec<usize> = line
                .split(",")
                .map(|x| x.parse::<usize>().unwrap())
                .collect();
            let mut is_valid: bool = true;
            for num in &nums {
                if seen
                    .iter()
                    .any(|&x| comes_after.get(&num).unwrap().contains(&x))
                {
                    is_valid = false;
                    break;
                }
                seen.push(*num);
            }
            if is_valid {
                count_1 += nums[nums.len() / 2];
            } else {
                nums.sort_by(|a, b| {
                    match comes_after.get(a).unwrap().contains(b) {
                        true => std::cmp::Ordering::Less,
                        false => std::cmp::Ordering::Greater,
                    }
                });
                count_2 += nums[nums.len() / 2];
            }
            i += 1;
        }
        println!("{count_1}");

        println!("{count_2}");

        Ok(())
    }
}
