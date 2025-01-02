use crate::adventofcode::AdventOfCode;

use std::collections::{HashMap, HashSet};

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

fn simulate(
    x: u64,
    y: u64,
    circuits: &HashMap<(Index, Op, Index), HashSet<Index>>,
) -> (
    u64,
    std::time::Duration,
    std::time::Duration,
    std::time::Duration,
) {
    let now = std::time::SystemTime::now();
    let (mut x, mut y) = (x, y);
    let mut wire_values: HashMap<Index, bool> = (0..=44).fold(HashMap::new(), |mut acc, i| {
        let (xi, yi) = (format!("x{:02}", i), format!("y{:02}", i));
        acc.insert(wire_to_index(&xi), x & 1 == 1);
        acc.insert(wire_to_index(&yi), y & 1 == 1);
        x >>= 1;
        y >>= 1;
        acc
    });
    // Wires where you know the input but the circuit it belongs to isn't solved yet
    let mut unresolved_wires: HashSet<Index> = wire_values.keys().copied().collect();
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
        for wire in unresolved_wires.iter() {
            if input_pairs_adj
                .get(wire)
                .unwrap()
                .iter()
                .all(|(x1, op, x2)| {
                    if let (Some(v1), Some(v2)) = (wire_values.get(x1), wire_values.get(x2)) {
                        let value: bool = op.eval(*v1, *v2);
                        for output in circuits.get(&(*x1, *op, *x2)).unwrap() {
                            if let Some(existing_value) = wire_values.get(output) {
                                assert!(*existing_value == value);
                                continue;
                            }
                            assert!(wire_values.insert(*output, value).is_none());
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
        }
        for wire in to_remove {
            unresolved_wires.remove(&wire);
        }
    }
    let compute_time = now.elapsed().unwrap();

    let now = std::time::SystemTime::now();
    let res = (0..=45)
        .scan((0, 1), |(acc, mul), i| {
            let zi = format!("z{:02}", i);
            if let Some(value) = wire_values.get(&wire_to_index(&zi)) {
                *acc += (*value as u64) * *mul;
                *mul *= 2;
                Some(*acc)
            } else {
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
        let (z, setup_time, compute_time, final_time) = simulate(x, y, &circuits);
        println!("{:?}", z);
        let src_wires: HashMap<Index, (Index, Index)> =
            circuits
                .iter()
                .fold(HashMap::new(), |mut acc, ((x1, _, x2), outputs)| {
                    for output in outputs.iter() {
                        acc.insert(*output, (*x1, *x2));
                    }
                    acc
                });
        let (mut acc_setup_time, mut acc_compute_time, mut acc_final_time): (
            std::time::Duration,
            std::time::Duration,
            std::time::Duration,
        ) = (
            std::time::Duration::new(0, 0),
            std::time::Duration::new(0, 0),
            std::time::Duration::new(0, 0),
        );
        for i in 0..=44 {
            let mask: u64 = 1 << i;
            for (x, y) in [(0, 0), (0, mask), (mask, 0), (mask, mask)].iter() {
                let (z, setup_time, compute_time, final_time) = simulate(*x, *y, &circuits);
                acc_setup_time += setup_time;
                acc_compute_time += compute_time;
                acc_final_time += final_time;
                let expected_mask = x + y;
                if z & expected_mask != expected_mask {
                    println!("Failed z bit: {}", i);
                    println!("x: {:045b}", x);
                    println!("y: {:045b}", y);
                    println!("z: {:045b}", z);
                }
            }
        }
        println!("Setup time: {:?}", acc_setup_time);
        println!("Compute time: {:?}", acc_compute_time);
        println!("Final time: {:?}", acc_final_time);

        Ok(())
    }
}
