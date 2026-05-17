cmake_minimum_required(VERSION 3.19)
project(caloryCount LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(caloryCount
    WIN32 MACOSX_BUNDLE
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    person.h person.cpp
    resources.qrc

)

target_link_libraries(caloryCount
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(caloryCount PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS caloryCount
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET caloryCount
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
