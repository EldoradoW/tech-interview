# 联合体和直接转换指针的类型双关

# 无法用于编译期

这段代码利用了 `union` 来做所谓的“位模式重解释”（type-punning）：

```c
constexpr float type_pun(int i) {
    union U {
        int   i;
        float f;
    } u{i};       // 用 i 来初始化联合体的 i 成员
    return u.f;   // 然后读取同一内存区域里的 f 成员
}
// 变量p必须也要声明成constexpr，否则编译器会优化掉，不会在编译期计算
// 下面代码会报错
int main(int argc, char **argv) {
    constexpr float f = type_pun(0);
    std::cout << f << std::endl;
    return 0;
}
```

------

### 1. 它在做什么？

1. **定义了一个匿名联合** `U`，有两个成员：`int i;` 和 `float f;`，它们共享同一块内存。
2. `u{i}` 是**聚合初始化**，把传入的 `int i` 存到了 `u.i` 上。
3. `return u.f;` 则把同一块内存按 `float` 来解读，返回一个 `float`，其位模式就是你原来传入的那个整数的二进制表示。

------

### 2. 为什么想这么写？

- 用它来“快读”把一个 `int` 的 32 位位模式当成 `float` 来看，而不是进行数值转换（`static_cast<float>(i)` 会按数学意义把整数转成浮点数，而这里要的只是内存位模式重用）。

------

### 3. 为什么在 C++ 中它是 **未定义行为**，也不能当成 `constexpr` 用？

- **严格别名规则**：C++ 标准不允许你通过一个类型的指针/引用去访问另一种不相关类型的对象（这里 `int` ↔ `float`），这是“违背严格别名规则”，属于未定义行为。
- **联合体成员访问**：即使写成 `union`，标准也只保证“读取最后一次写入的成员”是定义良好的。写了 `i` 成员后读 `f` 成员，仍然是未定义。
- **`constexpr` 限制**：要成为常量表达式，所有操作都必须是受限的、定义良好的。访问一个“非活动成员”（inactive member）的位模式重解释不在允许之列，编译器会拒绝把它当作 constexpr 求值。

------

### 4. 正确安全的编译期位模式重解释：`std::bit_cast`

从 **C++20** 起，标准提供了 `std::bit_cast`，它既 **安全**、**定义良好**，又是 `constexpr`：

```c
#include <bit>
#include <cstdint>

constexpr float type_pun(int i) {
    return std::bit_cast<float>(i);
}

int main(int argc, char **argv) {
    constexpr float f = type_pun(0);
    std::cout << f << std::endl;
    return 0;
}
```

- `std::bit_cast<T>(u)` 要求源类型和目标类型都是 **TriviallyCopyable**，并且大小相同。
- 它在编译期就能工作（如果你把它用在 `constexpr` 上下文里），**没有 UB**。

------

## 小结

| 方式                          | 是否 UB?       | 是否 constexpr?    |
| ----------------------------- | -------------- | ------------------ |
| `union` type-punning          | ✅ 未定义行为   | ❌ 不能 constexpr   |
| `(float&)i` 强转              | ✅ 未定义行为   | ❌                  |
| **`std::bit_cast<float>(i)`** | **✅ 定义良好** | **✅ 可 constexpr** |



因此，如果你需要在编译期“把 `int` 的位模式当 `float` 看”，推荐使用 `std::bit_cast` 而 **不要** 用 `union` 或指针强转。

