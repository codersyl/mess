// 用于计算最大公约数

int gcd(int a, int b)
{
    if(b == 0)  return a;
    return gcd(b, a % b);
}