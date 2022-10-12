[中文文档](./README-ZH-CN.md)

# Marmot Programming Language

The Marmot programming language is designed to implement a programming paradigm that separates data and functions, and has the characteristics of no GC, simple memory structure, and no life cycle. Marmot's goal is not to replace any programming language, like C or C++. Unlike Rust, which can guarantee memory safety at compile time, Marmot requires the user to manually release the allocated memory.

Comparison with other programming languages：

**C programming language**

- Marmot supports generics
- Marmot provides more data structures, like linked lists, hash tables, etc
- Marmot supports struct inheritance
- Marmot provides package management tools

**C++ programming language**

- Marmot does not support object-oriented programming
- Marmot has simpler memory structure
- Marmot provides a unified package management tool
- Marmot has a better module implementation

**Rust programming language**

- Marmot does not support compile-time memory safety checks
- Marmot needs to free memory manually
- Marmot is easier to learn

## Marmot Grammar

### Type System

#### Integer

- `int8`: 8-bit signed integer
- `int16`: 16-bit signed integer
- `int32`: 32-bit signed integer
- `int64`: 64-bit signed integer
- `int128`: 128-bit signed integer
- `u_int8`: 8-bit unsigned integer
- `u_int16`: 16-bit unsigned integer
- `u_int32`: 32-bit unsigned integer
- `u_int64`: 64-bit unsigned integer
- `u_int128`: 128-bit unsigned integer

#### Floating Point Type

- `float`: 32-bit floating point type
- `double`: 64-bit floating point type

#### Boolean Type

- `bool`: values are `true` and `false`