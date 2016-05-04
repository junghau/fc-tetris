#ifndef NO_ARDUINO
#define NO_ARDUINO

#include <time.h>
srand(time(NULL));
#define random(x) rand()%x

#endif
