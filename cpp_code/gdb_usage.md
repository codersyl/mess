查看版本
```
gdb -v
```

调试某个文件
```
gdb filename
```

对被调试的文件有要求：
* g++ 或者 gcc编译的话需要加 -g 选项，也可以 -Og
* 如果是cmake 可以
	* 使用命令`cmake -DCMAKE_BUILD_TYPE=Debug .. && make`
	* 或者在CMakeLists.txt中加`SET(CMAKE_BUILD_TYPE "Debug”)` 或者 `SET(CMAKE_BUILD_TYPE "Release")`

# 一些基础的命令
(gdb) break xxx 
(gdb) b xxx	
在源代码指定的某一行设置断点，其中 xxx 用于指定具体打断点的位置。


(gdb) run 
(gdb) r	
执行被调试的程序，其会自动在第一个断点处暂停执行。


(gdb) continue 
(gdb) c	
当程序在某一断点处停止运行后，使用该指令可以继续执行，直至遇到下一个断点或者程序结束。


(gdb) next 
(gdb) n	
令程序一行代码一行代码的执行。


(gdb) print xxx 
(gdb) p xxx	
打印指定变量的值，其中 xxx 指的就是某一变量名。


(gdb) list 
(gdb) l	
显示源程序代码的内容，包括各行代码所在的行号。


(gdb) quit 
(gdb) q	
终止调试。