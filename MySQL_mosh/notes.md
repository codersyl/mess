再看一次mosh的sql，这次笔记尽量记的详细一些。

# 第一章 介绍
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

# 第二章 一些基础语句
## SELECT子句详解
```sql
## code 1
USE sql_store; -- 选中需要使用的数据库
SELECT *
FROM customers
WHERE customer_id = 1
ORDER BY first_name
-- 双减号可以用来写注释

## code2
SELECT
last_name,
first_name,
points AS "POINTS HOHO", -- AS后跟别名，如果别名有空格，需要前后加引号
points * 10 + 100 AS money_they_obtain
FROM customers

## code3
SELECT DISTINCT state -- DISTINCT关键字，不出现重复的
FROM customers;
```


## WHERE子句详解
对所有句子进行遍历判断WHERE的条件

sql里
= 就是等于
<> 与 != 都是不等于
AND 是 并且
OR 是 或者
NOT 是 非
优先级 NOT > AND > OR

## 一些用在WHERE中的关键字
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
\_代表一个字符，%代表任意多字符

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

## ORDER BY子句
如果不指定的话，则默认以主键排序
```sql
SELECT * , quantity * unit_price AS total_price
FROM order_items
WHERE order_id = 2
ORDER BY total_price; ## 按照总价来排序
-- ORDER BY total_price DESC; ## 按照总价来排序，但是是降序
```

## LIMIT 关键字
总是写在结尾
```sql
SELECT *
FROM customers
LIMIT 3; ## 只显示三条
## LIMIT 6, 3; ## 只显示三条，且前6条不显示，相当于偏移量为6
```

# 第三章 各种连接
## INNER JOIN
```sql
## 以下代码意思是，用orders与customers联表，其中用customer_id来作为共同表项的依据
SELECT order_id, o.customer_id, first_name, last_name
FROM	orders o ## 这里意思是用o来指代orders这个表，且之后必须用o来当前缀
JOIN customers c ## 也可以用 INNER JOIN
	ON o.customer_id = c.customer_id;
``` 


## 跨数据库连接
```sql
SELECT *
FROM	order_items oi
JOIN sql_inventory.products p ## 加前缀示意这张表来自其他数据库
	ON oi.product_id = p.product_id;
``` 

## 自连接
```sql
SELECT e.*, m.first_name as superior
FROM employees e
JOIN employees m ## 使用同一张表，但用不同的别名
	ON e.reports_to = m.employee_id;
```

## 多表连接
```sql
SELECT o.order_id,
				o.order_date,
                c.first_name,
                c.last_name,
                os.name AS status
FROM orders o
JOIN customers c
	ON o.customer_id = c.customer_id
JOIN order_statuses os
	ON o.status = os.order_status_id;
```

## 复合条件连接
复合主键：多于一列数据作为主键，
```sql
SELECT *
FROM order_items oi
JOIN order_item_notes oin
	ON oi.order_id = oin.order_id 
    AND oi.product_id = oin.product_id;
```

## 隐式连接语法
```sql
-- SELECT *
-- FROM	orders o
-- JOIN customers c
-- 	ON o.customer_id = c.customer_id; 

## 隐式连接语法，建议不用
SELECT *
FROM orders o, customers c
WHERE o.customer_id = c.customer_id
```

## 外连接
LEFT JOIN会返回第一张表的所有表项，不管它是否满足条件
RIGHT JOIN会返回第二张表的所有表项，不管它是否满足条件
```sql
SELECT c.customer_id, c.first_name, o.order_id
FROM customers c
LEFT JOIN orders orders ## 还有 RIGHT JOIN
	ON o.customer_id = c.customer_id
ORDER BY c.customer_id;
```

## 多表外连接
```sql
USE sql_store;

SELECT c.customer_id,
				c.first_name,
                o.order_id,
                s.name AS shipper
FROM customers c
LEFT JOIN orders o
	ON c.customer_id = o.customer_id
LEFT JOIN shippers s
	ON o.shipper_id = s.shipper_id;
```

## 自外连接
```sql
USE sql_hr;

SELECT e.employee_id,
				e.first_name,
                e.last_name,
                m.first_name AS his_manager
FROM employees e
LEFT JOIN employees m
	ON e.reports_to = m.employee_id;
```

## USING 语句
```sql
USE sql_store;

SELECT
	o.order_id,
    c.first_name,
    sh.name AS shipper
FROM orders o
JOIN customers c
	-- ON o.customer_id = c.customer_id
    USING (customer_id)
LEFT JOIN shippers sh
	USING (shipper_id);
## 双主键也可以使用USING
SELECT *
FROM order_items oi
JOIN order_item_notes oin
	## ON oi.order_id = oin.order_id AND
		## oi.product_id = oin.product_id
	USING (order_id, product_id);
```

## 自然连接
不建议使用，因为有时候会产生意想不到的结果
```sql
USE sql_store;
SELECT 
	o.order_id,
    c.first_name
FROM orders o
NATURAL JOIN customers c;
```

## 交叉连接
表A有m条记录，表B有n条记录
使用交叉连接后可以得到一张m * n大小的表，笛卡尔积
```sql
USE sql_store;
SELECT 
    c.first_name AS customer,
    p.name AS product
FROM customers c
CROSS JOIN products p
ORDER BY customer;
```
此例子无意义，一个有意义的例子，衣服的所有尺寸 * 所有颜色的组合

## 联合
两张表的列的数量应该一致，否则会出错
```sql
USE sql_store;
SELECT 
	order_id,
    order_date,
    'Active' AS status
FROM orders
WHERE order_date >= '2019-01-01'

UNION

SELECT 
	order_id,
    order_date,
    'Archived' AS status
FROM orders
WHERE order_date < '2019-01-01';
```

# 第四章 增删改

## 插入单行
```sql
USE sql_store;
INSERT INTO customers (
	first_name,
    last_name,
    birth_date,
    address,
    city,
    state)	# 这个括号以及里面的东西可以不写，但若不写，则要在一些地方补充DEFAULT或者NULL
VALUES (
    'John',
    'Smith',
    '1990-01-01',
    'address',
    'city',
    'CA');
```

## 插入多行
```sql
USE sql_store;
INSERT INTO shippers (name)
VALUES ('Shipper1'),
	('Shipper2'),
	('Shipper2');
```

## 插入分层行
要点：LAST_INSERT_ID() 为上一次增加的记录的主键
```sql
USE sql_store;
INSERT INTO orders (customer_id, order_date, status)
VALUES (1, '2019-01-02', 1);

INSERT INTO order_items 
VALUES (LAST_INSERT_ID(), 1, 1, 2.95),
	(LAST_INSERT_ID(), 2, 1, 3.95);
```

## 创建表复制
```sql
# 把表orders中的所有表项复制到新表orders_archived中去
# 新表没有主键，也不会自增
CREATE TABLE orders_archived AS
SELECT * FROM orders;

# 把表orders中的一部分复合条件的表项复制到表orders_archived中去
INSERT INTO orders_archived
SELECT *
FROM orders
WHERE order_date < '2019-01-01';
```

## 更新单行
```sql
USE sql_invoicing;
UPDATE invoices
SET payment_total = 10,
	payment_date = '2019-03-01'
WHERE invoice_id = 1;
```

## 更新多行
```sql
USE sql_invoicing;
UPDATE invoices
SET
	payment_total = invoice_total * 0.1, 
    payment_date = due_date
WHERE client_id IN (3, 4);
```

## 在update中使用子查询
```sql
USE sql_invoicing;
UPDATE invoices
SET
	payment_total = invoice_total * 0.1, 
    payment_date = due_date
WHERE client_id = 
	(SELECT client_id
	FROM clients
	WHERE name = 'Myworks');

# 子查询返回多个值的时候需要用 IN 关键字
UPDATE invoices
SET
	payment_total = invoice_total * 0.1, 
    payment_date = due_date
WHERE client_id IN
	(SELECT client_id
	FROM clients
	WHERE state IN ('CA', 'NY'));
```

## 删除行
```sql
USE sql_invoicing;
DELETE FROM invoices
WHERE invoice_id = 1;
# 带子查询版本
DELETE FROM invoices
WHERE client_id IN 
(SELECT client_id
FROM clients
WHERE name = 'Myworks');
```

## 恢复数据库
这里指的是本课程用的数据库

恢复方法：
打开SQL脚本，然后执行即可

# 第五章
## 聚合函数
MySQL 有很多内置函数，其中有一种叫做聚合函数。

例如： MAX(), MIN(), AVG(), SUM(), COUNT()

```sql
USE sql_invoicing;
SELECT
	MAX(payment_date) AS latest,
	MIN(invoice_total) AS lowest,
    AVG(invoice_total) AS average,
    SUM(invoice_total * 1.1) AS total_1_1,
    COUNT(DISTINCT client_id) AS clients_of_invoicing,
    COUNT(*) AS number_of_all_records
FROM invoices;
```

## GROUP BY子句
```sql
USE sql_invoicing;
SELECT
	state,
	city,
	SUM(invoice_total) AS total_sales
FROM invoices i 
JOIN clients USING (client_id)
WHERE invoice_date BETWEEN '2019-01-01' AND '2019-12-31'
GROUP BY state, city
ORDER BY total_sales;
```

## HAVING子句
WHERE是对成表前就已经存在的数据进行筛选
HAVING使用场景是成表后再筛选数据
```sql
USE sql_invoicing;
SELECT
	client_id,
	SUM(invoice_total) AS total_sales,
    COUNT(*) AS number_of_invoices
FROM invoices i
GROUP BY client_id
HAVING total_sales > 500 AND number_of_invoices > 1;
```

## WITH ROLLUP关键字
加了这个关键字后，会额外一行或多行数据，把一些数据加起来
```sql
USE sql_invoicing;
SELECT
	client_id,
	SUM(invoice_total) AS total_sales
FROM invoices i
GROUP BY client_id WITH ROLLUP;

# exemple 2
USE sql_invoicing;
SELECT
	state,
    city,
	SUM(invoice_total) AS total_sales
FROM invoices i
JOIN clients c USING (client_id)
GROUP BY state, city WITH ROLLUP;
```

# 第六章
## 子查询（复习？
```sql
USE sql_store;
SELECT * 
FROM products
WHERE unit_price > (
	SELECT unit_price 
	FROM products 
	WHERE name REGEXP 'Lettuce'
)
```

## IN 运算符
```sql
# 找出从未被卖出过的产品
USE sql_store;
SELECT *
FROM products
WHERE product_id NOT IN (
	SELECT DISTINCT product_id
	FROM order_items
);
```

## 子查询 vs 连接
```sql
# 找出从未被卖出过的产品，LEFT JOIN 版本
USE sql_invoicing;
SELECT *
FROM clients
LEFT JOIN invoices USING (client_id)
WHERE invoice_id IS NULL;
```

## ALL 关键字
ALL() 等同于对所有值进行遍历
```sql
USE sql_invoicing;
SELECT *
FROM invoices
WHERE invoice_total > ALL (
	SELECT invoice_total
	FROM invoices
	WHERE client_id = 3
);
# 等同于
USE sql_invoicing;
SELECT *
FROM invoices
WHERE invoice_total > (
	SELECT MAX(invoice_total)
	FROM invoices
	WHERE client_id = 3
);
```

## ANY 关键字
ANY() 大于括号中的任意值即可，与ALL不同

## 相关子查询
```sql
USE sql_hr;
SELECT *
FROM employees e
WHERE salary > (
	SELECT AVG(salary)
	FROM employees
    WHERE office_id = e.office_id # 此处引用了外查询的 数据库e
);
```

## EXISTS 运算符
```sql
USE sql_invoicing;
SELECT *
FROM clients c
WHERE EXISTS (
	SELECT client_id
    FROM invoices
    WHERE client_id = c.client_id
);
# 等同于
SELECT *
FROM clients
WHERE client_id IN (
	SELECT DISTINCT client_id
    FROM invoices
);
```

## SELECT 子句中的子查询
```sql
USE sql_invoicing;
SELECT
	invoice_id,
    invoice_total,
    (SELECT AVG(invoice_total) 
		FROM invoices) AS invoice_average,
    invoice_total - (SELECT invoice_average) AS diff
FROM invoices;
```

## FROM 子句中的子查询
```sql
USE sql_invoicing;
SELECT *
FROM (
	SELECT
		client_id,
		name,
		(SELECT SUM(invoice_total)
			FROM invoices
			WHERE client_id = c.client_id) AS total_sales,
		(SELECT SUM(invoice_total)/ COUNT(invoice_id)
			FROM invoices) AS average,
		(SELECT total_sales) - (SELECT average) AS difference
	FROM clients c
) AS sales_summary
WHERE total_sales IS NOT NULL;
```

# 第七章
一些内置函数

## 一些数值函数
ROUND() 四舍五入
ROUND(5.71) = 6
ROUND(5.71, 1) = 5.7

CEILING(a) 返回大于等于a的最小整数

FLOOR(a) 返回小于等于a的最大整数

ABS() 返回绝对值

RAND() 得到一个0-1之间的随机数

## 字符串函数
LENGTH() 返回字符串长度

UPPER() 返回全大写

LOWER() 返回全小写

LTRIM() 删除字符串左边的空格

RTRIM() 删除字符串右边的空格

TRIM()  删除字符串前导以及末尾的空格

LEFT(s, 4) 返回左边四个字符组成的字符串

RIGHT(s, 4) 返回右边四个字符组成的字符串

SUBSTRING(s, startPosition, length) 注意 startPosition 是从1开始数的

LOCATE(target, s) 返回target 在 s 中的位置，且不区分大小写，target可以是一个字符，也可以是字符串。不存在则返回0

CONCAT(s1, s2, s3) 返回 s1 + s2 + s3

## 一些日期函数
NOW() 返回 xxxx-xx-xx xx:xx:xx

CURDATE() 返回 xxxx-xx-xx

CURTIME() 返回 xx:xx:xx

YEAR() 可以从一些格式中得到年份信息
MONTH() 可以从一些格式中得到月份信息
DAY()
HOUR()
MINUTE()
SECOND()

DAYNAME() 可以得到日期的星期信息
MONTHNAME

EXTRACT(DAY FROM NOW())

## 格式化日期和时间
DATE_FORMAT(NOW(), '%m %d %y %h:%i %p') ymd等的大小写表示不同格式

## 计算日期和时间
DATE_ADD(NOW(), INTERVAL 1 dAY)

DATE_SUB(NOW(), INTERVAL 1 dAY)

DATEDIFF(s1, s2) 返回值是以天为单位的

TIME_TO_SEC()

## IFNULL 与 COALESCE
IFNULL(a, b) 如果a为null 则显示b

COALESCE(a, b, c) 如果a为null，则显示b，如果b也为null，则显示c

## IF 函数
IF(expression, a, b)
```sql
USE sql_store;
SELECT
	order_id,
    order_date,
    IF(
		YEAR(order_date) = '2019',
        'Active',
        'Archived'
        ) AS category
FROM orders;
```

## CASE 运算符
```sql
CASE
	WHEN expression THEN value
	WHEN expression THEN value
	WHEN expression THEN value
	ELSE value
END
```

# 第八章 视图

## 创建视图
```sql
USE sql_invoicing;
CREATE VIEW sales_by_client AS # 这一行，重点
SELECT
	c.client_id,
    c.name,
    SUM(invoice_total) AS total_sales
FROM clients c
JOIN invoices i USING (client_id)
GROUP BY client_id;
```

视图与表的区别：视图并不存储数据

## 更改或删除视图
```sql
# 删除视图
DROP VIEW sales_by_client;

# 创建或者重建
# CREATE OR REPLACE
# 一般存储在views文件夹中，命名为 视图名.sql
# 如果没有源码，可以点视图右边的三个图标中的“扳手”设置图标，就能看到sql自己存的源码
USE sql_invoicing;
CREATE OR REPLACE VIEW sales_by_client AS # 这一行，重点
SELECT
	c.client_id,
    c.name,
    SUM(invoice_total) AS total_sales
FROM clients c
JOIN invoices i USING (client_id)
GROUP BY client_id;
```

## 可更新视图
视图在满足以下条件的时候可以更新(即使用INSERT、UPDATE、DELETE）:
1. 没DISTINCT
2. 没聚合函数(MIN, MAX, SUM, COUNT ...)
3. 没GROUP BY / HAVING
4. UNION

```sql
# 先建一张视图
USE sql_invoicing;
CREATE OR REPLACE VIEW invoices_with_balance AS
SELECT
	invoice_id,
    number,
    client_id,
    invoice_total,
    payment_total,
    invoice_total - payment_total AS balance,
    invoice_date,
    due_date,
    payment_date
FROM invoices
WHERE (invoice_total - payment_total) > 0;
# 上面的视图是一张可更新视图

# 删除1号发票
DELETE FROM invoices_with_balance
WHERE invoice_id = 1
# 把2号发票的日期延长两天
UPDATE invoices_with_balance
SET due_date = DATE_ADD(due_date, INTERVAL 2 DAY)
WHERE invoice_id = 2
```

## WITH CHECK OPTION
在CREATE 或者 REPLACE 视图的语句结尾加上`WITH CHECK OPTION`，可以免于删除一些数据从视图中删除，例如创建视图的时候可能会选择余额非0的用户数据，在视图中修改数据时，如果将某用户余额花完，会自动将该用户从视图中剔除，但若加了`WITH CHECK OPTION`。
```sql
# 以上一小节的建视图为例子
USE sql_invoicing;
CREATE OR REPLACE VIEW invoices_with_balance AS
SELECT
	invoice_id,
    number,
    client_id,
    invoice_total,
    payment_total,
    invoice_total - payment_total AS balance,
    invoice_date,
    due_date,
    payment_date
FROM invoices
WHERE (invoice_total - payment_total) > 0;
WITH CHECK OPTION
```

## 视图的优点
1. 简化查询
2. 视图可以减少数据库设计改动的影响
3. 可以使用视图限制基础表访问

# 第九章 存储过程和函数
存储过程是一个包含一堆SQL代码的数据库对象，在应用代码中，我们调用这些过程来获取或保存数据

## 创建一个存储过程
```sql
USE sql_invoicing;
DELIMITER $$
CREATE PROCEDURE get_clients()
BEGIN
	SELECT *
	FROM sql_invoicing.clients;
END$$
DELIMITER ;

# 调用存储过程
CALL get_clients();
```

若使用MySQL工作台，可以不需要使用DELIMITER来反复修改分隔符。
1. 右键 stored procedure
2. 选择 create stored procedure

## 删除存储过程
```sql
DROP PROCEDURE IF EXISTS get_clients;
```

## 参数
```sql
USE sql_invoicing;

DROP PROCEDURE IF EXISTS get_clients_by_state;

DELIMITER $$
CREATE PROCEDURE get_clients_by_state
(
	p_state CHAR(2)
)
BEGIN
	SELECT *
	FROM sql_invoicing.clients c
    WHERE c.state = p_state;
END$$
DELIMITER ;

CALL get_clients_by_state('NY');
```

## 带默认值的参数
```sql
-- 上一集的语句略作修改
USE sql_invoicing;

DROP PROCEDURE IF EXISTS get_clients_by_state;

DELIMITER $$
CREATE PROCEDURE `get_clients_by_state`
(
	p_state CHAR(2)
)
BEGIN
	IF p_state IS NULL THEN -- here!
		SELECT * FROM sql_invoicing.clients c;
	ELSE SELECT * FROM sql_invoicing.clients c WHERE c.state = p_state;
	END IF;
END$$
DELIMITER ;

CALL get_clients_by_state(NULL);
```

## 参数验证
```sql
DROP PROCEDURE IF EXISTS make_payment;
DELIMITER $$
CREATE PROCEDURE `make_payment`
(
	p_invoice_id INT,
    p_payment_amount DECIMAL(9, 2),
    p_payment_date DATE
)
BEGIN
	IF p_payment_amount <= 0 THEN -- here !
		SIGNAL SQLSTATE '22003'
			SET MESSAGE_TEXT = 'Invalid payment amount';
	END IF;
	UPDATE invoices i
	SET
		i.payment_total = p_payment_amount,
		i.payment_date = p_payment_date
	WHERE i.invoice_id = p_invoice_id;
END$$
DELIMITER ;
```

## 输出参数
```sql
USE `sql_invoicing`;
DROP procedure IF EXISTS get_unpaid_invoices_for_client;
DELIMITER $$
CREATE PROCEDURE `get_unpaid_invoices_for_client` 
(
	client_id INT,
    OUT invoices_count INT,	-- OUT 前缀表示输出值，类似函数的返回值
    OUT invoices_total DECIMAL(9, 2)
)
BEGIN
	SELECT COUNT(*), SUM(invoice_total)
    INTO invoices_count, invoices_total	-- INTO关键字装入输出值
    FROM invoices i
    WHERE i.client_id = client_id 
		AND payment_total = 0;
END$$
DELIMITER ;

-- 调用流程
set @invoices_count = 0;
set @invoices_total = 0;
call sql_invoicing.get_unpaid_invoices_for_client(3, @invoices_count, @invoices_total);
select @invoices_count, @invoices_total;

```

## 变量
变量存活在连接会话期间，连接断开则被清空，因此叫做 用户变量 或 会话变量。
```sql
set @invoices_count = 0;	-- @ 有点重要
```

另一种变量：本地变量，在存储过程或者函数中定义
```sql
USE sql_invoicing;
DELIMITER $$

CREATE PROCEDURE get_risk_factor()
BEGIN
-- risk_factor = invoices_total / invoices_count * 5
	DECLARE risk_factor DECIMAL(9, 2) DEFAULT 0;
    DECLARE invoices_total DECIMAL(9, 2);
    DECLARE invoices_count INT;
    
    SELECT COUNT(*), SUM(invoice_total)
    INTO invoices_count, invoices_total
    FROM invoices;
    
    SET risk_factor = invoices_total / invoices_count * 5;
    
    SELECT risk_factor;
END$$

DELIMITER ;
```

## 函数
函数与存储过程类似，唯一区别是函数只能返回单一值
```SQL
CREATE DEFINER=`root`@`localhost` FUNCTION `get_risk_factor_by_client`(
	client_id INT
) RETURNS int
-- DETERMINISTIC -- 有确定性，指同输入则有同输出，不依赖数据库的值
READS SQL DATA -- 内有SELECT
-- MODIFIES SQL DATA -- 有插入、更新或删除
BEGIN
-- risk_factor = invoices_total / invoices_count * 5
	DECLARE risk_factor DECIMAL(9, 2) DEFAULT 0;
    DECLARE invoices_total DECIMAL(9, 2);
    DECLARE invoices_count INT;
    
    SELECT COUNT(*), SUM(invoice_total)
    INTO invoices_count, invoices_total
    FROM invoices i
    WHERE i.client_id = client_id;
    
    SET risk_factor = invoices_total / invoices_count * 5;
    
RETURN IFNULL(risk_factor,0);
END


-- test
USE sql_invoicing;
SELECT
	client_id,
    name,
    get_risk_factor_by_client(client_id)
FROM clients;

-- 删除函数
DROP FUNCTION IF EXISTS get_risk_factor_by_client;
```

## 其他约定
函数前加fn，存储过程前加proc，驼峰命名法，首字母命名法等等。

# 第十章 

## 触发器
触发器（trigger）是再插入、更新和删除语句前后自动执行的一系列代码。 
通常使用触发器增强数据一致性
```sql
USE sql_invoicing;

DELIMITER $$ 

CREATE TRIGGER payments_after_insert
	AFTER INSERT ON payments
    FOR EACH ROW 
BEGIN
	UPDATE invoices 
    SET payment_total = payment_total + NEW.amount
	WHERE invoice_id = NEW.invoice_id;
END$$ 
DELIMITER ;
```

## 查看触发器
```sql
SHOW TRIGGERS;
SHOW TRIGGERS LIKE 'payments%';
```

## 删除触发器
```sql
DROP TRIGGER IF EXISTS payments_after_insert;
```

## 使用触发器进行审计
```sql
USE sql_invoicing;
DROP TRIGGER IF EXISTS payments_after_insert;
DELIMITER $$ 
CREATE TRIGGER payments_after_insert
	AFTER INSERT ON payments
    FOR EACH ROW 
BEGIN
	UPDATE invoices 
    SET payment_total = payment_total + NEW.amount
	WHERE invoice_id = NEW.invoice_id;
    -- 以下为审计部分
    -- 即把本次行为本身做一个记录，以方便后续复查
    INSERT INTO payments_audit 
    VALUES (NEW.client_id, NEW.date, NEW.amount, 'Insert', NOW());
END$$ 
DELIMITER ;
```

## 事件Events
事件是按计划执行的一系列任务或者代码，可以只执行一次，也可以按规律执行，例如每天or每周or每月执行一次，用于自动化维护数据库
```sql
SHOW VARIABLES; -- 展示所有系统变量
SHOW VARIABLES LIKE 'event%'; -- 找到以 event 开头的系统变量
SET GLOBAL event_scheduler = ON;

USE sql_invoicing;
DROP EVENT IF EXISTS yearly_delete_stale_audit_rows;
DELIMITER $$
CREATE EVENT yearly_delete_stale_audit_rows
ON SCHEDULE 
	EVERY 1 YEAR STARTS '2019-01-01'
	-- 可把上一行替换为 AT '2019-01-01 11:00'，则只执行一次
DO BEGIN
	DELETE FROM payment_audit
    WHERE action_date < NOW() - INTERVAL 1 YEAR;
END$$
DELIMITER ;
```

## 查看、删除和更改事件
```sql
-- 显示事件
SHOW EVENTS;
SHOW EVENTS LIKE 'yearly%';
-- 删除事件
DROP EVENT IF EXISTS yearly_delete_stale_audit_rows;
-- 更改事件
ALTER EVENT yearly_delete_stale_audit_rows DISABLE; -- or ENABLE
ALTER EVENT -- 之后的语法与 CREATE EVENT 类似
```

# 第十一章 事务
事务的ACID
* Atomicity
* Consistency
* Isolation
* Durability

## 创建事务
```sql
USE sql_store;
-- 开始事务
START TRANSACTION;

INSERT INTO orders (customer_id, order_date, status)
VALUES (1, '2019-01-01', 1);

INSERT INTO order_items
VALUES (LAST_INSERT_ID(), 1, 1, 1);
-- 提交事务
COMMIT;


USE sql_store;
-- 开始事务
START TRANSACTION;
INSERT INTO orders (customer_id, order_date, status)
VALUES (1, '2019-01-01', 1);
-- 突然想退回并且做一些手动检查
ROLLBACK;

-- 查看自动提交的系统变量
SHOW VARIABLES LIKE 'autocommit';
```

## 并发和锁定
解释了一下并发和锁定

## 并发问题
* Lost Updates 丢失更新
没上锁，则晚更新的会覆盖早更新的

* Dirty Reads 脏读
事务A改某个积分为1w，事务A没提交。此时事务B读取了那个1w积分。 
Read Committed读已提交，只能读已经提交了的数据

* Non-repeating Reads 不可重复读 
如果一个事务中读两次，且读到的数据不一样 

* Phantom Reads 幻读 
例：给数据库中所有大于100积分的人发奖，事务开始时读一遍，事务执行过程中，有一个人的积分涨到100以上，则他没得到奖品。用隔离级别“序列化Serializable”来执行，以确保此事务执行时，没有其他操作 此事务涉及到的数据库 的事务在进行

## 事务隔离级别 Transaction Isolation Level

need_

```sql
-- 查看隔离级别
SHOW VARIABLES LIKE 'transaction_isolation';
-- 设置隔离级别
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE; --下一个事务的级别
-- 设置本次会话所有隔离级别
SET SESSION TRANSACTION ISOLATION LEVEL SERIALIZABLE;
-- 设置所有隔离级别
SET GLOBAL TRANSACTION ISOLATION LEVEL SERIALIZABLE;
```
### READ UNCOMMITTED 读未提交
```sql
# 执行顺序按s1, s2, s3...执行
# 会话1
-- s1
USE sql_store;
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
-- s3
SELECT points
FROM customers
WHERE customer_id = 1;

# 会话2
-- s2
USE sql_store;
START TRANSACTION;
UPDATE customers
SET points = 20
WHERE customer_id = 1;
-- s4
ROLLBACK;

-- 执行完毕以后，会话1会读到一个从未在数据库中真正提交的数据：
-- id为1的客户的积分是20
-- 这就是脏读
```

### READ COMMITTED 读已提交
```sql
-- 会话1
-- step1
USE sql_store;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;
-- step3
SELECT points
FROM customers
WHERE customer_id = 1;
COMMIT;

-- 会话2
-- step2
USE sql_store;
START TRANSACTION;
UPDATE customers
SET points = 30
WHERE customer_id = 1;
-- step4
COMMIT;
```

### REPEATABLE READ 可重复读
约等于开始事务前搞一个整体的copy（实际上应该不是），然后从copy里读数，使得事务期间读到的数据具有一致性。

### SERIALIZABLE 序列化
人如其名，序列化，拒绝并发，一个事务一个事务的执行，仿佛数据库是单用户一般。

好处防止幻读等各种并发问题，坏处并发度降低，使得数据库性能下降。

## 死锁
```sql
-- session 1
-- step 1
USE sql_store;
START TRANSACTION;
UPDATE customers SET state = 'VA' WHERE customer_id = 1;
-- step 3
UPDATE orders SET status = 1 WHERE order_id = 1;
COMMIT;

-- session 2
-- step 2
USE sql_store;
START TRANSACTION;
UPDATE orders SET status = 1 WHERE order_id = 1;
-- step 4
UPDATE customers SET state = 'VA' WHERE customer_id = 1;
COMMIT;
```

# 第十二章

## 数据类型
* String Types
* Numeric Types
* Date And Time Types
* Blob Types
* Spatial Types

## String
最常见的是CHAR，VARCHAR

VARCHAR(50) 短字符串，例如账号密码
VARCHAR(255) 地址等

VARCHAR 最大64kB，65535

MEDIUMTEXT,最大16MB 最多可以存储1600万多个字符，对于JSON对象、CSV字符串以及中短长度的书比较好使。

LONGTEXT，最大4GB，适合存书以及多年的日志

TINYTEXT 最大255字节
TEXT 最大64KB

英语1字节，欧洲、中东2字节，亚洲3字节（例如中文日文）

## Integers

TINYINT 1B [-128, 127]
UNSIGNED TINYINT [0, 255]

SMALLINT 2B [-32K, 32K]

MEDIUMINT 3B [-8M, 8M]

INT 4B [-2B, 2B]

BIGINT 8B [-9Z, 9Z]

INT(4) 在数值不够4位的时候，会补0，例如把1显示为0001，但只会影响显示，不会影响MySQL存储它们的方式。

## Rationals
DECIMAL(p, s)	p 精度 1- 65，s 小数点后的位数 
DECIMAL的同义词有DEC, NUMERIC， FIXED

下面这两种存储的都是近似值，不是精确值
FLOAT 4B
DOUBLE 8B

## Booleans
BOOL
BOOLEAN

## ENUMS
ENUM('small', 'medium', 'large')

## Date/Time
DATE
TIME
DATETIME	8B
TIMESTAMP 	4B，最多存到2038年的数据
YEAR

## Blobs
TINYBLOB 最大255B
BLOB 	最大65KB
MEDIUMBLOB	最大16MB
LONGBLOB	最大4GB

非常不建议存二进制数据到数据库里。理由：
* 数据库大小会迅速增加
* 会弱化数据备份的功能
* 性能变差
* 存取数据会需要额外的代码

## JSON
```json
{
	"key1" : value1,
	"key2" : value2
}
```
```sql
-- 方法一
USE sql_store;
UPDATE products
SET properties = '
{
	"dimensions":[1, 2, 3],
    "weight": 10,
    "manufacturer":{"name":"sony"}
}
'
WHERE product_id = 1;

-- 方法二，调用内置函数
USE sql_store;
UPDATE products
SET properties = JSON_OBJECT(
	'weight', 10,
    'dimensions', JSON_ARRAY(1, 2, 3),
    'manufacturer',JSON_OBJECT('name', 'sony')
)
WHERE product_id = 1;
```

```sql
-- 提取JSON对象中键值的方法，$代表的是当前路径
SELECT product_id, JSON_EXTRACT(properties, '$.weight') AS weight
FROM products
WHERE product_id = 1;

-- 方法二
SELECT product_id, properties ->'$.weight'AS weight
FROM products
WHERE product_id = 1;

-- 可以对数组使用从0开始的索引
SELECT product_id, properties ->'$.dimensions[0]'AS what
FROM products
WHERE product_id = 1;

-- JSON中的JSON，使用 . 来访问
SELECT product_id, properties ->'$.manufacturer.name'AS what
FROM products
WHERE product_id = 1;

-- ->>可以去掉结果中的""
SELECT product_id, properties ->>'$.manufacturer.name'AS what
FROM products
WHERE product_id = 1;
```

```sql
-- 修改JSON对象
USE sql_store;
UPDATE products
SET properties = JSON_SET(
	properties,	-- 字段名
	'$.weight', 30,	-- 改老的
    '$.age', 10		-- 加新的
)
WHERE product_id = 1;

-- 删除JOSN对象里的东西
USE sql_store;
UPDATE products
SET properties = JSON_REMOVE(
	properties,	-- 字段名
    '$.age'	-- 要删除的东西
)
WHERE product_id = 1;
```

# 第十三章 设计数据库

## Data Modelling 数据建模
* 理解和分析业务需求
多收集信息，跟合作方、其他部门甚至终端用户讨论需求
* 建立业务的概念模型
包括业务中的实体、事物或者概念以及它们之间的关系
* 建立逻辑模型
建立一个数据模型或者数据结构用于存储数据，是一个独立于数据技术的抽象数据模型。
* 建立一个物理模型
具体的数据库

## Conceptual Models 概念模型
找出实体以及它们之间的关系，实体可能有人、事件、位置等。

可视化的搞概念模型方法：
* 实体关系图（ER图），通常用于数据建模
* UML图（Unified Modeling languages）

魔石的教学里采用ER图，windows可以用 Microsoft visio画，也可以使用在线工具draw.io, LucidCharts来画

## Logical Models 逻辑模型
把概念模型细化，比如
* 把name标上string，但不能标varchar，因为varchar是MySQL的实现细节
* 尽量拆分、细化，例如name拆分成姓、名，地址拆分为国家、省、市、区、街道、门牌号、楼
* 给实体之间的关系命名，这在概念模型中不太重要，但在逻辑模型中需要搞清楚

## Physical Models 实体模型
需要确定数据库

## 外键
引入其他表的主键，可以用来当这张表的主键，也可以不当。

可以调外键的行为，有几种选项
* RESTRICT，拒绝更新
* CASCADE，级联，跟着别的表的键一起变，如果被删了，则一起删
* SET NULL，设为NULL，会导致一个子记录失去父表，变成孤儿记录，尽量不要选这个
* NO ACTION，与RESTRICT相同

## Normalization 标准化
标准化是审查我们的设计，并确保它遵循一些防止数据重复的预定义规则的这一过程。

### 1NF 1st Normal Form 第一范式
Each cell should have a single value and we cannot have repeated columns.

有的时候需要借助连接表来确保第一范式
* Link Table 链接表
用于帮助两个表进行多对多关系链接的表，这个表会与另外两个表建立一对多关系。 
这个表是多，另外两个是一，且一般这个表会以那两个外键作为主键。

### 2NF 第二范式
Every table should describe one entity, and every column in that table should describe that enetity.

例如订单表里，不能有客户名的列，但可以有客户id的列。

### 3NF 第三范式
A column in a table should not be derived from other columns.

表中的列不能从其他列派生而来，例如，总额，消费，余额三个同时出现在columns中。
又或，customer_id 与 customer_name 不能同时出现在列中

## EAV
Entities

Attributes

Values

Solve today's problems, not future problems that may never happen.

Simplicity is the ultimate sophistication.

## Forward Engineering 正向工程
正向工程指的是，通过一个模型，建造一个数据库

搞完模型后，在Database选项找到正向工程，点击。之后按步骤完成就完事了。

## 数据库同步模型
修改数据库后，如何将改变同步到所有数据库中去。

在ERR图中做好修改后，点击上方的 Database 里的 Sychronize Model，按照一系列的流程弄好后，就完事了。最后阶段的代码最好复制下来同步到git里，方便其他使用这个数据库的人进行同步。

## Reverse Engineering 模型的逆向工程
从数据库得到模型的过程叫做逆向工程。

## 创建、删除数据库
```sql
CREATE DATABASE IF NOT EXISTS test;
DROP DATABASE IF EXISTS test;
```

## 创建、删除表
```sql
CREATE DATABASE IF NOT EXISTS test;
USE test;
DROP TABLE IF EXISTS customers;
CREATE TABLE IF NOT EXISTS customers
(
	customer_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name 	VARCHAR(50) NOT NULL,
    points		INT NOT NULL DEFAULT 0,
    email		VARCHAR(255) NOT NULL UNIQUE
);
```

## 修改表
```sql
ALTER TABLE customers
	ADD last_name VARCHAR(50) UNIQUE AFTER first_name
```





















