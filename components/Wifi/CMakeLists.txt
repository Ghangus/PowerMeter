# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS "Wifi.c" "IWifi.c"
    INCLUDE_DIRS "include"
    REQUIRES nvs_flash
)
