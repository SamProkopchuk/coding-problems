use crate::adventofcode::AdventOfCode;

use fancy_regex::Regex;
use itertools::Itertools;

pub struct Day;

type XY = (i64, i64);
type ABPrize = (XY, XY, XY);

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let re = Regex::new(r"\d+").unwrap();
        let a_b_prizes: Vec<ABPrize> = Day::input_lines(2024, 13)?
            .iter()
            .filter_map(|line| {
                if line.is_empty() {
                    None
                } else {
                    let mut matches = re.find_iter(&line);
                    Some((
                        matches
                            .next()
                            .unwrap()
                            .unwrap()
                            .as_str()
                            .parse::<i64>()
                            .unwrap(),
                        matches
                            .next()
                            .unwrap()
                            .unwrap()
                            .as_str()
                            .parse::<i64>()
                            .unwrap(),
                    ))
                }
            })
            .tuples::<(_, _, _)>()
            .collect();
        let fewest_tokens: i64 = a_b_prizes
            .iter()
            .filter_map(|(a, b, prize)| {
                let num_a = (prize.1 * b.0 - prize.0 * b.1) / (a.1 * b.0 - a.0 * b.1);
                let num_b = (prize.1 * a.0 - prize.0 * a.1) / (b.1 * a.0 - b.0 * a.1);
                if num_a * a.0 + num_b * b.0 == prize.0 && num_a * a.1 + num_b * b.1 == prize.1 {
                    Some(3 * num_a + num_b)
                } else {
                    None
                }
            })
            .sum::<i64>();
        println!("{}", fewest_tokens);
        let fewest_tokens: i64 = a_b_prizes
            .iter()
            .filter_map(|(a, b, prize)| {
                let prize = (prize.0 + 10000000000000, prize.1 + 10000000000000);
                let num_a = (prize.1 * b.0 - prize.0 * b.1) / (a.1 * b.0 - a.0 * b.1);
                let num_b = (prize.1 * a.0 - prize.0 * a.1) / (b.1 * a.0 - b.0 * a.1);
                if num_a * a.0 + num_b * b.0 == prize.0 && num_a * a.1 + num_b * b.1 == prize.1 {
                    Some(3 * num_a + num_b)
                } else {
                    None
                }
            })
            .sum::<i64>();
        println!("{}", fewest_tokens);

        Ok(())
    }
}
