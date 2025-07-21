add_rules("mode.debug", "mode.release", "plugin.compile_commands.autoupdate", {outputdir = "src/"})
add_requires("libxcb", {system = true})
add_requires("cairo", {system = true})
add_requires("xcb", {system = true})
add_requires("xcb-util", {system = true})
add_requires("xcb-keysyms", {system = true})
add_requires("xkbcommon", {system = true})
add_requires("xkbcommon-x11", {system = true})
add_requires("freetype2", {system = true})


set_config("export.compile_commands", true)

target("etk")
    set_kind("binary")
    add_defines("LOGC__USER_SETTINGS")
    add_includedirs(
        "ext_deps/",
        "ext_deps/wiringpi",
        "ext_deps/nuklear",
        "ext_deps/nuklear/backends/xcb_cairo"
    )
    add_syslinks("m", "crypt", "rt", "pthread")
    add_files(
        "ext_deps/wiringpi/*.c",
        "ext_deps/cJSON/*.c",
        "ext_deps/csv/*.c",
        "ext_deps/log_c/*.c",
        "src/*.c",
        "src/UI/*.c",
        "src/components/*.c"
    )
    add_packages("libxcb", "cairo", "xcb", "xcb-util", "xcb-keysyms", "xkbcommon", "xkbcommon-x11", "freetype2")
    after_build(function (target)
        -- Copy the assets and the css theme next to the build directory
        os.cp("src/assets", target:targetdir())
    end)