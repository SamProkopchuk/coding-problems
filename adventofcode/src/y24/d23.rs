use crate::adventofcode::AdventOfCode;

use std::collections::{BTreeMap, BTreeSet};

use itertools::Itertools;

pub struct Day;

type Node = u16;
type Edge = (Node, Node);

const A_BASE: Node = 'a' as Node;

fn str_to_node(node: &str) -> Node {
    assert!(node.len() == 2);
    node.chars().fold(0, |acc, c| acc * 26 + c as Node - A_BASE)
}

fn node_to_str(index: Node) -> String {
    (0..2)
        .fold((String::new(), index), |(mut acc, index), _| {
            acc.push((index % 26 + A_BASE) as u8 as char);
            (acc, index / 26)
        })
        .0
        .chars()
        .rev()
        .collect()
}

// Return the max clique that includes node
fn max_clique(
    adj: &BTreeMap<Node, BTreeSet<Node>>,
    node: Node,
    best_so_far: &mut usize,
) -> BTreeSet<Node> {
    let mut clique: BTreeSet<Node> = BTreeSet::new();
    let neighbors: Vec<Node> = adj.get(&node).unwrap().iter().copied().collect();
    for n in 1..=neighbors.len() {
        if n < *best_so_far {
            continue;
        }
        for comb in neighbors.iter().combinations(n) {
            let mut candidates: BTreeSet<Node> = comb.into_iter().copied().collect();
            let mut no_break = true;
            for candidate in candidates.iter().copied().collect::<Vec<Node>>() {
                candidates.remove(&candidate);
                if !adj.get(&candidate).unwrap().is_superset(&candidates) {
                    no_break = false;
                    break;
                }
                candidates.insert(candidate);
            }
            if no_break && candidates.len() > clique.len() {
                candidates.insert(node);
                clique = candidates;
                *best_so_far = clique.len();
            }
        }
    }
    clique
}

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let edges: Vec<Edge> = Day::input_lines(2024, 23)?
            .iter()
            .map(|line| {
                let mut parts = line.split("-");
                (
                    str_to_node(parts.next().unwrap()),
                    str_to_node(parts.next().unwrap()),
                )
            })
            .collect();
        let adj: BTreeMap<Node, BTreeSet<Node>> =
            edges.iter().fold(BTreeMap::new(), |mut acc, (a, b)| {
                acc.entry(*a).or_insert(BTreeSet::new()).insert(*b);
                acc.entry(*b).or_insert(BTreeSet::new()).insert(*a);
                acc
            });
        let start_with_t_indices: BTreeSet<Node> =
            (0..26).map(|i| (('t' as Node - A_BASE) * 26 + i)).collect();
        let mut ans: Node = 0;
        for t in &start_with_t_indices {
            let neighbors = adj.get(&t);
            if neighbors.is_none() {
                continue;
            }
            let neighbors = neighbors.unwrap();
            for neighbor in neighbors {
                if start_with_t_indices.contains(neighbor) && neighbor < t {
                    continue;
                }
                if let Some(neighbor_neighbors) = adj.get(neighbor) {
                    for neighbor_neighbor in neighbor_neighbors {
                        // Keep everything ordered to avoid double counting
                        if neighbor_neighbor < neighbor
                            || (start_with_t_indices.contains(neighbor_neighbor)
                                && neighbor_neighbor < t)
                        {
                            continue;
                        }
                        if neighbors.contains(neighbor_neighbor) {
                            ans += 1;
                        }
                    }
                }
            }
        }
        println!("{}", ans);
        let mut best_so_far = 0;
        let max_clique: BTreeSet<Node> = adj
            .keys()
            .map(|&node| {
                let max_clique = max_clique(&adj, node, &mut best_so_far);
                max_clique
            })
            .max_by_key(|clique| clique.len())
            .unwrap();
        let max_clique_str: String = max_clique.iter().map(|&node| node_to_str(node)).join(",");
        println!("{}", max_clique_str);

        Ok(())
    }
}
