// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

class LanguageManager : public QObject {
  Q_OBJECT
public:
  LanguageManager(QQmlApplicationEngine *engine, QObject *parent = nullptr) : QObject(parent), m_engine(engine) {}

public slots:
  Q_INVOKABLE void changeLanguage(const QString &locale, const QString &translationFile) {
    // Set the new locale
    QLocale regionlocal = QLocale(locale);
    QLocale::setDefault(regionlocal);
    qDebug() << "local Name=" << regionlocal.name();

    // Load the new translation file
    QTranslator translator;
    if (false == translator.load(translationFile)) {
      qDebug() << "local file Err: Name=" << translationFile;
    } else {
      qDebug() << "translator:" << translator.language();
      bool ret = qApp->installTranslator(&translator);
      qDebug() << "installTranslator=" << ret;
    }
    m_engine->retranslate();

    // Emit a signal to update the QML UI
    emit languageChanged(locale, translationFile);
  }

signals:
  void languageChanged(const QString, const QString);

private:
  QQmlApplicationEngine *m_engine;
};

#include "main.moc"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::China));
  QLocale::setDefault(QLocale(QLocale::French, QLocale::France));

  QGuiApplication app(argc, argv);

  // Load translations if needed, not need, `QLocale::setDefault` is necessary. --eton@241218
  QTranslator translator;
  if (translator.load("qml_fr.qm")) {
    bool ret = app.installTranslator(&translator);
    qDebug() << translator.language() << ",installTranslator=" << ret;
  }
  if (translator.load("qml_en.qm")) {
    bool ret = app.installTranslator(&translator);
    qDebug() << translator.language() << ",installTranslator=" << ret;
  }

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/qml-i18n.qml"));

  LanguageManager languageManager(&engine);

  // Expose the LanguageManager instance to QML
  engine.rootContext()->setContextProperty("languageManager", &languageManager);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
