#include "queue.h"

queue s;

struc point2d_t{
  double x;
  double y;
};

typedef Point struct point2d_t;

void Init( void );
void AddPoint( double x, double y );
void DrawPoints( void );
void Destroy();
