# 🛡️ C++ to Rust: The Oxidization Journey

> **Motivation**
>
> As a C++ developer, I found that most existing Rust tutorials act as introduction to programming, rather than a migration guide for systems programmers. They explain *what* a pointer is, not *how* Rust's references differ from C++ pointers.
>
> **There wasn't a fast-track guide for C++ developers, so I decided to write one as I learn.**

## 📚 What is this?
This repository documents my transition from C++ to Rust, focusing on:
* Mapping C++ concepts (RAII, Pointers, CMake) to Rust (Ownership, References, Cargo/Bazel).
* Implementing systems programming tasks using Tree-sitter and low-level APIs.
* Avoiding common pitfalls when unlearning C++ habits.





| C++  | C++ Example                   | Rust | Rust Example    | Description     | Note                                |
| ---- | ----------------------------- | ---- | --------------- | --------------- | ----------------------------------- |
| ::   | xxxxxxxxxx let mut a = 10;sql | ::   | std::io::stdout | Almost the same | [namespace.md](./Note/namespace.md) |
|      |                               |      |                 |                 |                                     |
|      |                               |      |                 |                 |                                     |



| **场景**              | **C++ 写法**                    | **Rust 写法**     | **备注**                                |
| --------------------- | ------------------------------- | ----------------- | --------------------------------------- |
| **访问命名空间/模块** | `std::cout`                     | `std::io::stdin`  | 几乎一模一样                            |
| **访问静态方法**      | `MyClass::create()`             | `MyStruct::new()` | 都是用于“类/结构体”级别的调用           |
| **访问枚举值**        | `Color::Red` (C++11 enum class) | `Color::Red`      | 一模一样                                |
| **访问实例方法**      | `obj.method()`                  | `obj.method()`    | **注意**：实例方法都用点 `.`，不用 `::` |