{
    depfiles_format = "gcc",
    depfiles = "runRemote.o: ext_deps/wiringpi/runRemote.c ext_deps/wiringpi/wiringPi.h  ext_deps/wiringpi/wpiExtensions.h ext_deps/wiringpi/drcNetCmd.h  ext_deps/wiringpi/network.h ext_deps/wiringpi/runRemote.h\
",
    files = {
        "ext_deps/wiringpi/runRemote.c"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-fvisibility=hidden",
            "-O3",
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
            "/usr/include/libpng16",
            "-DNDEBUG"
        }
    }
}