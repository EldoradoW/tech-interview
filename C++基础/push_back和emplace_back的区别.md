`push_back` 和 `emplace_back` 是 C++ 中 `std::vector` 等容器提供的成员函数，用于向容器尾部添加元素。**它们的区别在于是否发生临时对象构造与拷贝/移动。**

------

## ✅ 一句话区别：

| 函数名              | 做法                            |
| ------------------- | ------------------------------- |
| `push_back(x)`      | **先构造对象，再拷贝/移动进去** |
| `emplace_back(...)` | **直接在容器内原地构造对象**    |



------

## ✅ 示例：类构造函数观察

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct A {
  A(int x, int y) { cout << "构造 A(" << x << "," << y << ")\n"; }
  A(const A&)     { cout << "拷贝构造\n"; }
  A(A&&) noexcept { cout << "移动构造\n"; }
};

int main() {
  vector<A> v;

  cout << "--- push_back ---\n";
  A a(1, 2);
  v.push_back(a);  // 拷贝构造
  v.push_back(A(3, 4)); // 临时对象 + 移动构造

  cout << "--- emplace_back ---\n";
  v.emplace_back(5, 6);  // 直接在 vector 内构造，无拷贝/移动
}
```

### 输出：

```
--- push_back ---
构造 A(1,2)
拷贝构造
构造 A(3,4)
移动构造
--- emplace_back ---
构造 A(5,6)
```

------

## ✅ 功能总结对比

| 功能/特性             | `push_back`          | `emplace_back`                      |
| --------------------- | -------------------- | ----------------------------------- |
| 参数类型              | 需要传入对象         | 可以传入构造函数的参数              |
| 是否调用构造          | ❌ 不能直接构造       | ✅ 原地构造                          |
| 是否调用拷贝/移动构造 | 可能调用一次或两次   | 理论上**零**次（如无 reallocation） |
| 性能                  | 略慢（涉及临时对象） | 更快（尤其在复杂类型上）            |
| 可读性                | 更直接、简洁         | 有时写法更灵活（特别是结构体构造）  |



------

## ✅ 举个结构体场景差异：

```cpp
struct Person {
  string name;
  int age;
  Person(string n, int a): name(n), age(a) {}
};

vector<Person> v;

v.push_back(Person("Tom", 18));      // 创建临时对象 -> 移动到 vector
v.emplace_back("Alice", 20);         // 直接构造在 vector 内部，无中间对象
```

------

## ✅ 总结

| 建议                                                         |
| ------------------------------------------------------------ |
| ✅ 对于性能敏感或大对象，**推荐使用 `emplace_back`**          |
| ✅ 对已有对象（变量）使用 `push_back(obj)` 合理               |
| ❌ 不建议滥用 `emplace_back` 创建临时对象（效果反而和 `push_back` 类似） |
