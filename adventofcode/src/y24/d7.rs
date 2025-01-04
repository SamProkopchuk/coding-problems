use crate::adventofcode::AdventOfCode;

use itertools::Itertools;

use itertools::repeat_n;

pub struct Day;

type Equation = (i64, Vec<i64>);

#[derive(Copy, Clone, Debug)]
enum Operation {
    Add = 0,
    Multiply = 1,
    Concatenate = 2,
}

const P1_OPERATIONS: [Operation; 2] = [Operation::Add, Operation::Multiply];
const P2_OPERATIONS: [Operation; 3] = [Operation::Add, Operation::Multiply, Operation::Concatenate];

fn concatenate(a: i64, b: i64) -> i64 {
    let mut a_ = a;
    let mut b_ = b;
    while b_ > 0 {
        a_ *= 10;
        b_ /= 10;
    }
    a_ + b
}

fn evaluate(nums: &[i64], operations: &[Operation]) -> i64 {
    assert_eq!(nums.len() - 1, operations.len());
    let mut total: i64 = nums[0];
    for i in 0..operations.len() {
        match operations[i] {
            Operation::Add => {
                total += nums[i + 1];
            }
            Operation::Multiply => {
                total *= nums[i + 1];
            }
            Operation::Concatenate => {
                total = concatenate(total, nums[i + 1]);
            }
        }
    }
    total
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let equations: Vec<Equation> = Day::input_lines(2024, 7)?
            .iter()
            .map(|line| {
                let mut it = line.split(":");
                let value: i64 = it.next().unwrap().parse::<i64>().unwrap();
                let nums: Vec<i64> = it
                    .next()
                    .unwrap()
                    .split_whitespace()
                    .map(|x| x.parse::<i64>().unwrap())
                    .collect();
                (value, nums)
            })
            .collect();

        let mut total: i64 = 0;
        for (value, nums) in equations.iter() {
            for op_comb in repeat_n(P1_OPERATIONS, nums.len() - 1).multi_cartesian_product() {
                if *value == evaluate(nums, &op_comb) {
                    total += value;
                    break;
                }
            }
        }
        println!("{}", total);

        let mut total: i64 = 0;
        for (value, nums) in equations {
            for op_comb in repeat_n(P2_OPERATIONS, nums.len() - 1).multi_cartesian_product() {
                if value == evaluate(&nums, &op_comb) {
                    total += value;
                    break;
                }
            }
        }
        println!("{}", total);

        Ok(())
    }
}
