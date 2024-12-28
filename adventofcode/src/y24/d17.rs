use crate::adventofcode::AdventOfCode;

use std::collections::VecDeque;

use itertools::Itertools;

pub struct Day;

type Register = u128;
type IT = u8;
type Instruction = (IT, IT);

type Registers = (Register, Register, Register);

fn combo(registers: &Registers, operand: &IT) -> Register {
    match operand {
        0..=3 => *operand as Register,
        4 => registers.0,
        5 => registers.1,
        6 => registers.2,
        _ => panic!("Invalid operand: {}", operand),
    }
}

fn run_instructions(instructions: &Vec<Instruction>, registers: &mut Registers) -> Vec<Register> {
    let mut ip: usize = 0;
    let mut outputs: Vec<Register> = Vec::new();
    while (0..instructions.len()).contains(&ip) {
        let (op, operand) = instructions[ip];
        match op {
            0 => registers.0 = registers.0 >> combo(registers, &operand),
            1 => registers.1 = registers.1 ^ (operand as Register),
            2 => registers.1 = combo(registers, &operand) % 8,
            3 => {
                if registers.0 != 0 {
                    ip = (operand as usize).wrapping_sub(1);
                }
            }
            4 => registers.1 = registers.1 ^ registers.2,
            5 => outputs.push(combo(registers, &operand) % 8),
            6 => registers.1 = registers.0 >> combo(registers, &operand),
            7 => registers.2 = registers.0 >> combo(registers, &operand),
            _ => panic!("Invalid opcode: {}", op),
        }
        ip = ip.wrapping_add(1);
    }
    outputs
}
// (2,4),(1,2),(7,5),(4,3),(0,3),(1,7),(5,5),(3,0)
// B = A % 8;
// B = B^2
// C = A>>B
// B = B^C
// A = A>>3
// B=B^7
// print(B%8)
//     if A != 0 { ip = 0 }
//
// A = a B = 0 C= 0
// B = (A%8)^2
// C= A>>(A%8)^2
// B = ((A%8)^2)^(A>>(A%8)^2)
// B = ((A%8)^2)^(A>>(A%8)^2)^7
// print(
//     ((A%8)^2)^(A>>(A%8)^2)^7
// )
// A = A >> 3
//
// X = (A%8)^2
// (X ^ (A >> X)) ^ 7

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let lines = Day::input_lines(2024, 17)?;
        let mut registers: Registers = lines[..3]
            .iter()
            .map(|line| {
                line.split(":")
                    .skip(1)
                    .next()
                    .unwrap()
                    .trim()
                    .parse::<Register>()
                    .unwrap()
            })
            .collect_tuple()
            .unwrap();
        let raw_instructions: Vec<IT> = lines
            .last()
            .unwrap()
            .split(":")
            .skip(1)
            .next()
            .unwrap()
            .trim()
            .split(",")
            .map(|value| value.parse::<IT>().unwrap())
            .collect();
        let instructions: Vec<Instruction> =
            raw_instructions.clone().into_iter().tuples().collect();

        let outputs = run_instructions(&instructions, &mut registers);
        println!(
            "{}",
            outputs
                .iter()
                .map(|value| value.to_string())
                .collect::<Vec<String>>()
                .join(",")
        );
        let mut candidates: VecDeque<(Register, Register, usize)> =
            (0..1024).map(|i| (i, 1024, 1)).collect();
        while let Some((a, delta, target_size)) = candidates.pop_front() {
            registers = (a, 0, 0);
            let outputs = run_instructions(&instructions, &mut registers);
            if outputs.len() >= target_size
                && (0..target_size).all(|i| outputs[i] == raw_instructions[i] as Register)
            {
                if target_size == outputs.len() && target_size == raw_instructions.len() {
                    println!("{:?}", a);
                    break;
                } else {
                    for i in 0..8 {
                        candidates.push_back((a + delta * i, delta << 3, target_size + 1));
                    }
                }
            }
        }

        Ok(())
    }
}
