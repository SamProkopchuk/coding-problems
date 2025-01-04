use crate::adventofcode::AdventOfCode;

use itertools::Itertools;
use rand::rngs::StdRng;
use rand::Rng;
use rand::SeedableRng;

// The solution for p2 is slow and unoptimized.
// Essentially brute-forcing the solution by swapping pairs and checking if the solution improves.
// Takes ~5s with --release
pub struct Day;

#[derive(Debug, Hash, Eq, PartialEq, Copy, Clone)]
enum Op {
    AND,
    OR,
    XOR,
}

impl Op {
    fn from_str(s: &str) -> Self {
        match s {
            "AND" => Op::AND,
            "OR" => Op::OR,
            "XOR" => Op::XOR,
            _ => panic!("Invalid operator"),
        }
    }
    fn eval(&self, v1: bool, v2: bool) -> bool {
        match self {
            Op::AND => v1 && v2,
            Op::OR => v1 || v2,
            Op::XOR => v1 ^ v2,
        }
    }
}

type Index = u16;

const ALL_ONES: u64 = (1 << 45) - 1;

const fn char_to_index(c: char) -> Index {
    match c {
        '0'..='9' => c as Index - '0' as Index,
        'a'..='z' => c as Index - 'a' as Index + 10,
        _ => panic!("Invalid character"),
    }
}

const fn index_to_char(index: Index) -> char {
    match index {
        0..=9 => (index + '0' as Index) as u8 as char,
        10..=35 => ((index - 10) + 'a' as Index) as u8 as char,
        _ => panic!("Invalid index"),
    }
}

fn wire_to_index(wire: &str) -> Index {
    wire.chars().fold(0, |acc, c| acc * 36 + char_to_index(c))
}

fn index_to_wire(index: Index) -> String {
    (0..3)
        .fold((String::new(), index), |(mut acc, index), _| {
            acc.push(index_to_char(index % 36));
            (acc, index / 36)
        })
        .0
        .chars()
        .rev()
        .collect()
}

fn get_x_y_z_indices() -> (Vec<Index>, Vec<Index>, Vec<Index>) {
    let mut x_indices: Vec<Index> = Vec::new();
    let mut y_indices: Vec<Index> = Vec::new();
    let mut z_indices: Vec<Index> = Vec::new();
    for i in 0..=44 {
        let xi = format!("x{:02}", i);
        let yi = format!("y{:02}", i);
        let zi = format!("z{:02}", i);
        x_indices.push(wire_to_index(&xi));
        y_indices.push(wire_to_index(&yi));
        z_indices.push(wire_to_index(&zi));
    }
    let zi = format!("z{:02}", 45);
    z_indices.push(wire_to_index(&zi));
    (x_indices, y_indices, z_indices)
}

fn simulate(
    x: u64,
    y: u64,
    circuits: &Vec<((Index, Op, Index), Index)>,
    x_indices: &Vec<Index>,
    y_indices: &Vec<Index>,
    z_indices: &Vec<Index>,
) -> u64 {
    let (mut x, mut y) = (x, y);
    let mut wire_values: Vec<i8> = (0..=44).fold(vec![-1; Index::MAX as usize], |mut acc, i| {
        let (xi, yi) = (x_indices[i], y_indices[i]);
        acc[xi as usize] = (x & 1 == 1) as i8;
        acc[yi as usize] = (y & 1 == 1) as i8;
        x >>= 1;
        y >>= 1;
        acc
    });
    assert!(x == 0 && y == 0);
    let mut updated: bool = true;
    while updated {
        updated = false;
        for ((i, op, j), dst) in circuits.iter() {
            if wire_values[*dst as usize] == -1
                && (wire_values[*i as usize] != -1 && wire_values[*j as usize] != -1)
            {
                let (v1, v2): (bool, bool) =
                    (wire_values[*i as usize] == 1, wire_values[*j as usize] == 1);
                updated = true;
                wire_values[*dst as usize] = op.eval(v1, v2) as i8;
            }
        }
    }
    if let Some(_) = circuits
        .iter()
        .find(|(_, dst)| wire_values[*dst as usize] == -1)
    {
        return 0;
    }
    (0..=45)
        .scan((0, 1), |(acc, mul), i| {
            let value = wire_values[z_indices[i] as usize];
            if value != -1 {
                *acc += (value as u64) * *mul;
                *mul *= 2;
                Some(*acc)
            } else {
                assert!(false);
                None
            }
        })
        .last()
        .unwrap()
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let lines: Vec<String> = Day::input_lines(2024, 24)?;
        let blank_line_index: usize = lines.iter().position(|line| line.is_empty()).unwrap();
        let x: u64 = lines[..=44].iter().rev().fold(0, |acc, line| {
            acc * 2
                + line
                    .split(":")
                    .nth(1)
                    .unwrap()
                    .trim()
                    .parse::<u8>()
                    .unwrap() as u64
        });
        let y: u64 = lines[45..blank_line_index]
            .iter()
            .rev()
            .fold(0, |acc, line| {
                acc * 2
                    + line
                        .split(":")
                        .nth(1)
                        .unwrap()
                        .trim()
                        .parse::<u8>()
                        .unwrap() as u64
            });
        let circuits: Vec<((Index, Op, Index), Index)> = lines[blank_line_index + 1..]
            .iter()
            .map(|line| {
                let mut it = line.split("->");
                let inputs_str = it.next().unwrap().trim();
                let dst: Index = wire_to_index(it.next().unwrap().trim());
                let mut it = inputs_str.split(" ");
                (
                    (
                        wire_to_index(it.next().unwrap()),
                        Op::from_str(it.next().unwrap()),
                        wire_to_index(it.next().unwrap()),
                    ),
                    dst,
                )
            })
            .collect();
        let (x_indices, y_indices, z_indices) = get_x_y_z_indices();
        let z = simulate(x, y, &circuits, &x_indices, &y_indices, &z_indices);
        println!("{:?}", z);
        let test_cases: Vec<(u64, u64)> = {
            let mut rng = StdRng::seed_from_u64(69);
            (0..10)
                .map(|_| {
                    let x: u64 = rng.gen::<u64>() & ALL_ONES;
                    let y: u64 = rng.gen::<u64>() & ALL_ONES;
                    (x, y)
                })
                .chain(
                    [(ALL_ONES, 1), (1, ALL_ONES), (ALL_ONES, ALL_ONES)]
                        .iter()
                        .copied(),
                )
                .collect()
        };
        let mut swap_pairs: Vec<(usize, usize)> = Vec::new();
        let mut num_matched: u32 = {
            test_cases
                .iter()
                .map(|(x, y)| {
                    let z = simulate(*x, *y, &circuits, &x_indices, &y_indices, &z_indices);
                    ((x + y) ^ z).trailing_zeros()
                })
                .min()
                .unwrap()
        };
        println!("{:?}", num_matched);
        let mut circuits = circuits;
        while num_matched < 45 {
            for (i, j) in (0..circuits.len()).combinations(2).map(|v| (v[0], v[1])) {
                let temp = circuits[i].1;
                circuits[i].1 = circuits[j].1;
                circuits[j].1 = temp;
                let mut num_matched_: u32 = u32::MAX;
                for (x, y) in test_cases.iter() {
                    let z = simulate(*x, *y, &circuits, &x_indices, &y_indices, &z_indices);
                    let trailing_zeros: u32 = (z ^ (*x + *y)).trailing_zeros();
                    num_matched_ = num_matched_.min(trailing_zeros);
                }
                if num_matched_ > num_matched {
                    num_matched = num_matched_;
                    println!("Swapped: {:?} {:?}", i, j);
                    println!("{:?}", num_matched);
                    swap_pairs.push((i, j));
                    break;
                }
                let temp = circuits[i].1;
                circuits[i].1 = circuits[j].1;
                circuits[j].1 = temp;
            }
        }
        println!(
            "{:?}",
            swap_pairs
                .iter()
                .copied()
                .flat_map(|(i, j)| vec![i, j])
                .map(|i| index_to_wire(circuits[i].1))
                .sorted()
                .join(",")
        );

        Ok(())
    }
}
