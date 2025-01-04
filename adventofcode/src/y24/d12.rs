use crate::adventofcode::AdventOfCode;

use std::collections::HashSet;

pub struct Day;

type Point = (usize, usize);
type Direction = (isize, isize);

const DIRECTIONS: [(isize, isize); 4] = [(0, 1), (-1, 0), (0, -1), (1, 0)];

fn next(point: Point, direction: Direction) -> Point {
    (
        (point.0 as isize + direction.0) as usize,
        (point.1 as isize + direction.1) as usize,
    )
}

fn is_valid(farm: &Vec<Vec<char>>, point: Point) -> bool {
    (0..farm.len()).contains(&point.0) && (0..farm[0].len()).contains(&point.1)
}

fn get_num_corners(farm: &Vec<Vec<char>>, point: Point) -> u32 {
    let type_: char = farm[point.0][point.1];
    let mut num_corners: u32 = 0;
    for da in 0..DIRECTIONS.len() {
        let db = (da + 1) % DIRECTIONS.len();
        let point_a = next(point, DIRECTIONS[da]);
        let point_b = next(point, DIRECTIONS[db]);
        num_corners += ((!is_valid(farm, point_a) || farm[point_a.0][point_a.1] != type_)
            && (!is_valid(farm, point_b) || farm[point_b.0][point_b.1] != type_))
            as u32;
        let point_ = next(point_a, DIRECTIONS[db]);
        num_corners += ((is_valid(farm, point_a) && farm[point_a.0][point_a.1] == type_)
            && (is_valid(farm, point_b) && farm[point_b.0][point_b.1] == type_)
            && (farm[point_.0][point_.1] != type_)) as u32;
    }
    num_corners
}

fn get_area_perimeter_num_sides(
    farm: &Vec<Vec<char>>,
    point: Point,
    seen: &mut HashSet<Point>,
) -> (u32, u32, u32) {
    let type_: char = farm[point.0][point.1];
    let mut area: u32 = 0;
    let mut num_connections_x2: u32 = 0;
    let mut num_corners: u32 = get_num_corners(farm, point);

    seen.insert(point);
    let mut stack: Vec<Point> = vec![point];
    while let Some(point) = stack.pop() {
        area += 1;

        for direction in DIRECTIONS.iter() {
            let point_ = next(point, *direction);
            if is_valid(farm, point_) && farm[point_.0][point_.1] == type_ {
                num_connections_x2 += 1;
                if !seen.contains(&point_) {
                    num_corners += get_num_corners(farm, point_);
                    seen.insert(point_);
                    stack.push(point_);
                }
            }
        }
    }
    (area, 4 * area - num_connections_x2, num_corners)
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let farm: Vec<Vec<char>> = Day::input_lines(2024, 12)?
            .iter()
            .map(|line| line.chars().collect())
            .collect();
        assert!(farm.iter().all(|row| row.len() == farm[0].len()));

        let mut seen: HashSet<Point> = HashSet::new();
        let (total_price, total_discounted_price): (u32, u32) =
            itertools::iproduct!(0..farm.len(), 0..farm[0].len())
                .filter_map(|(i, j)| {
                    if !seen.contains(&(i, j)) {
                        let (area, perimeter, num_sides) =
                            get_area_perimeter_num_sides(&farm, (i, j), &mut seen);
                        Some((area * perimeter, area * num_sides))
                    } else {
                        None
                    }
                })
                .fold(
                    (0, 0),
                    |(total_price, total_discounted_price), (price, discounted_price)| {
                        (
                            total_price + price,
                            total_discounted_price + discounted_price,
                        )
                    },
                );
        println!("{:?}", total_price);
        println!("{:?}", total_discounted_price);

        Ok(())
    }
}
