use crate::adventofcode::AdventOfCode;

use std::collections::{BTreeMap, HashMap, HashSet};

pub struct Day;

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

impl Direction {
    fn turn(&self) -> (Direction, Direction) {
        match self {
            Direction::Up => (Direction::Left, Direction::Right),
            Direction::Left => (Direction::Down, Direction::Up),
            Direction::Down => (Direction::Right, Direction::Left),
            Direction::Right => (Direction::Down, Direction::Up),
        }
    }
}

type Score = i32;
type Position = (usize, usize, Direction);
type State = (usize, usize, Direction, Score);

const OBSTACLE: char = '#';
// const EMPTY: char = '.';
const START: char = 'S';
const END: char = 'E';

fn next_location(i: usize, j: usize, dir: &Direction) -> (usize, usize) {
    match dir {
        Direction::Up => (i - 1, j),
        Direction::Down => (i + 1, j),
        Direction::Left => (i, j - 1),
        Direction::Right => (i, j + 1),
    }
}

// Returns a tuple of final_state and path-source mapping.
fn get_best_path_data(
    maze: &Vec<Vec<char>>,
    start: (usize, usize),
) -> (Score, HashMap<State, HashSet<State>>) {
    let mut sources: HashMap<State, HashSet<State>> = HashMap::new();
    let mut priority_map: BTreeMap<Score, Vec<Position>> = BTreeMap::new();
    let mut seen_positions: HashSet<Position> = HashSet::new();
    let initial_state: State = (start.0, start.1, Direction::Right, 0);
    sources.insert(initial_state, HashSet::new());
    let initial_position: Position = (start.0, start.1, Direction::Right);
    priority_map.insert(0, vec![initial_position]);
    seen_positions.insert(initial_position);

    let mut lowest_score: Score = Score::MAX;
    while let Some((score, mut positions)) = priority_map.pop_first() {
        if score > lowest_score {
            break;
        }
        let position = positions.pop().unwrap();
        if !positions.is_empty() {
            priority_map.insert(score, positions);
        }
        let (i, j, direction) = position;
        let state: State = (i, j, direction, score);
        if maze[i][j] == END && score <= lowest_score {
            lowest_score = score;
        }
        let (inext, jnext) = next_location(i, j, &direction);
        let next_state: State = (inext, jnext, direction, score + 1);
        if maze[next_state.0][next_state.1] != OBSTACLE
            && (!sources.contains_key(&next_state) || !sources[&next_state].contains(&state))
        {
            sources
                .entry(next_state)
                .or_default()
                .insert(state);
            let next_position: Position = (inext, jnext, direction);
            if !seen_positions.contains(&next_position) {
                seen_positions.insert(next_position);
                priority_map
                    .entry(next_state.3)
                    .or_default()
                    .push(next_position);
            }
        }
        let (left_turn_direction, right_turn_direction) = direction.turn();
        let (inext, jnext) = next_location(i, j, &left_turn_direction);
        let next_state: State = (inext, jnext, left_turn_direction, score + 1001);
        if maze[next_state.0][next_state.1] != OBSTACLE
            && (!sources.contains_key(&next_state) || !sources[&next_state].contains(&state))
        {
            sources
                .entry(next_state)
                .or_default()
                .insert(state);
            let next_position: Position = (inext, jnext, left_turn_direction);
            if !seen_positions.contains(&next_position) {
                seen_positions.insert(next_position);
                priority_map
                    .entry(next_state.3)
                    .or_default()
                    .push(next_position);
            }
        }
        let (inext, jnext) = next_location(i, j, &right_turn_direction);
        let next_state: State = (inext, jnext, right_turn_direction, score + 1001);
        if maze[next_state.0][next_state.1] != OBSTACLE
            && (!sources.contains_key(&next_state) || !sources[&next_state].contains(&state))
        {
            sources
                .entry(next_state)
                .or_default()
                .insert(state);
            let next_position: Position = (inext, jnext, right_turn_direction);
            if !seen_positions.contains(&next_position) {
                seen_positions.insert(next_position);
                priority_map
                    .entry(next_state.3)
                    .or_default()
                    .push(next_position);
            }
        }
    }
    (lowest_score, sources)
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let maze: Vec<Vec<char>> = Day::input_lines(2024, 16)?
            .iter()
            .map(|line| line.chars().collect())
            .collect();
        assert!(maze.iter().all(|row| row.len() == maze[0].len()));
        let start: (usize, usize) = itertools::iproduct!(0..maze.len(), 0..maze[0].len())
            .find(|&(i, j)| maze[i][j] == START)
            .unwrap();
        let (lowest_score, sources) = get_best_path_data(&maze, start);
        println!("{:?}", lowest_score);

        let end: (usize, usize) = itertools::iproduct!(0..maze.len(), 0..maze[0].len())
            .find(|&(i, j)| maze[i][j] == END)
            .unwrap();
        let start_state: State = (start.0, start.1, Direction::Right, 0);
        let mut state_stack: Vec<State> = vec![
            (end.0, end.1, Direction::Right, lowest_score),
            (end.0, end.1, Direction::Left, lowest_score),
            (end.0, end.1, Direction::Up, lowest_score),
            (end.0, end.1, Direction::Down, lowest_score),
        ];
        let mut relevant_states: HashSet<State> = HashSet::from_iter(state_stack.iter().copied());
        while let Some(state) = state_stack.pop() {
            if state == start_state {
                continue;
            }
            if !sources.contains_key(&state) {
                continue;
            }
            for source in sources[&state].iter() {
                if !relevant_states.contains(source) {
                    state_stack.push(*source);
                    relevant_states.insert(*source);
                }
            }
        }

        let num_unique_locations = relevant_states
            .iter()
            .map(|state| (state.0, state.1))
            .collect::<HashSet<(usize, usize)>>()
            .len();
        println!("{:?}", num_unique_locations);

        Ok(())
    }
}
