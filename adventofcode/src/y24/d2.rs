use crate::adventofcode::AdventOfCode;

pub struct Day;

fn safe_difference(x: i32, min_diff: i32, max_diff: i32) -> bool {
    min_diff <= x && x <= max_diff
}

fn all_increasing(v: &[i32], min_diff: i32, max_diff: i32, mut may_skip: bool) -> bool {
    let mut i: usize = 0;
    while i < v.len() - 1 {
        let diff: i32 = v[i + 1] - v[i];
        if safe_difference(diff, min_diff, max_diff) {
            i += 1;
            continue;
        }
        if !may_skip {
            return false;
        }
        if i + 2 >= v.len() || safe_difference(v[i + 2] - v[i], min_diff, max_diff) {
            // Skip i+1
            i += 2;
            may_skip = false;
        } else if i == 0 || safe_difference(v[i + 1] - v[i - 1], min_diff, max_diff) {
            // Skip i
            i += 1;
            may_skip = false;
        } else {
            return false;
        }
    }
    true
}

fn is_safe(v: &[i32], may_skip: bool) -> bool {
    all_increasing(v, 1, 3, may_skip) || all_increasing(v, -3, -1, may_skip)
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let reports: Vec<Vec<i32>> = Day::input_lines(2024, 2)?
            .into_iter()
            .map(|line| {
                line.split(" ")
                    .map(|x| x.parse::<i32>().ok().unwrap())
                    .collect()
            })
            .collect();
        let num_safe: i32 = reports
            .iter()
            .fold(0, |acc, report| acc + is_safe(report, false) as i32);
        println!("{num_safe}");

        let num_safe_with_may_skip: i32 = reports
            .iter()
            .fold(0, |acc, report| acc + is_safe(report, true) as i32);
        println!("{num_safe_with_may_skip}");

        Ok(())
    }
}
