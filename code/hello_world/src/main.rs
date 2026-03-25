fn process_string(sv: &str) {
    // 1. 获取字节长度是 O(1) 的，因为 &str 这个胖指针里直接存了长度
    println!("Length (in bytes): {}", sv.len());

    // 2. 访问第一个字符
    // 注意：Rust 字符串是 UTF-8 编码的，不支持像 sv[0] 这样直接索引（为了防止切开多字节字符）
    // 我们通常用 .chars() 迭代器来安全地获取字符
    let x: Option<char> = sv.chars().next();

    match x {
        Some(val) => println!("First char: {}", val),
        None => {}
    }
    if let Some(val) = sv.chars().next(){
        println!("First char: {}", val)
    }
}

fn main() {
    // 情况 1：支持从 String 转换（类似 std::string）
    let s = String::from("Hello World");
    process_string(&s); // 通过 & 触发 Deref Coercion，自动转为 &str

    // 情况 2：支持字面量（类似 "Literal"，无堆分配）
    process_string("Literal");

    // 情况 3：支持从字节数组手动构造（类似 {arr, 2}）
    let arr = [72, 105]; // 'H' 和 'i' 的 ASCII 码
    // Rust 强制要求检查 UTF-8 有效性，所以这里返回的是 Result
    if let Ok(s_from_arr) = std::str::from_utf8(&arr) {
        process_string(s_from_arr);
    }
}