/*
 * UNISTD made by vivio2115 and StackOverflow (Github) last updated on 12/02/2025.
 * Its free to use and its under MIT license.
 * 
 * WATINING!!!
 * This may be not the best solution for usleep function, but it works.
 */

#ifndef UNISTD_H
#define UNISTD_H

#include <windows.h> //include the windows API header for the sleep function
#include <stdint.h>  //include the standard integer types header for uint32_t

typedef uint32_t useconds_t; //define useconds_t as an alias for uint32_t

//function to sleep for a specified number of microseconds
static int usleep(useconds_t usec) {
    Sleep(usec / 1000); //sleep function takes milliseconds so convert microseconds to milliseconds
    return 0; //return 0 to indicate success
}

#endif //UNISTD_H
