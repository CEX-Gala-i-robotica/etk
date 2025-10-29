#ifndef UI_ENTRY_HPP
#define UI_ENTRY_HPP


#include "buildconf.h"





#ifdef ETK_PLATFORM_DRM
    #define WINDOW_WIDTH 0
    #define WINDOW_HEIGHT 0
#else
    #define WINDOW_WIDTH 1080
    #define WINDOW_HEIGHT 900
#endif


namespace etk
{
    class AppEntry
    {
        public:
            AppEntry();
            ~AppEntry();
    };
}
#endif
