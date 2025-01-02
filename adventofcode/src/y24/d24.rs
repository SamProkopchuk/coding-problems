use crate::adventofcode::AdventOfCode;

use std::collections::{HashMap, HashSet};
use std::ops::AddAssign;

pub struct Day;

type Index = u16;

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
    x_values: &Vec<Index>,
    y_values: &Vec<Index>,
    z_values: &Vec<Index>,
) -> (
    u64,
    std::time::Duration,
    std::time::Duration,
    std::time::Duration,
) {
    let now = std::time::SystemTime::now();
    let mut wire_values: Vec<i8> = vec![-1; Index::MAX as usize];
    let mut unresolved_wires: HashSet<Index> = HashSet::new();
    for i in 0..=44 {
        let xi = (x & (1 << i)) as i8;
        let yi = (y & (1 << i)) as i8;
        wire_values[x_values[i] as usize] = xi;
        wire_values[y_values[i] as usize] = yi;
        unresolved_wires.insert(x_values[i]);
        unresolved_wires.insert(y_values[i]);
    }
    // Wires where you know the input but the circuit it belongs to isn't solved yet
    let input_pairs_adj: HashMap<Index, HashSet<(Index, Op, Index)>> =
        circuits
            .iter()
            .fold(HashMap::new(), |mut acc, ((x1, op, x2), _)| {
                acc.entry(*x1)
                    .or_insert(HashSet::new())
                    .insert((*x1, *op, *x2));
                acc.entry(*x2)
                    .or_insert(HashSet::new())
                    .insert((*x1, *op, *x2));
                acc
            });
    let setup_time = now.elapsed().unwrap();
    let now = std::time::SystemTime::now();
    while !unresolved_wires.is_empty() {
        let mut to_add: Vec<Index> = Vec::new();
        let mut to_remove: Vec<Index> = Vec::new();
        for wire in unresolved_wires.iter() {
            if input_pairs_adj
                .get(&wire)
                .unwrap()
                .into_iter()
                .all(|(x1, op, x2)| {
                    let v1 = wire_values[*x1 as usize];
                    let v2 = wire_values[*x2 as usize];
                    if v1 != -1 && v2 != -1 {
                        let v1 = v1 != 0;
                        let v2 = v2 != 0;
                        let value: bool = op.eval(v1, v2);
                        for output in circuits.get(&(*x1, *op, *x2)).unwrap() {
                            if wire_values[*output as usize] != -1 {
                                assert!(wire_values[*output as usize] == value as i8);
                                continue;
                            }
                            assert!(wire_values[*output as usize] == -1);
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
        to_add.iter().for_each(|wire| {
            unresolved_wires.insert(*wire);
        });
        to_remove.iter().for_each(|wire| {
            unresolved_wires.remove(wire);
        });
    }
    let compute_time = now.elapsed().unwrap();

    let now = std::time::SystemTime::now();
    let res = (0..=45)
        .scan((0, 1), |(acc, mul), i| {
            let value = wire_values[z_values[i] as usize];
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

fn get_x_y_z_values() -> (Vec<Index>, Vec<Index>, Vec<Index>) {
    let (mut x_values, mut y_values, mut z_values) = (Vec::new(), Vec::new(), Vec::new());
    for i in 0..=44 {
        x_values.push(wire_to_index(&format!("x{:02}", i)));
        y_values.push(wire_to_index(&format!("y{:02}", i)));
        z_values.push(wire_to_index(&format!("z{:02}", i)));
    }
    z_values.push(wire_to_index("z45"));
    (x_values, y_values, z_values)
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let lines: Vec<String> = Day::input_lines(2024, 24)?;
        let blank_line_index: usize = lines.iter().position(|line| line.is_empty()).unwrap();
        let x: u64 = lines[..=44].iter().rev().fold(0, |acc, line| {
            acc * 2
                + line
                    .split(":")
                    .skip(1)
                    .next()
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
                        .skip(1)
                        .next()
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
                acc.entry(inputs).or_insert(HashSet::new()).insert(output);
                acc
            });
        let (x_values, y_values, z_values) = get_x_y_z_values();
        let (z, setup_time, compute_time, final_time) =
            simulate(x, y, &circuits, &x_values, &y_values, &z_values);
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
        let mut failed_z_bits: Vec<usize> = Vec::new();
        let mut counts_by_candidate: HashMap<Index, usize> = HashMap::new();
        for i in 0..=44 {
            let mask: u64 = 1 << i;
            for (x, y) in [(0, 0), (0, mask), (mask, 0), (mask, mask)].iter() {
                let (z, setup_time, compute_time, final_time) =
                    simulate(*x, *y, &circuits, &x_values, &y_values, &z_values);
                acc_setup_time += setup_time;
                acc_compute_time += compute_time;
                acc_final_time += final_time;
                let expected_mask = x + y;
                if z & expected_mask != expected_mask {
                    println!("Failed z bit: {}", i);
                    println!("x: {:b}", x);
                    println!("y: {:b}", y);
                    println!("z: {:b}", z);
                    failed_z_bits.push(i);
                    let mut z = z;
                    while z > 0 {
                        let z_bit = z.trailing_zeros();
                        assert!(z_bit <= 45);
                        let zi = format!("z{:02}", z_bit);
                        let z_index = wire_to_index(&zi);
                        let mut src_stack: Vec<Index> = vec![z_index];
                        while let Some(src) = src_stack.pop() {
                            counts_by_candidate.entry(src).or_insert(0).add_assign(1);
                            if let Some((x1, x2)) = src_wires.get(&src) {
                                if !src_wires.get(x1).is_none() {
                                    src_stack.push(*x1);
                                }
                                if !src_wires.get(x2).is_none() {
                                    src_stack.push(*x2);
                                }
                            }
                        }
                        z &= !(1 << z_bit);
                    }
                }
            }
        }
        let mut count_candidate_pairs: Vec<(usize, Index)> = counts_by_candidate
            .iter()
            .map(|(candidate, count)| (*count, *candidate))
            .collect();
        count_candidate_pairs.sort_by_key(|k| std::cmp::Reverse(k.0));
        for (count, candidate) in count_candidate_pairs.iter() {
            println!("Candidate: {}, Count: {}", index_to_wire(*candidate), count);
        }
        println!("Num candidates: {}", counts_by_candidate.len());

        println!("Failed z bits: {:?}", failed_z_bits);
        println!("Setup time: {:?}", acc_setup_time);
        println!("Compute time: {:?}", acc_compute_time);
        println!("Final time: {:?}", acc_final_time);

        Ok(())
    }
}
