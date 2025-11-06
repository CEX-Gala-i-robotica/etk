#ifndef UTILS_HPP
#define UTILS_HPP



namespace EtkUtils
{
#ifdef ETK_PLATFORM_DRM
    void DRM_GetScreenSize(int &w, int &h);
#endif
}
#endif
