# some notes

# dense_rank()
# exemple code
SELECT 
	Score,
	dense_rank() over(order by Score desc) as 'Rank'
FROM Scores;
# 上面的这段代码的 dense_rank()意思是根据 Score 倒序排名
# 允许并列，例如有3个10分，1个9分，其中3个10分都排第1，9分的排第4