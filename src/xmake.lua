add_rules("mode.debug", "mode.release", "plugin.compile_commands.autoupdate")



-- DRM based
target("etk")
    --set_default(false)

    add_includedirs(
        "../assets/fonts/embeded",
        "../assets/icons/embeded",
        "../externals/",
        "../externals/wiringpi",
        "../externals/raylib",
        "../externals/imgui/backends/rlimgui",
        "../externals/imgui",
        "../externals/implot",
        "../externals/libqrencode",
        "../externals/csv"
    )

    -- Internal dependencies
    add_linkdirs(
        "../externals",
        "../externals/lib/raylib"
    )
    add_links("raylib_drm")

    -- System dependencies
    add_links(
        "GLESv2",
        "EGL",
        "gbm",
        "drm",
        "m",
        "dl",
        "pthread",
        "crypt"
    )

    --add_defines('PLATFORM_DRM')
    add_defines(
        "PLATFORM_DRM",
        "ETK_PLATFORM_DRM",
        "LOGC__USER_SETTINGS",
        "HAVE_CONFIG_H"
    )

    add_files(
        "../externals/csv/*.c",
        "../externals/libqrencode/*.c",
        "../externals/log_c/*.c",
        "../externals/wiringpi/*.c",
        "../externals/imgui/backends/rlimgui/*.cpp",
        "../externals/imgui/*.cpp",
        "*.c",
        "*.cpp",
        "components/*.c",
        "config/*.cpp",
        "UI/*.cpp"
    )

    after_build(function (target)
        -- Copy the fonts (for now)
        os.cp("../assets/fonts/Tomorrow-Medium.ttf", target:targetdir())
    end)







-- GLFW Based
target("etk-de")
    add_includedirs(
        "../assets/fonts/embeded",
        "../assets/icons/embeded",
        "../externals/",
        "../externals/wiringpi",
        "../externals/raylib",
        "../externals/imgui",
        "../externals/imgui/backends/rlimgui",
        "../externals/implot",
        "../externals/libqrencode",
        "../externals/csv"
    )

    add_linkdirs("../externals/lib/raylib")
    add_links("raylib_glfw")

    -- System dependencies
    add_links(
        "GLESv2",
        "EGL",
        "gbm",
        "m",
        "dl",
        "pthread",
        "crypt"
    )

    add_defines(
        "PLATFORM_DESKTOP",
        "LOGC__USER_SETTINGS",
        "HAVE_CONFIG_H"
    )

    add_files(
        "../externals/csv/*.c",
        "../externals/libqrencode/*.c",
        "../externals/log_c/*.c",
        "../externals/wiringpi/*.c",
        "../externals/imgui/backends/rlimgui/*.cpp",
        "../externals/imgui/*.cpp",
        "*.cpp",
        "*.c",
        "components/*.c",
        "config/*.cpp",
        "UI/*.cpp"
    )

    after_build(function (target)
        -- Copy the fonts (for now)
        os.cp("../assets/fonts/Tomorrow-Medium.ttf", target:targetdir())
    end)