# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS "source/Wifi.c" "source/IWifi.c"
    INCLUDE_DIRS header
    REQUIRES nvs_flash
)
