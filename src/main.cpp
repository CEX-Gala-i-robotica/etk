//#define ETK_INDIVIDUAL_TESTS
#define ETK_DEV








#ifdef ETK_INDIVIDUAL_TESTS
    #include "tests/tests.h"
#else
    #include <stdio.h>
    #include "ui_entry.hpp"
#endif




int main(int argc, char * argv[])
{
    
#ifdef ETK_PLATFORM_DRM
    printf("PLATFORM: DRM\n");
#else
    printf("PLATFORM: DESKTOP\n");
#endif

#ifdef ETK_INDIVIDUAL_TESTS
#else
    etk::AppEntry app;
#endif
    return 0;
}