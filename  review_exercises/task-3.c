#include <stdio.h>
#include <math.h>

struct Points {
float x1;
float x2;
float y1;
float y2;
};

float power (float, float);
float distance (struct Points *);
float from_zero_distance (struct Points *);
void midpoint (struct Points *);

int main ()
{
struct Points ptr;

printf("Distance is %f\n", distance(&ptr));

printf("From 0 distance is %f\n", from_zero_distance(&ptr));

midpoint(&ptr);

return 0;
}

void midpoint (struct Points * ptr)
{
ptr->x1 = 2;
ptr->y1 = 4;

ptr->x2 = 6;
ptr->y2 = 8;

printf("X midpoint is: %f\n", (ptr->x1 + ptr->x2) / 2);
printf("Y midpoint is: %f\n", (ptr->y1 + ptr->y2) / 2);
}

float distance (struct Points * ptr)
{
ptr->x1 = 2;
ptr->y1 = 3;

ptr->x2 = 6;
ptr->y2 = 6;

float xres = power(ptr->x2 - ptr->x1, 2);
float yres = power(ptr->y2 - ptr->y1, 2);

return sqrt(xres + yres);
}

float from_zero_distance (struct Points * ptr)
{
 ptr->x1 = 2;
 ptr->y1 = 3;
 
 return sqrt(power(ptr->x1, 2) + power(ptr->y1, 2));
}

float power (float n, float p)
{
 if (p == 0) return 1;
 return power(n, --p) * n;
}