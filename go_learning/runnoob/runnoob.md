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

# Go 语言数组
```go
var variable_name [SIZE] variable_type
// exemple
var balance [10] float32
// 编译器自行判断数组长度 [...]
var balance = [...]float32{1000.0, 2.0, 3.4, 7.0, 50.0}
```

# Go 语言指针
```go
var var_name *var-type
var ip *int        /* 指向整型*/
var fp *float32    /* 指向浮点型 */
```

# Go 语言结构体
```go
// 结构体定义
type struct_variable_type struct {
   member definition
   member definition
   ...
   member definition
}

// 结构体声明
variable_name := structure_variable_type {value1, value2...valuen}
// or
variable_name := structure_variable_type { key1: value1, key2: value2..., keyn: valuen}

// 访问结构体成员
var Book1 Books        /* 声明 Book1 为 Books 类型 */
/* book 1 描述 */
Book1.title = "Go 语言"
Book1.author = "www.runoob.com"
Book1.subject = "Go 语言教程"
Book1.book_id = 6495407
```

结构体指针访问成员同样用.

# Go 语言切片(Slice) - 动态数组
```go
var identifier []type
var slice1 []type = make([]type, len)
slice1 := make([]type, len)
// make([]T, length, capacity)
// 也可以指定容量，其中 capacity 为可选参数

// append()
numbers = append(numbers, 2,3,4)

// copy()
copy(numbers1,numbers)  // 拷贝 numbers 的内容到 numbers1
```

# Go 语言范围(Range)
Go 语言中 range 关键字用于 for 循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)的元素。

在数组和切片中它返回元素的索引和索引对应的值，在集合中返回 key-value 对。
```go
// for 循环的 range 格式可以对 slice、map、数组、字符串等进行迭代循环。
for key, value := range oldMap {
    newMap[key] = value
}
```

# Go 语言Map(集合)
Map 是一种**无序**的键值对的集合。

```go
/* 声明变量，默认 map 是 nil */
var map_variable map[key_data_type]value_data_type

/* 使用 make 函数 */
map_variable := make(map[key_data_type]value_data_type)

/*查看元素在集合中是否存在 */
capital, ok := countryCapitalMap [ "American" ] /*如果确定是真实的,则存在,否则不存在 */
/*fmt.Println(capital) */
/*fmt.Println(ok) */
if (ok) {
    fmt.Println("American 的首都是", capital)
} else {
    fmt.Println("American 的首都不存在")
}

/*删除元素*/ 
delete(countryCapitalMap, "France")
```

# Go 语言类型转换

```go
type_name(expression)
```

tips: Go 不支持隐式转换

# Go 语言接口
```go
// 抽象例子
/* 定义接口 */
type interface_name interface {
   method_name1 [return_type]
   method_name2 [return_type]
   method_name3 [return_type]
   ...
   method_namen [return_type]
}

/* 定义结构体 */
type struct_name struct {
   /* variables */
}

/* 实现接口方法 */
func (struct_name_variable struct_name) method_name1() [return_type] {
   /* 方法实现 */
}
// ...
func (struct_name_variable struct_name) method_namen() [return_type] {
   /* 方法实现*/
}
```

```go
// 具体例子
package main
import (
    "fmt"
)
// 定义接口 Phone
type Phone interface {
    call()
}
// 两种结构体及其方法
type NokiaPhone struct {
}
type IPhone struct {
}
func (nokiaPhone NokiaPhone) call() {
    fmt.Println("I am Nokia, I can call you!")
}
func (iPhone IPhone) call() {
    fmt.Println("I am iPhone, I can call you!")
}

func main() {
    // 声明了个接口
    var phone Phone
    // 给接口赋值
    phone = new(NokiaPhone)
    phone.call()

    phone = new(IPhone)
    phone.call()
}
```

# Go 错误处理
Go 语言通过内置的错误接口提供了非常简单的错误处理机制。
```go
// error 接口定义
type error interface {
    Error() string
}
```

```go
func Sqrt(f float64) (float64, error) {
    if f < 0 {
        return 0, errors.New("math: square root of negative number")
    }
    // 实现
}
```

```go
// 具体例子
package main
import (
    "fmt"
)

// 定义一个 DivideError 结构
type DivideError struct {
    dividee int
    divider int
}

// 实现 `error` 接口
func (de *DivideError) Error() string {
    strFormat := `
    Cannot proceed, the divider is zero.
    dividee: %d
    divider: 0
`
    return fmt.Sprintf(strFormat, de.dividee)
}

// 定义 `int` 类型除法运算的函数
func Divide(varDividee int, varDivider int) (result int, errorMsg string) {
    if varDivider == 0 {
            dData := DivideError{
                    dividee: varDividee,
                    divider: varDivider,
            }
            errorMsg = dData.Error()
            return
    } else {
            return varDividee / varDivider, ""
    }

}

func main() {

    // 正常情况
    if result, errorMsg := Divide(100, 10); errorMsg == "" {
            fmt.Println("100/10 = ", result)
    }
    // 当除数为零的时候会返回错误信息
    if _, errorMsg := Divide(100, 0); errorMsg != "" {
            fmt.Println("errorMsg is: ", errorMsg)
    }

}
```

# Go 并发
```go
go 函数名( 参数列表 )
```

## 通道（channel）
```go
// 声明通道
ch := make(chan int)
// 第二个参数可以指定缓冲区大小
ch := make(chan int, 100)
```

```go
// 具体例子
package main
import "fmt"

func sum(s []int, c chan int) {
        sum := 0
        for _, v := range s {
                sum += v
        }
        c <- sum // 把 sum 发送到通道 c
}

func main() {
        s := []int{7, 2, 8, -9, 4, 0}
        c := make(chan int)
        go sum(s[:len(s)/2], c)
        go sum(s[len(s)/2:], c)
        // 从通道 c 中接收
        x, y := <-c, <-c 
        fmt.Println(x, y, x+y)
}
```

## Go 遍历通道与关闭通道
```go
v, ok := <-ch   // besoin 没太搞懂

// 具体例子
package main
import (
        "fmt"
)
func fibonacci(n int, c chan int) {
        x, y := 0, 1
        for i := 0; i < n; i++ {
                c <- x
                x, y = y, x+y
        }
        close(c)
}
func main() {
        c := make(chan int, 10)
        go fibonacci(cap(c), c)
        // range 函数遍历每个从通道接收到的数据，因为 c 在发送完 10 个
        // 数据之后就关闭了通道，所以这里我们 range 函数在接收到 10 个数据
        // 之后就结束了。如果上面的 c 通道不关闭，那么 range 函数就不
        // 会结束，从而在接收第 11 个数据的时候就阻塞了。
        for i := range c {
                fmt.Println(i)
        }
}
```