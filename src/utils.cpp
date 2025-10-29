#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <log_c/log.h>

#ifdef ETK_PLATFORM_DRM
    #include <libdrm/drm.h>
    #include <xf86drm/xf86drm.h>
    #include <xf86drm/xf86drmMode.h>
#endif








#include "utils.hpp"



// Some poor attempt to get the physical screen size + resolution
// this is required for setting the rendering screen size in raylib drm
#ifdef ETK_PLATFORM_DRM
void EtkUtils::DRM_GetScreenSize(int w, int h)
{
    int fd = open("/dev/dri/card0", O_RDONLY);
    if(fd < 0)
    {
        log_error("Failed to open /dev/dri/card0: %s", strerror(errno));
        return;
    }

    drmModeRes *res = drmModeGetResources(fd);
    if(!res)
    {
        log_error("drmModeGetResources() failed: %s", strerror(errno));
        close(fd);
        return;
    }

    drmModeConnector *conn = NULL;
    for(int i = 0; i < res->count_connectors; i++)
    {
        conn = drmModeGetConnector(fd, res->connectors[i]);
        if(conn && conn->connection == DRM_MODE_CONNECTED)
            break;
        drmModeFreeConnector(conn);
        conn = NULL;
    }

    if(!conn)
    {
        log_error("No connected display found");
        drmModeFreeResources(res);
        close(fd);
        return;
    }

    log_debug("Physical size: %dmm x %dmm", conn->mmWidth, conn->mmHeight);
    if(conn->count_modes > 0)
        log_debug("Resolution: %dx%d @ %dHz", conn->modes[0].hdisplay, conn->modes[0].vdisplay, conn->modes[0].vrefresh);

    drmModeFreeConnector(conn);
    drmModeFreeResources(res);
    close(fd);
}
#endif