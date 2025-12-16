#include "ui_entry.hpp"

//#define ETK_INDIVIDUAL_TESTS


#ifdef ETK_INDIVIDUAL_TESTS
extern "C"
{
    #include "tests/tests.h"
}
#else
    #include <stdio.h>
#endif




int main(int argc, char * argv[])
{

#ifndef ETK_INDIVIDUAL_TESTS
#ifdef ETK_PLATFORM_DRM
    printf("PLATFORM: DRM\n");
#else
    printf("PLATFORM: DESKTOP\n");
#endif

#ifdef ETK_INDIVIDUAL_TESTS
#else
    etk::AppEntry app;
#endif
#else
    while(1)
    {
        idk();
    }
#endif
    return 0;
}