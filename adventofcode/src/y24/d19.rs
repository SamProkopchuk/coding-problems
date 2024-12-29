use crate::adventofcode::AdventOfCode;

use std::collections::BTreeMap;

use itertools::Itertools;

pub struct Day;

type Ways = u128;

fn num_ways_for_design(towels: &Vec<&str>, design: &str) -> Ways {
    let mut num_ways: Ways = 0;
    let mut partial_matches: BTreeMap<usize, Ways> = BTreeMap::from([(0, 1)]);
    while let Some((index, partial_ways)) = partial_matches.pop_first() {
        // Can be sped up with binary search
        let mut start_match_index: usize = towels
            .iter()
            .position(|towel| design[index..].starts_with(towel))
            .unwrap_or(towels.len());
        while start_match_index < towels.len()
            && design.chars().skip(index).next().unwrap()
                == towels[start_match_index].chars().next().unwrap()
        {
            if design[index..].starts_with(towels[start_match_index]) {
                let new_index = index + towels[start_match_index].len();
                if new_index == design.len() {
                    num_ways += partial_ways;
                } else {
                    partial_matches
                        .entry(new_index)
                        .and_modify(|ways| *ways += partial_ways)
                        .or_insert(partial_ways);
                }
            }
            start_match_index += 1;
        }
    }
    num_ways
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let lines: Vec<String> = Day::input_lines(2024, 19)?;

        let towels: Vec<&str> = lines
            .first()
            .unwrap()
            .split(",")
            .map(|towel| towel.trim())
            .sorted()
            .collect();
        let designs: Vec<&str> = lines.iter().skip(2).map(|line| line.as_str()).collect();
        let num_ways_for_designs: Vec<Ways> = designs
            .iter()
            .map(|design| num_ways_for_design(&towels, design))
            .collect();
        let num_possible_designs: usize = num_ways_for_designs
            .iter()
            .filter(|&&num_ways| num_ways > 0)
            .count();
        println!("{}", num_possible_designs);
        let num_total_ways: Ways = num_ways_for_designs.iter().sum();
        println!("{}", num_total_ways);

        Ok(())
    }
}
