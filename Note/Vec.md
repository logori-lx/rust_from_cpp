# 排序
## 升序排序
### 稳定排序sort()
能够确保先出现的元素一定在后出现的元素前面
```rust
let mut val = vec![3,1,23,4];
val.sort(); //升序排序
println!("{:?}", val);
```
输出结果为:
\[1,3,4,23\]

### 不稳定排序sort_unstable()
不能够确保先出现的元素一定在后出现的元素前面，但是性能比sort()更好，所以对于基础类型，比如i32之类的，优先用不稳定排序
```rust
let mut val = vec![3,1,23,4];
val.sort_unstable(); //升序排序
println!("{:?}", val);
```
## 降序排序
rust中并没有C++中的反向迭代器rbegin, rend，所以降序排序只能够通过类似自定义排序的方式来实现。
```rust
use std::cmp::Reverse;
let mut val = vec![3,1,23,4];
val.sort_by_key(|w| Reverse(*w)); //升序排序
println!("{:?}", val);
```
输出结果为:
\[23, 4, 3, 1\]
对应C++中的
```C++
vector<int> val(3,1,23,4);
sort(val.begin(), val.end(), [](int a, int b){ return a > b});
```
### 自定义排序
```rust
struct User {
    name: String,
    age: u32,
}
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
```
输出为：
\[User { name: "Bob", age: 3 }, User { name: "Jackie", age: 3 }, User { name: "Alice", age: 12 }\]