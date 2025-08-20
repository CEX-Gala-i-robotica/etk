{
    depfiles = "ui_main.o: src/UI/ui_main.c ext_deps/log_c/log.h  ext_deps/log_c/log_conf.h src/UI/ui_main.h ext_deps/nuklear/nuklear.h  ext_deps/nuklear/backends/xcb_cairo/nuklear_xcb.h  src/UI/components/dev_demos/style.c src/UI/main_window.h  src/UI/../tests.h src/UI/../config_utils.h src/UI/components/trs/trs.h  src/UI/../gpio_utils.h src/UI/../components/servo.h  src/UI/../components/stepper_uln2003.h src/UI/../components/dht.h  src/UI/../components/ultrasonic.h src/UI/../components/mpu6050.h  src/UI/../components/LCD_I2C.h src/UI/../components/universal_sensors.h  src/UI/../components/keypad.h src/UI/../components/TTP229.h  src/UI/../components/A4988.h src/UI/../components/PCA9685.h  ext_deps/wiringpi/wiringPiI2C.h ext_deps/libqrencode/qrencode.h  src/UI/default_theme.h\
",
    depfiles_format = "gcc",
    files = {
        "src/UI/ui_main.c"
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