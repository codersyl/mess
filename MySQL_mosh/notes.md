再看一次mosh的sql，这次笔记尽量记的详细一些。


每个数据库有
1. Tables 存储数据的地方
2. Views 视图，类似虚拟线缆。可以把不同图的表拖进view，对建报告很有帮助
3. Stored Procedures 存储过程、函数
4. Functions

课程介绍
* 增删改查
* 创建视图、存储过程、函数
* 触发器、事件、事务、并发
* 数据库设计
* 索引以提高效率
* 保护数据库

# SELECT子句详解
```sql
# code 1
USE sql_store; -- 选中需要使用的数据库
SELECT *
FROM customers
WHERE customer_id = 1
ORDER BY first_name
-- 双减号可以用来写注释

# code2
SELECT
last_name,
first_name,
points AS "POINTS HOHO", -- AS后跟别名，如果别名有空格，需要前后加引号
points * 10 + 100 AS money_they_obtain
FROM customers

# code3
SELECT DISTINCT state -- DISTINCT关键字，不出现重复的
FROM customers;
```


# WHERE子句详解
对所有句子进行遍历判断WHERE的条件

sql里
= 就是等于
<> 与 != 都是不等于
AND 是 并且
OR 是 或者
NOT 是 非
优先级 NOT > AND > OR

# 一些用在WHERE中的关键字
IN关键字
state = 1 OR state = 2 OR state = 3 等同于
state IN (1, 2, 3)

BETWEEN关键字
某个东西在值A与值B间（包括值A与B）
WHERE points >= 0 AND points <= 100
等同于
WHERE points BETWEEN 0 AND 100

LIKE关键字
WHERE name LIKE '%a%'; -- 这句也能搜到大写A，也可以使用 NOT LIKE 取补集
寻找name中有a的人
_代表一个字符，%代表任意多字符

REGEXP关键字
正则
WHERE name REGEXP 'a'; 等同于 WHERE name LIKE '%a%';
WHERE name REGEXP '^abc'; 表示name必须要abc开头
WHERE name REGEXP 'abc$'; 表示name必须要abc结尾
WHERE name REGEXP 'a|b'; 表示name必须要包含a或者b
WHERE name REGEXP '[abc]d'; 表示name必须要ad或bd或cd
WHERE name REGEXP '[a-m]n' 表示从a到m都行，！！！不包括m

IS NULL关键字
WHERE phone IS NULL
WHERE phone IS NOT NULL

# ORDER BY子句
如果不指定的话，则默认以主键排序
```sql
SELECT * , quantity * unit_price AS total_price
FROM order_items
WHERE order_id = 2
ORDER BY total_price; # 按照总价来排序
-- ORDER BY total_price DESC; # 按照总价来排序，但是是降序
```

# LIMIT 关键字
总是写在结尾
```sql
SELECT *
FROM customers
LIMIT 3; # 只显示三条
# LIMIT 6, 3; # 只显示三条，且前6条不显示，相当于偏移量为6
```

# INNER JOIN
```sql
# 以下代码意思是，用orders与customers联表，其中用customer_id来作为共同表项的依据
SELECT order_id, o.customer_id, first_name, last_name
FROM	orders o # 这里意思是用o来指代orders这个表，之后可以用o来当前缀
JOIN customers c
	ON o.customer_id = c.customer_id;
``` 