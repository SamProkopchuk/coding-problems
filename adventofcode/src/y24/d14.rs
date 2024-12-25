use crate::adventofcode::AdventOfCode;

use itertools::Itertools;
use std::collections::HashMap;

pub struct Day;

type Vec2D = (i64, i64);

const NUM_ROWS: i64 = 103;
const NUM_COLS: i64 = 101;

const MID_ROW: i64 = NUM_ROWS / 2;
const MID_COL: i64 = NUM_COLS / 2;

fn location(point: Vec2D, velocity: Vec2D, num_steps: i64) -> Vec2D {
    (
        (point.0 + velocity.0 * num_steps).rem_euclid(NUM_COLS),
        (point.1 + velocity.1 * num_steps).rem_euclid(NUM_ROWS),
    )
}

fn get_vec2d(raw: &str) -> Vec2D {
    let relevant = &raw[2..raw.len()];
    let mut parts = relevant.split(',');
    (
        parts.next().unwrap().parse::<i64>().unwrap(),
        parts.next().unwrap().parse::<i64>().unwrap(),
    )
}

fn symmetry_score(points: &Vec<Vec2D>) -> i64 {
    let mut score: i64 = 0;
    let counts: HashMap<&Vec2D, usize> = points.iter().counts();
    for (point, _count) in counts.iter() {
        if point.0 == MID_ROW {
            score += 1;
        } else {
            let mirror_row = NUM_ROWS - point.0;
            if counts.contains_key(&(mirror_row, point.1)) {
                score += 1;
            }
        }
    }
    score
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let robots: Vec<(Vec2D, Vec2D)> = Day::input_lines(2024, 14)?
            .iter()
            .map(|line| {
                line.split_whitespace()
                    .map(|s| get_vec2d(s))
                    .collect_tuple()
                    .unwrap()
            })
            .collect();
        let final_positions: Vec<Vec2D> = robots
            .iter()
            .map(|(point, velocity)| location(*point, *velocity, 100))
            .collect();
        let num_robots_by_quadrant: (i64, i64, i64, i64) =
            final_positions.iter().fold((0, 0, 0, 0), |acc, point| {
                if point.0 < MID_COL && point.1 < MID_ROW {
                    (acc.0 + 1, acc.1, acc.2, acc.3)
                } else if point.0 < MID_COL && point.1 > MID_ROW {
                    (acc.0, acc.1 + 1, acc.2, acc.3)
                } else if point.0 > MID_COL && point.1 < MID_ROW {
                    (acc.0, acc.1, acc.2 + 1, acc.3)
                } else if point.0 > MID_COL && point.1 > MID_ROW {
                    (acc.0, acc.1, acc.2, acc.3 + 1)
                } else {
                    acc
                }
            });
        let score: i64 = num_robots_by_quadrant.0
            * num_robots_by_quadrant.1
            * num_robots_by_quadrant.2
            * num_robots_by_quadrant.3;
        println!("{}", score);
        let mut robots = robots;
        let mut num_steps: i64 = 0;
        while symmetry_score(
            &robots
                .iter()
                .map(|(point, _)| *point)
                .collect::<Vec<Vec2D>>(),
        ) < 100
        {
            robots = robots
                .iter()
                .map(|(point, velocity)| (location(*point, *velocity, 1), *velocity))
                .collect();
            num_steps += 1;
        }
        let mut viz: Vec<Vec<char>> = vec![vec!['.'; NUM_COLS as usize]; NUM_ROWS as usize];
        for (point, _) in robots.iter() {
            viz[point.1 as usize][point.0 as usize] = '#';
        }
        for row in viz.iter() {
            println!("{}", row.iter().collect::<String>());
        }
        println!("{}", num_steps);

        Ok(())
    }
}
