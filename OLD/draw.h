#include "queue.h"
#include <cairo.h>
#include <cairo-pdf.h>



struct point2d_t{
  double x;
  double y;
};

typedef struct point2d_t* Point;
queue s;

void Init( void );
void AddPoint( double x, double y );
void DrawPoints( void );
void Destroy();
