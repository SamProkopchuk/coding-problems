use crate::adventofcode::AdventOfCode;
use fancy_regex::Regex;

pub struct Day;

fn mul(s: &str) -> i32 {
    let re = Regex::new(r"\d+").unwrap();
    let mut it = re.find_iter(s);
    let (x, y) = (
        it.next().unwrap().unwrap().as_str().parse::<i32>().unwrap(),
        it.next().unwrap().unwrap().as_str().parse::<i32>().unwrap(),
    );
    x * y
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let memory: String = Day::input_raw(2024, 3).unwrap();
        let re = Regex::new(r"mul\(\d+,\d+\)")?;

        let total = re
            .find_iter(&memory)
            .fold(0, |acc, m| acc + mul(m.unwrap().as_str()));
        println!("{total}");

        // Stupidly overcomplicated, but nice challenge.
        // Reads two ordered iterators of (index, bool) pairs & reverses.
        let mut filter_indices: Vec<(usize, bool)> = itertools::merge_join_by(
            Regex::new(r"do\(\)")?
                .find_iter(&memory)
                .map(|m| (m.unwrap().start(), false)),
            Regex::new(r"don't\(\)")?
                .find_iter(&memory)
                .map(|m| (m.unwrap().start(), true)),
            |a, b| a.0.cmp(&b.0),
        )
        .map(|eob| eob.into_left())
        .collect::<Vec<_>>()
        .into_iter()
        .rev()
        .collect();
        let mut filter: bool = false;
        let mut filtered_total: i32 = 0;
        for m in re.find_iter(&memory).map(|m| m.unwrap()) {
            while !filter_indices.is_empty() && filter_indices.last().unwrap().0 < m.start() {
                filter = filter_indices.pop().unwrap().1;
            }
            if !filter {
                filtered_total += mul(m.as_str());
            }
        }
        println!("{filtered_total}");

        Ok(())
    }
}
