{
    files = {
        "ext_deps/wiringpi/mcp3002.c"
    },
    depfiles = "mcp3002.o: ext_deps/wiringpi/mcp3002.c ext_deps/wiringpi/wiringPi.h  ext_deps/wiringpi/wiringPiSPI.h ext_deps/wiringpi/mcp3002.h\
",
    values = {
        "/usr/bin/gcc",
        {
            "-g",
            "-O0",
            "-Iext_deps",
            "-Iext_deps/wiringpi",
            "-Iext_deps/nuklear",
            "-Iext_deps/nuklear/backends/xcb_cairo",
            "-Iext_deps/libqrencode",
            "-DLOGC__USER_SETTINGS",
            "-DHAVE_CONFIG_H",
            "-isystem",
            "/usr/include/cairo",
            "-isystem",
            "/usr/include/glib-2.0",
            "-isystem",
            "/usr/lib/aarch64-linux-gnu/glib-2.0/include",
            "-isystem",
            "/usr/include/pixman-1",
            "-isystem",
            "/usr/include/X11/dri",
            "-isystem",
            "/usr/include/freetype2",
            "-isystem",
            "/usr/include/libpng16"
        }
    },
    depfiles_format = "gcc"
}