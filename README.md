# Marmot Programming Language

The Marmot programming language is designed to implement a programming paradigm that separates data and functions, and has the characteristics of no GC, simple memory structure, and no life cycle. Marmot's goal is not to replace any programming language, like C or C++. Unlike Rust, which can guarantee memory safety at compile time, Marmot requires the user to manually release the allocated memory.

Comparison with other programming languages：

**C programming language**


## Grammar

**Data Type**

- Integer: `int8`, `u_int8`, `int16`, `u_int16`, `int32`, `u_int32`, `int64`, `u_int64`, `int128`, `u_int128`
- Charactor: `char`
- Float: `float`, `double`
- Function: `func`

**Inner Type**

`string`

**Struct**

```marmot
struct Person {
    name: string
    age: u_int8
}
```

**Inheritance**

```marmot
struct Teacher extends Person {
    school: string
}
```

**Function**

```marmot
func sayHallo[Human]() {
    printl("I am {}, my age is {}", _.name, _.age);
}

func sayHallo[Teacher]() {
    printl("I am {}, my age is {}, I am a teacher of {}", _.name, _.age, _.school);
}
```

**New and Inoke Method**

```marmot
Person p = new Person("Tom", 18);
p -> sayHallo();

Teacher t = new Teacher();
t.name("Tony");
t.age(32);
t.school("ECUST");

t -> sayHallo();
```

**Copy Function**

```marmot
func sayHallo0 = func sayHallo[Teacher];

t -> sayHallo0();
```

**Lambda**

```marmot
func sayHallo1 = [Teacher]() -> {
    printl("I am {}, my age is {}, I am a teacher of {}", _.name, _.age, _.school);
}
```

**Name Space**

```marmot
namespace MarmotGroup {
    func addMember[Group](member: Member) {
        _.members -> add(member);
    }
}

Group g = new Group();
Member m = new Member();
g -> MarmotGroup::addMember(m);
```