// sys/time.h

#include<sys/time.h>

int gettimeofday(struct  timeval*tv,struct  timezone *tz )
// 成功则返回0，失败返回－1
// 参数一用来存时间
// 参数二用来存时区

struct  timeval{
       long  tv_sec;/*秒*/
       long  tv_usec;/*微妙*/
};

struct  timezone{
        int tz_minuteswest;/*和greenwich时间差*/
        int tz_dsttime; 
};

// tz_dsttime:
// DST_NONE  //不使用
// DST_USA  //美国
// DST_AUST  //澳洲
// DST_WET  //西欧
// DST_MET  //中欧
// DST_EET  //东欧
// DST_CAN  //加拿大
// DST_GB  //大不列颠
// DST_RUM  //罗马尼亚
// DST_TUR  //土耳其
// DST_AUSTALT  //澳洲(1986 年以后)