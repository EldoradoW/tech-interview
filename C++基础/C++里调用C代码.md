## ✅ 一、总流程总结（核心）

| 步骤 | 操作                                       |
| ---- | ------------------------------------------ |
| ①    | 保留 `.c` 文件不变，用 `gcc` 编译生成 `.o` |
| ②    | 用 `extern "C"` 包装 C 的头文件            |
| ③    | 在 C++ 中 `#include` C 的头文件            |
| ④    | 用 `g++` 链接 `.cpp` 和 `.o` 文件          |



------

## 🧱 二、示例讲解

### 🔧 文件结构

```
project/
├── c_code.c
├── c_code.h
├── main.cpp
```

------

### 1. C 源码：`c_code.c`

```cpp
#include <stdio.h>

void c_say_hello(const char* name) {
    printf("Hello from C, %s!\n", name);
}
```

------

### 2. C 的头文件：`c_code.h`

```cpp
#ifndef C_CODE_H
#define C_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

void c_say_hello(const char* name);  // 函数声明

#ifdef __cplusplus
}
#endif

#endif
```

> ⚠️ 重点：`extern "C"` 用于告诉 C++ **不要对函数名做 name mangling**，以便链接器能找到正确的 C 函数符号。

------

### 3. C++ 主程序：`main.cpp`

```cpp
#include "c_code.h"  // ✅ 正确引入

int main() {
    c_say_hello("world");  // 调用 C 函数
    return 0;
}
```

------

### 4. 编译方式

```cpp
gcc -c c_code.c -o c_code.o       # 编译 C 文件
g++ main.cpp c_code.o -o app      # 编译链接 C++ 主程序和 C 库
```

> ⚠️ 千万别用 `g++` 编译 `.c` 文件，不然会当成 C++ 编译，出错！

------

## 📌 三、你需要做的最小操作（归纳）

| 内容                 | 是否必须 | 说明                         |
| -------------------- | -------- | ---------------------------- |
| 使用 `extern "C"`    | ✅        | 防止函数名重整，确保链接成功 |
| `.c` 用 `gcc` 编译   | ✅        | 防止误用 C++ 编译规则        |
| `.cpp` 用 `g++` 编译 | ✅        | 支持 C++ 语法                |
| 使用头文件           | ✅        | C++ 需要正确声明函数原型     |



------

## 🚫 四、错误示例（会出错）

### ❌ 忘了 `extern "C"`，C++ 编译器找不到符号：

```
main.cpp: undefined reference to `c_say_hello'
```

------

## ✅ 五、实际应用中这样场景很常见

| 场景                         | C 函数使用示例                 |
| ---------------------------- | ------------------------------ |
| 调用 C 标准库（如 `math.h`） | `sqrt`, `strlen` 等            |
| 使用 C 编写的外部库          | `libpng`, `libcurl`, `sqlite3` |
| 嵌入系统中使用 C HAL         | STM32、ESP32 中常见            |
| 在 LLVM/Clang 插件开发中     | C 接口导出的 `libclang`        |



------

## ✅ 总结

| 项目                | 操作说明                   |
| ------------------- | -------------------------- |
| 是否能用 C 函数     | ✅ 可以                     |
| 是否需要 extern "C" | ✅ 必须用于头文件           |
| 编译顺序            | `.c` 用 gcc, `.cpp` 用 g++ |
| 链接顺序            | g++ 编译时链接 `.o` 文件   |
