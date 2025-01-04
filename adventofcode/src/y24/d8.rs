use crate::adventofcode::AdventOfCode;

use std::collections::{BTreeSet, HashMap, HashSet};

use itertools::Itertools;

pub struct Day;

type Coordinate = (usize, usize);

const EMPTY: char = '.';

// Abandoning "clean code" starting today, to speedup development.
// Ex: No "City" struct...
impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let city: Vec<Vec<char>> = Day::input_lines(2024, 8)?
            .iter()
            .map(|line| line.chars().collect())
            .collect();

        let num_rows: usize = city.len();
        let num_cols: usize = city[0].len();
        assert!(city.iter().all(|row| row.len() == num_cols));

        let nodes: HashMap<char, BTreeSet<Coordinate>> = itertools::iproduct!(
            0..num_rows,
            0..num_cols
        )
        .fold(HashMap::new(), |mut acc, (i, j)| {
            let c: char = city[i][j];
            if c == EMPTY {
                return acc;
            }
            acc.entry(c).or_default().insert((i, j));
            acc
        });
        let antinodes: HashSet<Coordinate> =
            nodes.iter().fold(HashSet::new(), |mut acc, (_, coords)| {
                for (&coordi, &coordj) in coords.iter().tuple_combinations() {
                    let (xi, yi): (isize, isize) = (coordi.0 as isize, coordi.1 as isize);
                    let (xj, yj): (isize, isize) = (coordj.0 as isize, coordj.1 as isize);
                    let direction: (isize, isize) = (xj - xi, yj - yi);
                    let (x, y): (usize, usize) =
                        ((xj + direction.0) as usize, (yj + direction.1) as usize);
                    if (0..num_rows).contains(&x) && (0..num_cols).contains(&y) {
                        acc.insert((x, y));
                    }
                    let (x, y): (usize, usize) =
                        ((xi - direction.0) as usize, (yi - direction.1) as usize);
                    if (0..num_rows).contains(&x) && (0..num_cols).contains(&y) {
                        acc.insert((x, y));
                    }
                }
                acc
            });
        println!("{:?}", antinodes.len());
        let antinodes: HashSet<Coordinate> =
            nodes.iter().fold(HashSet::new(), |mut acc, (_, coords)| {
                for (&coordi, &coordj) in coords.iter().tuple_combinations() {
                    let (xi, yi): (isize, isize) = (coordi.0 as isize, coordi.1 as isize);
                    let (xj, yj): (isize, isize) = (coordj.0 as isize, coordj.1 as isize);
                    let direction: (isize, isize) = (xj - xi, yj - yi);
                    let (mut x, mut y): (usize, usize) = (xj as usize, yj as usize);
                    while (0..num_rows).contains(&x) && (0..num_cols).contains(&y) {
                        acc.insert((x, y));
                        x = (x as isize + direction.0) as usize;
                        y = (y as isize + direction.1) as usize;
                    }
                    let (mut x, mut y): (usize, usize) = (xi as usize, yi as usize);
                    while (0..num_rows).contains(&x) && (0..num_cols).contains(&y) {
                        acc.insert((x, y));
                        x = (x as isize - direction.0) as usize;
                        y = (y as isize - direction.1) as usize;
                    }
                }
                acc
            });
        println!("{:?}", antinodes.len());

        Ok(())
    }
}
