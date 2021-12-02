// from boost
#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_


class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);  // 禁用拷贝构造函数
  const noncopyable& operator=(const noncopyable&); // 禁用赋值构造函数
};

#endif // _NONCOPYABLE_H_