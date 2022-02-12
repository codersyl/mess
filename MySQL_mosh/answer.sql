# p8
SELECT name,
	unit_price,
    unit_price * 1.1 AS "new price"
FROM products;

# p9
SELECT *
FROM orders
WHERE order_date >= '2019-01-01';

# p10
SELECT *
FROM order_items
WHERE order_id = 6 AND (quantity * unit_price > 30);

# p11
SELECT *
FROM products
WHERE quantity_in_stock IN (49, 38, 72);

# p12
SELECT *
FROM	customers
WHERE birth_date BETWEEN '1990-01-01' AND '2000-01-01' ;

# p13
SELECT *
FROM	customers
WHERE 	address LIKE '%trail%' OR 
				address LIKE '%avenue%' OR 
				phone LIKE '%9';

# p14
SELECT *
FROM	customers
-- WHERE 	first_name = 'elka' OR first_name = 'ambur';
-- WHERE last_name REGEXP 'ey$|on$';
-- WHERE last_name REGEXP '^my|se';
WHERE last_name REGEXP 'b[ru]'

# p15
SELECT *
FROM	orders
WHERE shipped_date IS NULL;

# p16
SELECT *, quantity * unit_price AS total_price
FROM	order_items
WHERE order_id = 2
ORDER BY total_price DESC;

# p17
SELECT *
FROM	customers
ORDER BY points DESC
LIMIT 3;

# p18
SELECT order_id, o.product_id, quantity, o.unit_price
FROM	order_items o
JOIN products p
	ON o.product_id = p.product_id
ORDER BY order_id;

