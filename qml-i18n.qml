// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    visible: true
    width: 640
    height: 480

    Column {
        anchors.fill: parent
        spacing: 20

        Text {
            text: "If a translation is available for the system language (eg. French) then the "
                  + "string below will be translated (eg. 'Bonjour'). Otherwise it will show 'Hello'."
            width: parent.width
            wrapMode: Text.WordWrap
        }

        Text {
            //% "text-ID-based for id-Hello"
            text: qsTrId("Hello")
            font.pointSize: 25
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            //% "text-ID-based for id-English"
            text: qsTrId("English")
            onClicked: {
                languageManager.changeLanguage("en_US", "qml_en.qm")
            }
        }

        Button {
            //% "text-ID-based for id-French"
            text: qsTrId("id-French")
            onClicked: {
                languageManager.changeLanguage("fr_FR", "qml_fr.qm")
            }
        }
    }
}
