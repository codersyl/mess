// from boost
#pragma once

class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);  // 禁用拷贝构造函数
  const noncopyable& operator=(const noncopyable&); // 禁用赋值构造函数
};