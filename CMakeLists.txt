# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qml-i18n LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/qml/qmli18n")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml LinguistTools)

qt_add_executable(qmli18n  main.cpp)

target_link_libraries(qmli18n PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

qt_add_qml_module(qmli18n
    URI i18n
    QML_FILES
        qml-i18n.qml
    NO_RESOURCE_TARGET_PATH
)
set(QT_GLOBAL_LUPDATE_TARGET "explicit_target_lupdate")

set(TRANSLATION_SOURCES qml-i18n.qml qml-i18n.qrc)

#this not prodeuce ts files;
#qt6_add_lupdate(qmli18n SOURCES ${TRANSLATION_SOURCES}
#    TS_FILES qmli18n_base.ts NO_GLOBAL_TARGET)

# this start from qt6.7
#qt_collect_translation_source_targets(i18n_targets)
#qt_add_lupdate(SOURCE_TARGETS ${i18n_targets})

qt_add_translations(qmli18n
    TS_FILES
    i18n/base.ts
    i18n/qml_en.ts
    i18n/qml_en_AU.ts
    i18n/qml_fr.ts
    RESOURCE_PREFIX i18n/
    #QM_FILES_OUTPUT_VARIABLE qmQM_files
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
    LUPDATE_OPTIONS -no-obsolete
    LRELEASE_OPTIONS -idbased #this line is necessary for text-id-based, and .ts should describe in text-id-based also --eton@241220
)

# qt_add_translations(qmli18n
#     SOURCES ${TRANSLATION_SOURCES}
#     #RESOURCE_PREFIX /qt/qml/Translated/i18n
#     TS_FILE_BASE qml
#     TS_FILE_DIR i18n2
#     QM_FILES_OUTPUT_VARIABLE qmQM_files
# )
#install(FILES ${qmQM_files} DESTINATION ${INSTALL_EXAMPLEDIR})

install(TARGETS qmli18n
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

