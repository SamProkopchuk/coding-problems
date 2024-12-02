use anyhow::{Ok, Result};

use adventofcode::AdventOfCode;

mod adventofcode;
mod api;
mod y24;

use y24::Day;

fn main() -> Result<()> {
    Day::solve()?;

    Ok(())
}
