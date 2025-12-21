# Rust Learn note

# 基础概念

## Cargo

### 创建新项目

```sql
cargo new {project_name}
```

### 编译运行代码

编译项目，默认为**debug模式**，cargo会以最快的速度编译项目，但不会对其进行任何优化，所以编译速度虽然快，但运行速度会相对慢些，同时会在${project}/target/debug下创建${project_name}.exe可执行文件

```sql
cargo build
```

**release模式**，编译慢，但会对其进行优化，运行速度快

```sql
cargo build --release
```

运行对应的项目，相当于cargo build + ./xxx.exe

```sql
cargo run （--release）
```

### 代码检查

由于rust需要做很多复杂的编译优化和语言特性解析，所以其编译速度也会变慢，我们可以通过cargo内置的check指令快速的检查代码是否能够通过编译，节省编译时间

```sql
cargo check
```

### Cargo.toml

Cargo.toml指定了项目依赖的package名称和对应的能运行的版本范围，类似于python中的requirements.txt

以下面的Cargo.toml作为示例:

```sql
[package]
name = "hello_world"
version = "0.1.0"
edition = "2024"

[dependencies]
rand = "0.3"
hammer = { version = "0.5.0"}
color = { git = "https://github.com/bjz/color-rs" }
geometry = { path = "crates/geometry" }
```

其中package中描述了项目的描述信息，name定义项目名称，version定义了项目的版本，edition定义了rust的大版本，此处为2024说明为Rust edition 2024的版本。

dependencies定义了项目依赖，其有几种写法

```sql
# 引入rust 标准库，其中0.3表示0.3.1 0.3.2 ...
# 都可以作为依赖
rand = "0.3"
# 也为引入rust 标准库，但这种方式可以使用feature功能
# 只引入必要的库，或者额外引入一些这个库的其他功能
hammer = { version = "0.5.0"}
# 从github引入库
color = { git = "https://github.com/bjz/color-rs" }
# 用相对路劲引入本地的库
geometry = { path = "crates/geometry" }
```

### 变量定义

在rust 中我们使用let去定义一个变量，如

```sql
let a = 10;
```

但rust中默认定义的变量是一个常量，其值不可更改，如果想要更改变量中的值需要这样定义

```sql
let mut a = 10;
```

同时