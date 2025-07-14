#include <gtk/gtk.h>



#define DEV_TEST

#ifdef DEV_TEST
    #include "dev_test.h"
#else
    #include "UI/entry.h"
    #include "gpio_utils.h"
    #include "config_utils.h"
#endif

int main(int argc, char *argv[])
{
#ifdef DEV_TEST
    Dev_Test(argc,argv);
#else
    configuration_setup();
    ui_entry(argc, argv);
    signal(SIGINT, onExit);
#endif

    return 0;
}