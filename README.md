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

#### Byte Type

- `byte`: 8 bit

#### Character Type

- `char`: a character

#### Reference Type

- `List` is a reference type of the structure `struct List {}`

### Literal

- Decimal: eg: `39`, `94`
- Octal: starts with `0`, eg: `032`, `064`
- Binary: starts with `0b`, eg: `0b1010`
- Hexadecimal: starts with `0x`, eg: `0xff`
- String: eg: `"hello world"`

### Operator

- Arithmetic operations: add `+`, subtract `-`, multiply `*`, divide `/`
- Shift operations: left shift `<<`, right shift `>>`
- Type judgment: `instanceof`

### Conditional Judgment

**if**

```marmot
if(a > b) {
    // ...
} else if (a > c) {
    // ...
} else {
    // ...
}
```

### Loop Statement

**for**

```marmot
for (int i = 0; i < 20; i ++) {
    // ...
    continue; // or break;
}
```


**while**

```marmot
while(true) {
    // ...
    continue; // or break;
}
```

### match statement

Since Marmot does not directly provide `null` judgment, the referenced non-null judgment needs to use the `match` statement.

```marmot
match car {
    val -> {
        // if car is not null
    }

    null -> {
        // if car is null
    }
}
```

where `val` is just the variable name, it can be anything, for example: `carVal` etc.

### Structure

A structure type is a type used to organize data. All properties of a structure are public properties, as follows:

```marmot
struct Node {
    Node prev;
    Node next;
    u_int32 val;
}
```

**Generic**

Structures can define a class of structures through generics, as follows:

```marmot
struct Node<V> {
    Node<V> prev;
    Node<V> next;
    V val;
}
```

**Inherit**

A structure can inherit the properties of its parent structure, and a structure supports multiple inheritance, that is, a structure can have multiple parent structures, as follows:

```marmot
struct A {
    u_int32 a;
}

struct B<T> {
    T b;
}

struct C : A, B<u_int32> {
    u_int32 c;
}
```

The structure `C` is equivalent to the following definition:

```marmot
struct C {
    u_int32 a;
    u_int32 b;
    u_int32 c;
}
```

The inheritance of generic structures is as follows:

```marmot
struct A<T> {
    T a;
}

struct B<K> {
    K b;
}

struct C<V> : A<V>, B<u_int32> {
    u_int32 c1;
    V c2;
}
```

The structure `C` is equivalent to the following definition:

```marmot
struct C<V> {
    V a;
    u_int32 b;
    u_int32 c1;
    V c2;
}
```

**Create**

Creating a structure will apply for memory space and return a reference to the structure, as follows:

```marmot
Car car = new Car();
```

Create a generic struct:

```marmot
Map<u_int32, u_int32> map = new Map<>();
```

**Set property value**

```marmot
Car car = new Car();
car.weight(32);
```

**Get property value**

```marmot
Car car = new Car();
u_int32 weight = car.weight();
```

### Function

A function is the smallest unit of execution code, and a function is defined by the keyword `func`, as follows:

```marmot
func insert[Map<K, V>](K key, V value) : V {
    V oldVal;
    // ... do map insert
    u_int32 size = _.size;

    ret oldVal;
}
```

Among them, `insert` is the function name, `Map<K, V>` is the calling point of the function, `key` and `value` are the parameter names of the function, `V` after `:` is the return type of the function, The return value is returned by `ret`.

Call site: It is a structure type, and the function body can access the attributes of the structure through the `_` symbol. For example, `_.size` accesses the `size` attribute of the `Map<K, V>` structure.

**No return value**

```marmot
func eat[Animal]() : void {

}
```

Or:

```marmot
func eat[Animal]() {

}
```

**Global function**

A global function is a function that does not specify a calling point. A general function can be called by all structures, as follows:

```marmot
func do() {

}
```

Or:

```marmot
func do[]() {

}
```

**Main Function**

The Main function is the entry function of the program, as follows:

```marmot
func main[](u_int32 argc, String[] argv) : u_int32 {
    ret 0;
}
```

**Function call**

Structures can use `->` to call functions and general functions whose call point is their own or parent class.

as follows:

```marmot
func main[](u_int32 argc, String[] argv) : u_int32 {
    Map<u_int32, u_int32> map = new Map<>();
    map -> insert(8. 64);
    ret 0;
}
```

**Lambda expressions**

```marmot
func sayHallo = [Teacher]() -> {
    printl("I am {}, my age is {}, I am a teacher of {}", _.name, _.age, _.school);
}
```

```marmot
func sayHallo0 = func sayHallo[Teacher];
```

**Namespaces**

```marmot
namespace MarmotGroup;
```