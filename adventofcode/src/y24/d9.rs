use crate::adventofcode::AdventOfCode;

use itertools::repeat_n;

pub struct Day;

impl AdventOfCode for Day {
    fn solve() -> anyhow::Result<()> {
        let disk_map: Vec<char> = Day::input_raw(2024, 9)?.trim().chars().collect();
        let mut disk_init: Vec<i32> = Vec::new();
        disk_init.reserve(disk_map.len() * 10);
        for i in 0..disk_map.len() {
            let block_size: usize = disk_map[i].to_digit(10).unwrap() as usize;
            if i % 2 == 0 {
                disk_init.extend(repeat_n(i as i32 / 2, block_size));
            } else {
                disk_init.extend(repeat_n(-1, block_size));
            }
        }
        let mut disk: Vec<i32> = disk_init.clone();
        let min_free_index_init: usize = (0..disk.len()).find(|&i| disk[i] == -1).unwrap();
        let mut min_free_index: usize = min_free_index_init;
        for i in (0..disk.len()).rev() {
            if min_free_index > i {
                break;
            } else if disk[i] == -1 {
                continue;
            }
            assert!(disk[min_free_index] == -1);
            disk.swap(min_free_index, i);
            assert!(disk[min_free_index] != -1);
            while disk[min_free_index] != -1 {
                min_free_index += 1;
            }
        }
        let mut checksum: u64 = 0;
        for i in 0..disk.len() {
            if disk[i] == -1 {
                break;
            }
            checksum += (i as u64) * disk[i] as u64;
        }
        println!("{:?}", checksum);
        // Unoptimized version (O(n^2)).
        let mut disk: Vec<i32> = disk_init;
        let mut min_free_index: usize = min_free_index_init;
        let mut i: usize = disk.len() - 1;
        while min_free_index < i {
            if disk[i] == -1 {
                i -= 1;
                continue;
            }
            let block_size: usize = (0..i + 1).rev().take_while(|&j| disk[j] == disk[i]).count();
            let mut temp_free_index: usize = min_free_index;
            let mut free_size: usize = (temp_free_index..i).take_while(|&j| disk[j] == -1).count();
            while free_size < block_size {
                temp_free_index += free_size;
                if temp_free_index >= i {
                    break;
                }
                while disk[temp_free_index] != -1 && temp_free_index < disk.len() {
                    temp_free_index += 1;
                }
                free_size = (temp_free_index..i).take_while(|&j| disk[j] == -1).count();
            }
            if temp_free_index < i {
                for delta in 0..block_size {
                    disk.swap(i - block_size + 1 + delta, temp_free_index + delta);
                }
            }
            while disk[min_free_index] != -1 {
                min_free_index += 1;
            }
            i -= block_size;
        }
        let mut checksum: u64 = 0;
        for i in 0..disk.len() {
            if disk[i] == -1 {
                continue;
            }
            checksum += (i as u64) * disk[i] as u64;
        }
        println!("{:?}", checksum);

        Ok(())
    }
}
