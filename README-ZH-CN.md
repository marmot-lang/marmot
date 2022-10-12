# Marmot 编程语言

Marmot 编程语言旨在于实现数据和函数分离的编程范式，具有无GC、简单的内存结构、无生命周期的特点。Marmot 的目标不是为了代替任何编程语言，像 C 或者 C++。Marmot 不像 Rust 能够保证编译期的内存安全，需要使用者手动释放申请的内存。

与其他编程语言比较：

**C 语言**

- Marmot 支持泛型
- Marmot 提供更多的数据结构，像链表、哈希表等
- Marmot 支持结构体继承
- Marmot 提供包管理工具

**C++ 语言**

- Marmot 不支持面向对象
- Marmot 具有更简单的内存结构
- Marmot 提供统一的包管理工具
- Marmot 具有更好的模块实现

**Rust 语言**

- Marmot 不支持编译期内存检查
- Marmot 需要手动释放内存
- Marmot 更容易学习

## Marmot 语法

### 类型系统

#### 整型

- `int8`: 8 位有符号整型
- `int16`: 16 位有符号整型
- `int32`: 32 位有符号整型
- `int64`: 64 位有符号整型
- `int128`: 128 位有符号整型
- `u_int8`: 8 位无符号整型
- `u_int16`: 16 位无符号整型
- `u_int32`: 32 位无符号整型
- `u_int64`: 64 位无符号整型
- `u_int128`: 128 位无符号整型

#### 浮点类型

- `float`: 32 位浮点类型
- `double`: 64 位浮点类型

#### 布尔类型

- `bool`: 值为 `true` 和 `false`

#### Byte 类型

- `byte`: 8 位

#### 字符类型

- `char`: 一个字符

#### 引用类型

- `List`: 是结构体 `struct List {}` 的一个引用类型

### 字面量

- 十进制：例如：`39`，`94`
- 八进制：由 `0` 开头，例如：`032`, `064`
- 二进制：由 `0b` 开头，例如：`0b1010`
- 十六进制：由 `0x` 开头, 例如：`0xff`
- 字符串：例如：`"hello world"`

### 运算符

- 算数运算：加 `+`，减 `-`，乘 `*`，除 `/`
- 移位运算：左移 `<<`，右移 `>>`
- 类型判断：`instanceof`

### 条件判断

**if 条件判断**

```marmot
if(a > b) {
    // ...
} else if (a > c) {
    // ...
} else {
    // ...
}
```

### 循环语句

**for 循环**

```marmot
for (int i = 0; i < 20; i ++) {
    // ...
    continue; // or break;
}
```


**while 循环**

```marmot
while(true) {
    // ...
    continue; // or break;
}
```

### match 语句

由于 Marmot 并不直接提供 `null` 判断，所以引用的非空判断需要使用 `match` 语句。

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

其中，`val` 只是变量名，可以是任何名称，例如：`carVal` 等。

### 结构体

结构体类型是一种用来组织数据的类型，结构体的所有属性都是公有属性，如下：

```marmot
struct Node {
    Node prev;
    Node next;
    u_int32 val;
}
```

**泛型**

结构体可以通过泛型来定义一类结构体，如下：

```marmot
struct Node<V> {
    Node<V> prev;
    Node<V> next;
    V val;
}
```

**继承**

结构体可以继承父结构体的属性，结构体支持多继承, 即一个结构体可以有多个父结构体，如下：

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

结构体 `C` 等同于如下的定义：

```marmot
struct C {
    u_int32 a;
    u_int32 b;
    u_int32 c;
}
```

泛型结构体的继承，如下：

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

结构体 `C` 等同于如下的定义：

```marmot
struct C<V> {
    V a;
    u_int32 b;
    u_int32 c1;
    V c2;
}
```

**创建**

创建结构体会申请内存空间，并返回一个结构体的引用，如下：

```marmot
Car car = new Car();
```

创建泛型结构体：

```marmot
Map<u_int32, u_int32> map = new Map<>();
```

**设置属性值**

```marmot
Car car = new Car();
car.weight(32);
```

**获取属性值**

```marmot
Car car = new Car();
u_int32 weight = car.weight();
```

### 函数

函数是执行代码的最小单元，函数由关键字 `func` 定义，如下：

```marmot
func insert[Map<K, V>](K key, V value) : V {
    V oldVal;
    // ... do map insert
    u_int32 size = _.size;

    ret oldVal;
}
```

其中，`insert` 是函数名，`Map<K, V>` 是函数的调用点，`key` 和 `value` 是函数的参数名，`:` 后的 `V` 是函数的返回类型，返回值由 `ret` 返回。

调用点：是一个结构体类型，函数体内可以通过 `_` 符号访问该结构体的属性，像 `_.size` 访问的就是 `Map<K, V>` 结构体的 `size` 属性。

**无返回值**

```marmot
func eat[Animal]() : void {

}
```

或者：

```marmot
func eat[Animal]() {

}
```

**通用函数**

通用函数即不指明调用点的函数，通用函数可以由所有的结构体调用，如下：

```marmot
func do() {

}
```

或者：

```marmot
func do[]() {

}
```

**Main 函数**

Main 函数是程序的入口函数，是一个通用函数，如下：

```marmot
func main[](u_int32 argc, String[] argv) : u_int32 {
    ret 0;
}
```

**函数调用**

结构体可以通过 `->` 调用调用点是自己或者父类的函数和通用函数。

如下：

```marmot
func main[](u_int32 argc, String[] argv) : u_int32 {
    Map<u_int32, u_int32> map = new Map<>();
    map -> insert(8. 64);
    ret 0;
}
```

**Lambda 表达式**

```marmot
func sayHallo = [Teacher]() -> {
    printl("I am {}, my age is {}, I am a teacher of {}", _.name, _.age, _.school);
}
```

```marmot
func sayHallo0 = func sayHallo[Teacher];
```

**命名空间**

```marmot
namespace MarmotGroup;
```



