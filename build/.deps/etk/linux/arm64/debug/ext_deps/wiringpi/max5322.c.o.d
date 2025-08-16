{
    files = {
        "ext_deps/wiringpi/max5322.c"
    },
    depfiles = "max5322.o: ext_deps/wiringpi/max5322.c ext_deps/wiringpi/wiringPi.h  ext_deps/wiringpi/wiringPiSPI.h ext_deps/wiringpi/max5322.h\
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