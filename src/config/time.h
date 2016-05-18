#ifndef GAME_TIME_H
#define GAME_TIME_H

typedef struct _time Time;
/* Time
<description text> */

void Time_init();
/* () -> void */

double Time_getFrameunit();
/* 
 */

int Time_getFramerate();
/* 
 */

int Time_getFramemilisec();
/* 
 */

#endif
