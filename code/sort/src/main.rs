use std::cmp::Reverse;
#[derive(Debug, Eq, PartialEq)]
struct User {
    name: String,
    age: u32,
}
fn main() {
    let mut val = vec![3,1,23,4];
    val.sort_by_key(|w| Reverse(*w)); //升序排序
    println!("{:?}", &val);

    let mut struct_val = vec![
        User{ name: "Alice".to_string(), age: 12},
        User{ name: "Bob".to_string(), age: 3},
        User{ name: "Jackie".to_string(), age: 3},
    ];
    struct_val.sort_by(|a, b| {
        if a.age == b.age {
            return a.name.cmp(&b.name);
        }
        a.age.cmp(&b.age)
    });
    println!("{:?}",&struct_val);
}