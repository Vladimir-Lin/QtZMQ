NAME         = QtZMQ
TARGET       = $${NAME}
QT           = core
QT          -= gui
QT          -= script
QT          += network

load(qt_build_config)
load(qt_module)

CONFIG(static,static|shared) {
DEFINES     += ZMQ_STATIC
DEFINES     += SODIUM_STATIC
}

INCLUDEPATH += $${PWD}/../../include/QtZMQ
INCLUDEPATH += $${PWD}/../../include/QtZMQ/sodium
INCLUDEPATH += $${PWD}/../../include/QtZMQ/pgm
INCLUDEPATH += $${PWD}/../../include/QtZMQ/zmq

HEADERS     += $${PWD}/../../include/QtZMQ/qtzmq.h
HEADERS     += $${PWD}/../../include/QtZMQ/zmq/*
HEADERS     += $${PWD}/../../include/QtZMQ/sodium/*
HEADERS     += $${PWD}/../../include/QtZMQ/sodium/sodium/*
HEADERS     += $${PWD}/../../include/QtZMQ/pgm/*

SOURCES     += $${PWD}/nZMQ.cpp
SOURCES     += $${PWD}/Endpoint.cpp
SOURCES     += $${PWD}/Context.cpp
SOURCES     += $${PWD}/Socket.cpp
SOURCES     += $${PWD}/Message.cpp
SOURCES     += $${PWD}/Poll.cpp

include ($${PWD}/Sodium/Sodium.pri)
include ($${PWD}/OpenPGM/OpenPGM.pri)

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

win32 {

SODIUMLIB    = libsodium
PGMLIB       = libpgm
ZMQLIB       = libzmq

CONFIG(debug, debug|release) {

  LIBS      += -l$${SODIUMLIB}d
  LIBS      += -l$${PGMLIB}d
  LIBS      += -l$${ZMQLIB}d

} else {

  LIBS      += -l$${SODIUMLIB}
  LIBS      += -l$${PGMLIB}
  LIBS      += -l$${ZMQLIB}

}

}
