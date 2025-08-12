- ## ✅ 一句话回答：

  > 在 C++ 中，**推荐使用 `nullptr` 而不要用 `NULL`**，因为 `nullptr` 是一个**真正的空指针类型**，而 `NULL` 只是一个整数（`0`），会导致类型歧义和调用错误。

  ------

  ## 🔍 一、`NULL` 的本质是什么？

  ```c++
  #ifndef NULL
  	#ifdef __cplusplus
  		#define NULL 0
  	#else
  		#define NULL ((void *)0)
  	#endif
  #endif
  ```
  
  - 在C++ 中，`NULL` 就是整数 `0` 的别名；
  - 它并不具有“指针类型”，**只是一个 `int` 字面值**。
  - C++不支持把 void*的指针类型隐式的转换成其他的指针类型
  
  这会带来严重的问题：**类型不明确**！
  
  ------
  
  ## ❌ 问题示例：重载歧义
  
  假设你有以下重载函数：

  ```c++
  void func(int);
  void func(char*);
  
  func(NULL);   // ⛔️ 错误：int 还是指针？
  ```
  
  此时 `NULL` 是 `0`，类型是 `int`，编译器优先调用 `func(int)`，而不是你可能想要的 `func(char*)`！
  
  ------
  
  ## ✅ `nullptr` 的优势（C++11 起）

  ```c++
  void func(int);
  void func(char*);
  
  func(nullptr);   // ✅ 明确是“空指针”，调用 func(char*)
  ```
  
  ### 🔹 原因：
  
  - `nullptr` 的类型是一个新类型：`std::nullptr_t`
  - 它可以**隐式转换为任意指针类型**，但**不会和 `int` 混淆**
  - 更安全、更明确、更现代！
  
  ```c++
  std::nullptr_t np = nullptr;   // 合法
  int* p = nullptr;              // 合法
  int x = nullptr;               // ❌ 错误！不能转为 int
  ```
  
  ------
  
  ## 🧠 举个真实的“坑”
  
  ```c++
  void print(int val)   { std::cout << "int\n"; }
  void print(void* ptr) { std::cout << "pointer\n"; }
  
  print(NULL);      // 输出：int （⛔️ 很可能不是你想要的）
  print(nullptr);   // 输出：pointer ✅
  ```
  
  
  
  ------
  
  ## ✅ 总结对比表格
  
  | 比较项     | `NULL`               | `nullptr`        |
  | ---------- | -------------------- | ---------------- |
  | 定义       | 宏，等于 0           | 关键字           |
  | 类型       | `int`                | `std::nullptr_t` |
  | 可转换     | 转为整数或指针       | 只能转为指针     |
  | 安全性     | ⛔️ 不安全（重载歧义） | ✅ 安全           |
  | C 支持     | ✅                    | ❌（C 不支持）    |
  | C++11 引入 | ❌                    | ✅                |
