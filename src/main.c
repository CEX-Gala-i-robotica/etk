//#include <gtk/gtk.h>

#include <signal.h>

//#define DEV_TEST

#ifdef DEV_TEST
    #include "dev_test.h"
#else
    #include "UI/ui_main.h"
    #include "gpio_utils.h"
    #include "config_utils.h"
#endif

int main(int argc, char *argv[])
{
#ifdef DEV_TEST
    Dev_Test(argc,argv);
#else
    configuration_setup();
    ui_main(argc, argv);
    signal(SIGINT, on_exit_signal);
#endif

    return 0;
}