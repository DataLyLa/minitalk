#include "minitalk.h"

void hand_error(const char *signal_name)
{
    perror(signal_name);
    exit(EXIT_FAILURE);
}
