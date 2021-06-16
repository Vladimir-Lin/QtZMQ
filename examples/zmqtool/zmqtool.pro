QT             = core
QT            -= gui
QT            += QtZMQ

CONFIG(debug, debug|release) {
TARGET         = zmqtoold
} else {
TARGET         = zmqtool
}

CONFIG        += console

TEMPLATE       = app

SOURCES       += $${PWD}/zmqtool.cpp

win32 {
RC_FILE        = $${PWD}/zmqtool.rc
OTHER_FILES   += $${PWD}/zmqtool.rc
OTHER_FILES   += $${PWD}/*.js
OTHER_FILES   += $${PWD}/../../include/QtZMQ/qtzmq.h
}

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
