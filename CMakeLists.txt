cmake_minimum_required(VERSION 3.16)

project(VelaryonV3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network PrintSupport)

set(TS_FILES VelaryonV3_en_US.ts)

set(PROJECT_SOURCES



        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VelaryonV3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/app/main.cpp src/app/MainWindow.cpp src/app/MainWindow.h src/core/Protocols/App.h src/core/Protocols/Messages.h dependencies/QCustomPlot/qcustomplot.cpp dependencies/QCustomPlot/qcustomplot.h src/features/communication/udp/codecs/UdpCodec.cpp src/features/communication/udp/codecs/UdpCodec.h src/features/communication/udp/frames_logger/RingBuffer.h src/features/communication/udp/frames_logger/UdpLogger.h src/features/communication/udp/frames_logger/Writer.h src/features/communication/udp/ui/UdpChannelParametersViewModel.cpp src/features/communication/udp/ui/UdpChannelParametersViewModel.h src/features/communication/udp/ui/UdpChannelParametersWidget.cpp src/features/communication/udp/ui/UdpChannelParametersWidget.h src/features/communication/udp/UdpChannel.cpp src/features/communication/udp/UdpChannel.h src/features/communication/udp/UdpCodecBuilder.cpp src/features/communication/udp/UdpCodecBuilder.h src/features/communication/udp/UdpWorker.cpp src/features/communication/udp/UdpWorker.h src/features/file_export/csv/CsvExporter.cpp src/features/file_export/csv/CsvExporter.h src/features/file_export/ui/ExportMenu.h src/features/file_export/ui/ExportMenuViewModel.h src/features/graphics/plot/PlotViewModel.cpp src/features/graphics/plot/PlotViewModel.h src/features/graphics/plot/PlotWidget.cpp src/features/graphics/plot/PlotWidget.h src/features/graphics/GraphicTabView.cpp src/features/graphics/GraphicTabView.h src/features/menu_bar/files/FilesMenu.h src/features/menu_bar/tools/ToolsMenu.cpp src/features/menu_bar/tools/ToolsMenu.h src/features/overlay/debug_display/DebugDisplay.cpp src/features/overlay/debug_display/DebugDisplay.h src/features/overlay/debug_display/DebugDisplayViewModel.cpp src/features/overlay/debug_display/DebugDisplayViewModel.h src/features/parameters_window/ParametersWindow.cpp src/features/parameters_window/ParametersWindow.h src/features/pid/actuator/glowPlug/GlowPlugSwitchWidget.cpp src/features/pid/actuator/glowPlug/GlowPlugSwitchWidget.h src/features/pid/actuator/valve/ValveSwitchWidget.cpp src/features/pid/actuator/valve/ValveSwitchWidget.h src/features/pid/actuator/ActuatorSwitchViewModel.cpp src/features/pid/actuator/ActuatorSwitchViewModel.h src/features/pid/actuator/ActuatorSwitchWidget.cpp src/features/pid/actuator/ActuatorSwitchWidget.h src/features/pid/actuator/StatusTableWidget.cpp src/features/pid/actuator/StatusTableWidget.h src/features/pid/misc/initialise_valve/InitialiseValveButtonViewModel.cpp src/features/pid/misc/initialise_valve/InitialiseValveButtonViewModel.h src/features/pid/misc/initialise_valve/InitialiseValveButtonWidget.cpp src/features/pid/misc/initialise_valve/InitialiseValveButtonWidget.h src/features/pid/misc/Chrono.cpp src/features/pid/misc/Chrono.h src/features/pid/misc/CloseButtonWidget.cpp src/features/pid/misc/CloseButtonWidget.h src/features/pid/misc/LoadingScreen.cpp src/features/pid/misc/LoadingScreen.h src/features/pid/misc/Logo.cpp src/features/pid/misc/Logo.h src/features/pid/misc/PidBackground.cpp src/features/pid/misc/PidBackground.h src/features/pid/sensors/SensorValueIndicatorViewModel.cpp src/features/pid/sensors/SensorValueIndicatorViewModel.h src/features/pid/sensors/SensorValueIndicatorWidget.cpp src/features/pid/sensors/SensorValueIndicatorWidget.h src/features/pid/PidLayout.cpp src/features/pid/PidLayout.h src/features/pid/PidTab.cpp src/features/pid/PidTab.h src/features/pid/PidViewModel.cpp src/features/pid/PidViewModel.h src/features/test/frames/countdown_clock/CountDownClockViewModel.cpp src/features/test/frames/countdown_clock/CountDownClockViewModel.h src/features/test/frames/countdown_clock/CountdownClockWidget.cpp src/features/test/frames/countdown_clock/CountdownClockWidget.h src/features/test/frames/emergency_controls/EmergencyControlsViewModel.cpp src/features/test/frames/emergency_controls/EmergencyControlsViewModel.h src/features/test/frames/emergency_controls/EmergencyControlsWidget.cpp src/features/test/frames/emergency_controls/EmergencyControlsWidget.h src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorViewModel.cpp src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorViewModel.h src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorWidget.cpp src/features/test/frames/tank_pressure/pressure_setting_indicator/TankPressureSettingsIndicatorWidget.h src/features/test/frames/tank_pressure/PressureTanksModel.cpp src/features/test/frames/tank_pressure/PressureTanksModel.h src/features/test/frames/tank_pressure/TankPressureControlerViewModel.cpp src/features/test/frames/tank_pressure/TankPressureControlerViewModel.h src/features/test/frames/tank_pressure/TankPressureControlFrameWidget.cpp src/features/test/frames/tank_pressure/TankPressureControlFrameWidget.h src/features/test/frames/tank_pressure/TankPressureControlWidget.cpp src/features/test/frames/tank_pressure/TankPressureControlWidget.h src/features/test/frames/terminal/LogTerminalViewModel.cpp src/features/test/frames/terminal/LogTerminalViewModel.h src/features/test/frames/terminal/LogTerminalWidget.cpp src/features/test/frames/terminal/LogTerminalWidget.h src/features/test/frames/test_launcher/TestLauncherViewModel.cpp src/features/test/frames/test_launcher/TestLauncherViewModel.h src/features/test/frames/test_launcher/TestLaunchWidget.cpp src/features/test/frames/test_launcher/TestLaunchWidget.h src/features/test/frames/ActuatorControlWidget.cpp src/features/test/frames/ActuatorControlWidget.h src/features/test/frames/TvcControlWidget.cpp src/features/test/frames/TvcControlWidget.h src/features/test/TestBenchModel.cpp src/features/test/TestBenchModel.h src/features/test/TestTabView.cpp src/features/test/TestTabView.h src/mvvm/models/AppModels.cpp src/mvvm/models/AppModels.h src/mvvm/viewmodels/AppViewModels.cpp src/mvvm/viewmodels/AppViewModels.h src/services/Config/ConfigService.cpp src/services/Config/ConfigService.h src/services/EventBus/EventBus.h src/services/FileSystem/FileSystem.h src/services/Logger/Logger.cpp src/services/Logger/Logger.h src/services/Logger/LogService.h src/services/Timer/Timer.cpp src/services/Timer/Timer.h src/services/TXTManager/TxtParser.cpp src/services/TXTManager/TxtParser.h src/services/AppServices.cpp src/services/AppServices.h
        src/features/pid/PidTabFactory.cpp
        src/features/pid/PidTabFactory.h
        src/features/test/frames/tank_pressure/TankPressureControlerFrameFactory.h
        src/features/test/frames/tank_pressure/TankPressureControlerFrameFactory.cpp
        src/features/test/TestTabFactory.cpp
        src/features/test/TestTabFactory.h
        src/features/graphics/GraphicTabFactory.cpp
        src/features/graphics/GraphicTabFactory.h
        src/features/menu_bar/files/FilesMenuFactory.cpp
        src/features/menu_bar/files/FilesMenuFactory.h
        src/features/menu_bar/files/FilesMenu.cpp
        src/features/menu_bar/tools/ToolsMenuFactory.cpp
        src/features/menu_bar/tools/ToolsMenuFactory.h
        src/features/parameters_window/ParametersWindowFactory.cpp
        src/features/parameters_window/ParametersWindowFactory.h
        src/features/overlay/Overlay.cpp
        src/features/overlay/Overlay.h
        src/features/overlay/OverlayFactory.h
        src/features/overlay/OverlayFactory.cpp
        src/features/communication/udp/frames_logger/UdpLogger.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VelaryonV3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(VelaryonV3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VelaryonV3
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(VelaryonV3 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_include_directories(VelaryonV3 PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VelaryonV3)
endif()
set_target_properties(VelaryonV3 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VelaryonV3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VelaryonV3)
endif()

set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE iwyu)


# ─── Runtime files ───────────────────────────────────────────────
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/assets)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}
    COMMENT "Syncing assets/ -> build dir"
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
