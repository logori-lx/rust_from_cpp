在rust中所有的option都需要进行处理，比如
```rust
let x: Option<char> = sv.chars().next();
match x {
	Some(val) => println!("First char: {}", val),
	None => {} //光写None不对，因为要对option进行处理。
}
```
# Some
Some函数的作用在rust中其实相当于C++中的!= nullptr，some(val)的作用就是如果option非none就把其内容拆包，将其中的数据赋值给val
比如
```rust
let x: Option<char> = sv.chars().next();
//将返回的option x进行比较，如果非None则交给Some函数解包，解包出来的数据赋值给val
match x {
	Some(val) => println!("First char: {}", val),
	None => {}
}
```
同时我们也可以用if let来简写上面这段代码
```rust
//将sv.chars().next()的返回值解包放到val中，如果不能解包则跳过
if let Some(val) = sv.chars().next(){
	println!("First char: {}", val)
}
```
if判断的是next()函数的返回值是否能被Some函数解包，如果能被解包let会创建一个新变量val以供if语句当中使用，否则则跳过if语句。

