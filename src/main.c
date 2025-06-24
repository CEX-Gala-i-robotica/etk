#include <gtk/gtk.h>


// #define DEV_TEST

#ifdef DEV_TEST
    #include "dev_test.h"
#else
    #include "UI/entry.h"
#endif

int main(int argc, char *argv[])
{
#ifdef DEV_TEST
    Dev_Test(argc,argv);
#else
    ui_entry(argc, argv);
#endif

    return 0;
}