#ifndef UI_ENTRY_HPP
#define UI_ENTRY_HPP



#ifdef ETK_PLATFORM_DRM
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
#else
    #define WINDOW_WIDTH 1080
    #define WINDOW_HEIGHT 1000
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
