{
    files = {
        "ext_deps/wiringpi/wpiExtensions.c"
    },
    depfiles = "build/.objs/etk/linux/arm64/debug/ext_deps/wiringpi/wpiExtensions.c.o:  ext_deps/wiringpi/wpiExtensions.c ext_deps/wiringpi/wiringPi.h  ext_deps/wiringpi/mcp23008.h ext_deps/wiringpi/mcp23016.h  ext_deps/wiringpi/mcp23017.h ext_deps/wiringpi/mcp23s08.h  ext_deps/wiringpi/mcp23s17.h ext_deps/wiringpi/sr595.h  ext_deps/wiringpi/pcf8574.h ext_deps/wiringpi/pcf8591.h  ext_deps/wiringpi/mcp3002.h ext_deps/wiringpi/mcp3004.h  ext_deps/wiringpi/mcp4802.h ext_deps/wiringpi/mcp3422.h  ext_deps/wiringpi/max31855.h ext_deps/wiringpi/max5322.h  ext_deps/wiringpi/ads1115.h ext_deps/wiringpi/sn3218.h  ext_deps/wiringpi/drcSerial.h ext_deps/wiringpi/drcNet.h  ext_deps/wiringpi/drcNetCmd.h ext_deps/wiringpi/pseudoPins.h  ext_deps/wiringpi/bmp180.h ext_deps/wiringpi/htu21d.h  ext_deps/wiringpi/ds18b20.h ext_deps/wiringpi/rht03.h  ext_deps/wiringpi/wpiExtensions.h\
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