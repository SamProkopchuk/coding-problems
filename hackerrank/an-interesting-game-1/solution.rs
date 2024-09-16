use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut stdin_lineit = stdin.lock().lines();

    let g: usize = stdin_lineit.next().unwrap().unwrap().parse().unwrap();
    for _ in 0..g {
        let n: usize = stdin_lineit.next().unwrap().unwrap().parse().unwrap();

        let line = stdin_lineit.next().unwrap().unwrap();
        let mut parts = line.split_whitespace().map(|x| x.parse::<u32>().unwrap());
        let mut v: Vec<(u32, u32)> = (0..n).map(|i| (parts.next().unwrap(), i as u32)).collect();
        v.sort_by(|a, b| b.cmp(&a));

        let mut minidx = v[0].0;
        let mut andy_wins = true;
        for (_, i) in v {
            if i < minidx {
                minidx = i;
                andy_wins = !andy_wins;
            }
        }
        println!("{}", if andy_wins { "ANDY" } else { "BOB" });
    }
}
