#ifndef __common__
#define __common__


typedef unsigned int uint32;
typedef unsigned long long ulong; 

#define REAL_WIDTH  600
#define REAL_HEIGHT  600
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT  600
#define KEY_CNT 512
#define FPS 30
#define PI 3.141592653

#define angle_to_radian(X) ((X)/180*PI)
#define radian_to_angle(X) ((X)/PI*180)
#define clamp(x, min, max) (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define lerp(a, b, t) ((a) + ((b) - (a)) * (t))

#endif /* __common__ */
