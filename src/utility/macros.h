#ifndef GAME_MACROS
#define GAME_MACROS


/* MACRO FUNCTIONS */
#define foreach(array, type, key, value) for (key = 0, value = array[key]; key < (sizeof(array)/sizeof(type)); ++key, value = array[key])
#define init(module) module##_init()
#define pool_overflow(type) printf("ERROR: " #type " pool overflow.\n"); return 0

/* MACRO CONSTANTS */
#define PI 3.14159265358979323846

#endif
