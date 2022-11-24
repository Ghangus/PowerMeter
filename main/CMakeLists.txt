# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS main.c        
    REQUIRES Wifi HTTP_Client UDP_Client GPIO SleepManager
)
