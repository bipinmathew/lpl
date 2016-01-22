

#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
