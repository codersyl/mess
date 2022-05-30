# some notes

# dense_rank()
# exemple code
SELECT 
	Score,
	dense_rank() over(order by Score desc) as 'Rank'
FROM Scores;
# 上面的这段代码的 dense_rank()意思是根据 Score 倒序排名
# 允许并列，例如有3个10分，1个9分，其中3个10分都排第1，9分的排第4


# ROUND()
ROUND(1.333, 2)
# 上面表示对 1.333取小数点后两位数


# GROUP_CONCAT()
# 类似于CONCAT，可以使得()里的字符用 , 串联起来
# 不同于CONCAT的地方是，需要配合 GROUP BY 使用，()里的内容可以是GROUP后的东西

# UCASE()
# 返回字母全为大写

# LCASE()
# 返回字母全为小写

# SUBSTRING(s, index)
# 返回子字符串，且sql中index是从1开始计算的

