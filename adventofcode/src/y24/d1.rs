use crate::adventofcode::AdventOfCode;

pub struct Day;

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let (mut ls, mut rs): (Vec<i32>, Vec<i32>) = Day::input_lines(2024, 1)?
            .into_iter()
            .map(|line| {
                let (first, second) = line.split_once("   ").unwrap();
                (
                    first.parse::<i32>().ok().unwrap(),
                    second.parse::<i32>().ok().unwrap(),
                )
            })
            .unzip();
        ls.sort();
        rs.sort();

        // Assume no overflow
        let distance: i32 =
            std::iter::zip(ls.iter(), rs.iter()).fold(0, |acc, (l, r)| acc + (l - r).abs());
        println!("{distance}");

        Ok(())
    }
}
