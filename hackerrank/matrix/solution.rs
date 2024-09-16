use std::io;
use std::io::BufRead;
use std::mem;

struct Edge(usize, usize, usize);

fn find_set(parent: &mut Vec<usize>, node: usize) -> usize {
    if node != parent[node] {
        parent[node] = find_set(parent, parent[node]);
    }
    parent[node]
}

fn union_sets(
    parent: &mut Vec<usize>,
    size: &mut Vec<usize>,
    num_machines: &mut Vec<usize>,
    mut a: usize,
    mut b: usize,
) {
    a = find_set(parent, a);
    b = find_set(parent, b);
    if a != b {
        if size[a] < size[b] {
            mem::swap(&mut a, &mut b);
        }
        parent[b] = a;
        size[a] += size[b];
        num_machines[a] += num_machines[b];
    }
}

fn main() {
    let stdin = io::stdin();
    let mut stdin_lineit = stdin.lock().lines();

    let (n, k): (usize, usize) = {
        let line = stdin_lineit.next().unwrap().unwrap();
        let mut parts = line.split_whitespace().map(|x| x.parse().unwrap());
        (parts.next().unwrap(), parts.next().unwrap())
    };

    let mut edges: Vec<Edge> = (0..(n - 1))
        .map(|_| {
            let line = stdin_lineit.next().unwrap().unwrap();
            let mut parts = line.split_whitespace().map(|x| x.parse().unwrap());
            let [a, b, c] = [(); 3].map(|_| parts.next().unwrap());
            Edge(a, b, c)
        })
        .collect();
    edges.sort_by(|a, b| b.2.cmp(&a.2));

    let machines: Vec<usize> = (0..k)
        .map(|_| stdin_lineit.next().unwrap().unwrap().parse().unwrap())
        .collect();

    // Objects for disjoint union set
    let mut parent: Vec<usize> = (0..n).collect();
    let mut size: Vec<usize> = vec![1; n];
    let mut num_machines: Vec<usize> = vec![0; n];
    for machine in machines {
        num_machines[machine] = 1;
    }

    let mut total_cost: u64 = 0;
    for edge in &edges {
        if num_machines[find_set(&mut parent, edge.0)] + num_machines[find_set(&mut parent, edge.1)]
            > 1
        {
            total_cost += edge.2 as u64;
            continue;
        }
        union_sets(&mut parent, &mut size, &mut num_machines, edge.0, edge.1);
    }
    println!("{}", total_cost);
}
