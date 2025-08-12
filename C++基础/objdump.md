`objdump` 并不是 GCC 的选项，而是一个 **GNU Binutils 工具**，常与 GCC 一起使用，专门用于查看编译生成的二进制文件（如 `.o`, `.out`, `.elf` 等）的内容。

------

## 🛠️ 一、什么是 `objdump`？

`objdump` 是一个强大的二进制分析工具，能让你从可执行文件中反汇编、查看节（section）、符号表、机器码等信息。

它的作用类似于：

> 🧐 **把看不懂的机器文件，翻译成汇编、人能读的结构信息**

------

## 📚 二、常用命令与选项

| 命令                        | 说明                                      |
| --------------------------- | ----------------------------------------- |
| `objdump -d a.out`          | **反汇编代码段（.text）**                 |
| `objdump -S a.out`          | 汇编中**带有 C 源码**（需要带 `-g` 编译） |
| `objdump -t a.out`          | 查看**符号表**（函数/变量等）             |
| `objdump -x a.out`          | 显示所有头部信息（节头、符号、入口点等）  |
| `objdump -h a.out`          | 显示**节段信息**（section header）        |
| `objdump -s a.out`          | 查看**原始十六进制数据**                  |
| `objdump -D -M intel a.out` | 反汇编为 Intel 风格汇编（默认是 AT&T）    |



------

## 🧪 三、示例：反汇编可执行文件

```
gcc -g hello.c -o hello
objdump -d hello
```

输出（只显示 `.text` 段汇编）：

```
080483f4 <main>:
 80483f4: 55                    push   %ebp
 80483f5: 89 e5                 mov    %esp,%ebp
 80483f7: 83 ec 08              sub    $0x8,%esp
```

------

## 🎯 四、查看符号表

```
objdump -t hello
```

输出：

```
0000000000001139 g     F .text  0000000000000006              _Z3addii
0000000000001170 g     F .text  000000000000002a              main
```

这会显示函数名、地址、所属段（如 `.text`）、大小、链接属性等。

------

## 🧠 五、查看带源码的汇编（调试辅助）

```
gcc -g test.c -o test
objdump -S test
```

输出类似：

```
int main() {
 80483f4: 55                    push   %ebp
 80483f5: 89 e5                 mov    %esp,%ebp
```

如果有调试信息，会直接显示 C 源码对应的汇编。

------

## ✅ 六、objdump vs other tools

| 工具      | 功能                            |
| --------- | ------------------------------- |
| `objdump` | 全能的二进制结构和汇编查看      |
| `readelf` | 查看 ELF 文件结构（节头、符号） |
| `nm`      | 查看符号表（更简洁）            |
| `strings` | 提取可读字符串                  |
| `gdb`     | 运行时调试工具                  |



------

## 七、常用组合推荐

```
# 编译带符号信息
gcc -g test.c -o test

# 反汇编 + 源码
objdump -S test

# 用 Intel 汇编风格反汇编
objdump -d -M intel test

# 查看节区信息
objdump -h test
```

------

## ✅ 总结

| 你想做的事                 | 推荐命令           |
| -------------------------- | ------------------ |
| 看汇编代码                 | `objdump -d a.out` |
| 看 C 源码 + 汇编           | `objdump -S a.out` |
| 看符号表（函数/变量）      | `objdump -t a.out` |
| 看程序节（.text, .data等） | `objdump -h a.out` |
| 看原始二进制/十六进制内容  | `objdump -s a.out` |
