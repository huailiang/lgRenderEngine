#ifndef __common__
#define __common__


typedef unsigned int uint;  //32bit
typedef unsigned long long ulong; //64bit

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT  600
#define KEY_CNT 512
#define FPS 30
#define PI 3.141592653

#define angle_to_radian(X) ((X)/180*PI)
#define radian_to_angle(X) ((X)/PI*180)
#define CMID(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define interp(a, b, t) ((a) + ((b) - (a)) * (t))

#endif /* __common__ */
