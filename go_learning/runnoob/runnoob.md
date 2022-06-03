# 来源

[菜鸟教程](https://www.runoob.com/go/go-tutorial.html)

# Hello world
```go
// 非注释的第一行指明本文件属于哪个包
package main

// 表明编译需要使用 fmt 包
import "fmt"

func main() {
   /* 这是我的第一个简单的程序 */
   fmt.Println("Hello, World!")
}
```

# 执行Go程序
```
go run hello.go

go build hello.go 
./hello
```

tips: { 不能单独成行

# Go 语言基础语法
## Go标记
* 行分隔符
* 注释
* 标识符
   * 用来命名变量、类型
   * 由大小写字母、数字、下划线组成
   * 第一个字符不能是数字
* 字符串连接 使用 +
* 关键字

# Go语言数据类型
## 一些类型
* 布尔型
* 数字类型 int float32 float64
* 字符串 由字节连接而成，Go采用UTF-8 的Unicode
* 派生类型
   * 指针类型（Pointer）
   * 数组类型
   * 结构化类型(struct)
   * Channel 类型
   * 函数类型
   * 切片类型
   * 接口类型（interface）
   * Map 类型

## 数字类型
整型
* uint8
* uint16
* uint32
* uint64
* int8
* int16
* int32
* int64

浮点型
* float32
* float64
* complex64
* complex128

其他数字类型
* byte 类似uint8
* rune 类似uint32
* uint 32 or 64 bit
* int 与uint一样大小
* uintptr 无符号整型，用于存放一个指针

# Go 语言变量
```go
var identifier type

var identifier1, identifier2 type

var x, y int
var (  // 这种因式分解关键字的写法一般用于声明全局变量
    a int
    b bool
)

var c, d int = 1, 2
var e, f = 123, "hello"

//这种不带声明格式的只能在函数体中出现
//g, h := 123, "hello"
func main(){
    g, h := 123, "hello"
    println(x, y, a, b, c, d, e, f, g, h)
}
```

值类型与引用类型

# Go 语言常量
常量只能是布尔型、数字型或者字符串型
```go
package main

import "fmt"

func main() {
   const LENGTH int = 10
   const WIDTH int = 5  
   var area int
   const a, b, c = 1, false, "str" //多重赋值

   area = LENGTH * WIDTH
   fmt.Printf("面积为 : %d", area)
   println()
   println(a, b, c)  
}
```

用作枚举类型
```go
const (
    Unknown = 0
    Female = 1
    Male = 2
)
```

iota，特殊常量，可以理解为常量的行索引

# Go 语言运算符
* 算术运算符
* 关系运算符
* 逻辑运算符
* 位运算符
* 赋值运算符
* 其他运算符

## 算术运算符
\+ - * / % ++ --

## 关系运算符
* ==
* !=
* >
* <
* >=
* <=

## 逻辑运算符
&& \|\| !

## 位运算符
& \| ^ << >>

## 赋值运算符
各种=

## 其他运算符
* & 取地址
* * 指针变量

## 运算符优先级

# Go 语言条件语句
## if 与cpp类似，但是条件不用小括号()括起来

## switch 也类似，但也不用()，且每个case都不用break，但若加fallthrough会强制执行下一条case且不用判断
```go
package main
import "fmt"
func main() {
    switch {
    case false:
            fmt.Println("1、case 条件语句为 false")
            fallthrough
    case true:
            fmt.Println("2、case 条件语句为 true")
            fallthrough
    case false:
            fmt.Println("3、case 条件语句为 false")
            fallthrough
    case true:
            fmt.Println("4、case 条件语句为 true")
    case false:
            fmt.Println("5、case 条件语句为 false")
            fallthrough
    default:
            fmt.Println("6、默认 case")
    }
}
// 运行结果
// 2、case 条件语句为 true
// 3、case 条件语句为 false
// 4、case 条件语句为 true
```

## select
```go
select {
    case communication clause  :
       statement(s);      
    case communication clause  :
       statement(s);
    /* 你可以定义任意数量的 case */
    default : /* 可选 */
       statement(s);
}
```
* 每个 case 都必须是一个通信
* 所有 channel 表达式都会被求值
* 所有被发送的表达式都会被求值
* 如果任意某个通信可以进行，它就执行，其他被忽略。
* 如果有多个 case 都可以运行，Select * 会随机公平地选出一个执行。其他不会执行。
* 否则：
   * 如果有 default 子句，则执行该语句。
   * 如果没有 default 子句，select 将阻塞，直到某个通信可以运行；Go 不会重新对 channel 或值进行求值。

! Go没有 ( ? : ) 这个三目运算符

# Go 语言循环语句
## for
```go
// 3种基础款
for init; condition; post { }
for condition { }
for { } // 无限循环

// for -range
for key, value := range oldMap {
    newMap[key] = value
}

// for -each range
numbers := [6]int{1, 2, 3, 5}
for i,x:= range numbers {
       fmt.Printf("第 %d 位 x 的值 = %d\n", i,x)
}
```

break
```go
fmt.Println("---- break label ----")
re:
   for i := 1; i <= 3; i++ {
      fmt.Printf("i: %d\n", i)
      for i2 := 11; i2 <= 13; i2++ {
      fmt.Printf("i2: %d\n", i2)
      break re
   }
}
```

continue 也可以像break一样配合label使用

goto 同 cpp中一样不建议使用

# Go 语言函数
```go
func function_name( [parameter list] ) [return_types] {
   函数体
}

// exemple
/* 函数返回两个数的最大值 */
func max(num1, num2 int) int {
   /* 声明局部变量 */
   var result int

   if (num1 > num2) {
      result = num1
   } else {
      result = num2
   }
   return result
}
```

函数参数的两种传递方式：
1. 值传递
2. 引用传递

闭包，有点神奇：
```go
package main

import "fmt"

func getSequence() func() int {
   i:=0
   return func() int {
      i+=1
     return i  
   }
}

func main(){
   /* nextNumber 为一个函数，函数 i 为 0 */
   nextNumber := getSequence()  

   /* 调用 nextNumber 函数，i 变量自增 1 并返回 */
   fmt.Println(nextNumber())
   fmt.Println(nextNumber())
   fmt.Println(nextNumber())
   
   /* 创建新的函数 nextNumber1，并查看结果 */
   nextNumber1 := getSequence()  
   fmt.Println(nextNumber1())
   fmt.Println(nextNumber1())
}
```

Go语言函数方法
```go
package main
import (
   "fmt"  
)
/* 定义结构体 */
type Circle struct {
  radius float64
}

func main() {
  var c1 Circle
  c1.radius = 10.00
  fmt.Println("圆的面积 = ", c1.getArea())
}

// 该 method 属于 Circle 类型对象中的方法
func (c Circle) getArea() float64 {
  //c.radius 即为 Circle 类型对象中的属性
  return 3.14 * c.radius * c.radius
}
```

# Go 语言变量作用域
* 全局变量
* 局部变量
* 形式参数