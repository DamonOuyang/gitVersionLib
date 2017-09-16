TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    nlsSpeech-release/demo/asr-demo.cpp

HEADERS += \
    nlsSpeech-release/demo/NlsClient.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/release/ -llibeay32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/debug/ -llibeay32
else:unix: LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/ -llibeay32

INCLUDEPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug
DEPENDPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/release/ -lopusd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/debug/ -lopusd
else:unix: LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/ -lopusd

INCLUDEPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug
DEPENDPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/release/ -lrealTimeSdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/debug/ -lrealTimeSdk
else:unix: LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/ -lrealTimeSdk

INCLUDEPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug
DEPENDPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/release/ -lssleay32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/debug/ -lssleay32
else:unix: LIBS += -L$$PWD/nlsSpeech-release/lib/win/x64/ -lssleay32

INCLUDEPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug
DEPENDPATH += $$PWD/nlsSpeech-release/lib/win/x64/Debug
