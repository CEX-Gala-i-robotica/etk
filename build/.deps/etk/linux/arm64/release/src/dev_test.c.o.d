{
    depfiles = "dev_test.o: src/dev_test.c ext_deps/wiringpi/wiringPi.h  ext_deps/wiringpi/softTone.h ext_deps/wiringpi/softServo.h  ext_deps/wiringpi/softPwm.h ext_deps/log_c/log.h  ext_deps/log_c/log_conf.h src/config_utils.h src/dev_test.h  src/gpio_utils.h src/components/servo.h src/components/stepper_uln2003.h  src/components/dht.h src/components/ultrasonic.h  src/components/mpu6050.h src/components/LCD_I2C.h  src/components/universal_sensors.h src/components/keypad.h  src/components/TTP229.h src/components/A4988.h src/components/PCA9685.h  ext_deps/wiringpi/wiringPiI2C.h src/UI/components/trs/trs.h\
",
    files = {
        "src/dev_test.c"
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
    },
    depfiles_format = "gcc"
}