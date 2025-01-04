use crate::adventofcode::AdventOfCode;

use std::collections::{HashMap, HashSet};

use itertools::Itertools;
use rand::rngs::StdRng;
use rand::Rng;
use rand::SeedableRng;

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

const Z_MIN: Index = char_to_index('z') * 36 * 36;

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
    circuits: &HashMap<(Index, Op, Index), HashSet<Index>>,
    x_indices: &Vec<Index>,
    y_indices: &Vec<Index>,
    z_indices: &Vec<Index>,
) -> (
    u64,
    std::time::Duration,
    std::time::Duration,
    std::time::Duration,
) {
    let now = std::time::SystemTime::now();
    let (mut x, mut y) = (x, y);
    // let mut resolved_wires: Vec<i8> = vec![-1; Index::MAX as usize];
    let mut unresolved_wires: HashSet<Index> = HashSet::new();
    let mut wire_values: Vec<i8> = (0..=44).fold(vec![-1; Index::MAX as usize], |mut acc, i| {
        let (xi, yi) = (x_indices[i], y_indices[i]);
        acc[xi as usize] = (x & 1 == 1) as i8;
        acc[yi as usize] = (y & 1 == 1) as i8;
        unresolved_wires.insert(xi);
        unresolved_wires.insert(yi);
        x >>= 1;
        y >>= 1;
        acc
    });
    // Wires where you know the input but the circuit it belongs to isn't solved yet
    let input_pairs_adj: HashMap<Index, HashSet<(Index, Op, Index)>> =
        circuits
            .iter()
            .fold(HashMap::new(), |mut acc, ((x1, op, x2), _)| {
                acc.entry(*x1).or_default().insert((*x1, *op, *x2));
                acc.entry(*x2).or_default().insert((*x1, *op, *x2));
                acc
            });
    let setup_time = now.elapsed().unwrap();
    let now = std::time::SystemTime::now();
    while !unresolved_wires.is_empty() {
        let mut to_add: Vec<Index> = Vec::new();
        let mut to_remove: Vec<Index> = Vec::new();
        let mut changed: bool = false;
        for wire in unresolved_wires.iter() {
            if input_pairs_adj
                .get(wire)
                .unwrap()
                .iter()
                .all(|(x1, op, x2)| {
                    let (v1, v2) = (wire_values[*x1 as usize], wire_values[*x2 as usize]);
                    if v1 != -1 && v2 != -1 {
                        let (v1, v2) = (v1 == 1, v2 == 1);
                        let value: bool = op.eval(v1, v2);
                        for output in circuits.get(&(*x1, *op, *x2)).unwrap() {
                            wire_values[*output as usize] = value as i8;
                            if *output < Z_MIN {
                                to_add.push(*output);
                            }
                        }
                        true
                    } else {
                        false
                    }
                })
            {
                to_remove.push(*wire);
            }
        }
        for wire in to_add {
            unresolved_wires.insert(wire);
            changed = true;
        }
        for wire in to_remove {
            unresolved_wires.remove(&wire);
            changed = true;
        }
        if !changed {
            return (
                0,
                setup_time,
                now.elapsed().unwrap(),
                std::time::Duration::new(0, 0),
            );
        }
    }
    let compute_time = now.elapsed().unwrap();

    let now = std::time::SystemTime::now();
    let res = (0..=45)
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
        .unwrap();
    let final_time = now.elapsed().unwrap();
    (res, setup_time, compute_time, final_time)
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
        let circuits: HashMap<(Index, Op, Index), HashSet<Index>> = lines[blank_line_index + 1..]
            .iter()
            .map(|line| {
                let mut it = line.split("->");
                let inputs_str = it.next().unwrap().trim();
                let output: Index = wire_to_index(it.next().unwrap().trim());
                let mut it = inputs_str.split(" ");
                (
                    (
                        wire_to_index(it.next().unwrap()),
                        Op::from_str(it.next().unwrap()),
                        wire_to_index(it.next().unwrap()),
                    ),
                    output,
                )
            })
            .fold(HashMap::new(), |mut acc, (inputs, output)| {
                acc.entry(inputs).or_default().insert(output);
                acc
            });
        let (x_indices, y_indices, z_indices) = get_x_y_z_indices();
        let (z, _, _, _) = simulate(x, y, &circuits, &x_indices, &y_indices, &z_indices);
        println!("{:?}", z);
        let (mut acc_setup_time, mut acc_compute_time, mut acc_final_time): (
            std::time::Duration,
            std::time::Duration,
            std::time::Duration,
        ) = (
            std::time::Duration::new(0, 0),
            std::time::Duration::new(0, 0),
            std::time::Duration::new(0, 0),
        );
        let circuit_items: Vec<((Index, Op, Index), Index)> = circuits
            .iter()
            .fold(Vec::new(), |mut acc, (inputs, outputs)| {
                for output in outputs {
                    acc.push((*inputs, *output));
                }
                acc
            })
            .into_iter()
            .sorted_by_key(|((x1, _op, x2), output)| (*output, *x1, *x2))
            .collect();
        let mut rng = StdRng::seed_from_u64(69);
        const ALL_ONES: u64 = (1 << 45) - 1;
        let test_cases: Vec<(u64, u64)> = (0..4)
            .map(|_| {
                let x: u64 = rng.gen::<u64>() & ALL_ONES;
                let y: u64 = rng.gen::<u64>() & ALL_ONES;
                (x, y)
            })
            .chain([(ALL_ONES, 1), (1, ALL_ONES)].iter().cloned())
            .collect();
        let mut swap_pairs: Vec<(usize, usize)> = Vec::new();
        let mut zs: Vec<u64> = Vec::new();
        let mut num_matched: u32 = {
            test_cases
                .iter()
                .map(|(x, y)| {
                    let z = simulate(*x, *y, &circuits, &x_indices, &y_indices, &z_indices).0;
                    zs.push(z);
                    ((x + y) ^ z).trailing_zeros()
                })
                .min()
                .unwrap()
        };
        println!("{:?}", num_matched);
        let mut circuit_items = circuit_items;
        for _ in 0..4 {
            for (i, j) in (0..circuit_items.len())
                .combinations(2)
                .map(|v| (v[0], v[1]))
            {
                let temp = circuit_items[i].1;
                circuit_items[i].1 = circuit_items[j].1;
                circuit_items[j].1 = temp;
                let circuits: HashMap<(Index, Op, Index), HashSet<Index>> =
                    circuit_items.iter().fold(
                        HashMap::new(),
                        |mut acc, ((inputs, op, output), output_)| {
                            acc.entry((*inputs, *op, *output))
                                .or_default()
                                .insert(*output_);
                            acc
                        },
                    );
                let mut num_matched_: u32 = u32::MAX;
                let mut new_zs: Vec<u64> = Vec::new();
                let mut good = true;
                for (x, y) in test_cases.iter() {
                    let (z, setup_time, compute_time, final_time) =
                        simulate(*x, *y, &circuits, &x_indices, &y_indices, &z_indices);
                    new_zs.push(z);
                    acc_setup_time += setup_time;
                    acc_compute_time += compute_time;
                    acc_final_time += final_time;
                    let trailing_zeros: u32 = (z ^ (*x + *y)).trailing_zeros();
                    num_matched_ = num_matched_.min(trailing_zeros);
                    if trailing_zeros < num_matched {
                        good = false;
                    }
                }
                if itertools::izip!(test_cases.iter(), zs.iter(), new_zs.iter()).all(
                        |((x, y), z, z_)| {
                            ((x + y) ^ *z).count_ones() > ((x + y) ^ *z_).count_ones()
                        },
                    )
                {
                    num_matched = num_matched_;
                    zs = new_zs;
                    println!("Swapped: {:?} {:?}", i, j);
                    println!("{:?}", num_matched);
                    swap_pairs.push((i, j));
                    break;
                }
                let temp = circuit_items[i].1;
                circuit_items[i].1 = circuit_items[j].1;
                circuit_items[j].1 = temp;
            }
        }
        println!("Num matched: {:?}", num_matched);
        println!("Setup time: {:?}", acc_setup_time);
        println!("Compute time: {:?}", acc_compute_time);
        println!("Final time: {:?}", acc_final_time);

        Ok(())
    }
}
