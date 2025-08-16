{
    files = {
        "ext_deps/libqrencode/qrspec.c"
    },
    depfiles_format = "gcc",
    depfiles = "qrspec.o: ext_deps/libqrencode/qrspec.c ext_deps/libqrencode/config.h  ext_deps/libqrencode/qrspec.h ext_deps/libqrencode/qrencode.h  ext_deps/libqrencode/qrinput.h ext_deps/libqrencode/bitstream.h\
",
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