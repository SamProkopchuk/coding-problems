use std::collections::BTreeSet;
use text_io;

fn main() {
    let q: usize = text_io::read!();
    for _ in 0..q {
        let (n, m): (usize, i64) = (text_io::read!(), text_io::read!());
        let mut best: i64 = 0;
        let mut cumsum: i64 = 0;
        let mut cumsums: BTreeSet<i64> = BTreeSet::new();
        for _ in 0..n {
            let x: i64 = text_io::read!();
            cumsum = (cumsum + x).rem_euclid(m);
            let target: i64 = cumsum + 1;
            // Find largest element in cumsums that is >= target, if it exists
            if let Some(&largest) = cumsums.range(target..).next() {
                best = best.max(m + cumsum - largest);
            } else {
                best = best.max(cumsum);
            }
            cumsums.insert(cumsum);
        }

        println!("{}", best);
    }
}
