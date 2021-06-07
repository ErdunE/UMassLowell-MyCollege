fn cartesian_i(al:Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let mut ans = vec![];
    if al.len() == 1 {
        for i in &al[0] { ans.push(vec![*i]) }
    } else if al.len() > 1 {
        let res = cartesian_i(al[1..].to_vec());
        for i in &al[0] { 
            for j in &res {
                let mut new_vec = j.to_vec();
                new_vec.push(*i);
                ans.push(new_vec)
            }
        }
    }
    return ans
}

fn cartesian(mut al:Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    al.reverse();
    return cartesian_i(al);
}



fn main() {
    println!("{:?}", cartesian(vec![vec![1,2,3], vec![5, 6]]));
    println!("{:?}", cartesian(vec![vec![1,2,3], vec![5, 6], vec![7, 8]]));
}
