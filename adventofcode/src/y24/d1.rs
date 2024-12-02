use std::collections::HashMap;
use std::iter::zip;

use crate::adventofcode::AdventOfCode;

pub struct Day;

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let (mut ls, mut rs): (Vec<i32>, Vec<i32>) = Day::input_lines(2024, 1)?
            .into_iter()
            .map(|line| {
                let (l, r) = line.split_once("   ").unwrap();
                (
                    l.parse::<i32>().ok().unwrap(),
                    r.parse::<i32>().ok().unwrap(),
                )
            })
            .unzip();
        ls.sort();
        rs.sort();

        // Assume no overflow
        let distance: i32 = zip(ls.iter(), rs.iter()).fold(0, |acc, (l, r)| acc + (l - r).abs());
        println!("{distance}");

        let rcounts = rs.iter().fold(HashMap::new(), |mut acc, r| {
            acc.entry(r).and_modify(|c| *c += 1).or_insert(1);
            acc
        });
        let similarity: i32 = ls
            .iter()
            .fold(0, |acc, l| acc + l * rcounts.get(l).unwrap_or(&0));
        println!("{similarity}");

        Ok(())
    }
}
