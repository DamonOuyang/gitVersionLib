TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    nlsSpeech-release/demo/asr-demo.cpp \
    nlsSpeech-release/demo/nlu-demo.cpp \
    nlsSpeech-release/demo/realtime-demo.cpp \
    nlsSpeech-release/demo/tts-demo.cpp

HEADERS += \
    nlsSpeech-release/demo/NlsClient.h
