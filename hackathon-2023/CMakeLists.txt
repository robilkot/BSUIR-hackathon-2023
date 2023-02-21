cmake_minimum_required(VERSION 3.5)

project(hackathon-2023 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


####################################### Здесь должен быть ваш путь ############################
set (BOOST_ROOT "C:/boost_1_81_0/boost_1_81_0/boost_mingw_1120_64") # Путь к библиотеке Boost
################################################################################################
find_package(PythonLibs 3.9 REQUIRED) #подключение Python

#Справочная инфа
message("Python_FOUND:${Python_FOUND}")
message("Python_VERSION:${Python_VERSION}")
message("Python_Development_FOUND:${Python_Development_FOUND}")
message("Python_LIBRARIES:${Python_LIBRARIES}")


# boost
set(Boost_NO_SYSTEM_PATHS true)
set (Boost_USE_STATIC_LIBS OFF CACHE BOOL "use static libraries from Boost")
set (Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED
  COMPONENTS
 python
  )

include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

  # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )

  # force all boost libraries to dynamic link (we already disabled
  # autolinking, so I don't know why we need this, but we do!)
  add_definitions( -DBOOST_ALL_DYN_LINK )


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        settings.cpp
        settings.h
        settings.ui
        editor.cpp
        editor.h
        editor.ui
        choice.cpp
        choice.h
        choice.ui
        exam.cpp
        exam.h
        exam.ui
        questions.cpp
        dynamiclabel.cpp
        dynamiclabel.h
        dynamiclineedit.cpp
        dynamiclineedit.h
        dynamicradiobutton.cpp
        dynamicradiobutton.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hackathon-2023
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET hackathon-2023 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(hackathon-2023 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(hackathon-2023
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_include_directories(hackathon-2023 PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(hackathon-2023 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  ${PYTHON_LIBRARIES})


install(TARGETS hackathon-2023
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS hackathon-2023
    LIBRARY DESTINATION ${Boost_INCLUDE_DIRS})
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(hackathon-2023)
endif()
