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




#ifdef ETK_PLATFORM_DRM
void EtkUtils::DRM_GetScreenSize(int &w, int &h)
{   
    // Set them to 0 if something fails so the app can still runn although the screen scaling might be bad
    w = 0;
    h = 0;

    int fd = open("/dev/dri/card1", O_RDONLY | O_CLOEXEC);
    if(fd < 0)
    {
        log_error("Failed to open /dev/dri/card1: %s", strerror(errno));
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
    {
	    w = (int)conn -> modes[0].hdisplay;
	    h = (int)conn -> modes[0].vdisplay;
        log_debug("Resolution: %dx%d @ %dHz", conn->modes[0].hdisplay, conn->modes[0].vdisplay, conn->modes[0].vrefresh);
    }
    else    
        log_warn("Failed to get screen resolution !!!");

 
    drmModeFreeConnector(conn);
    drmModeFreeResources(res);
    close(fd);
}
#endif
