#include <qtzmq.h>
#include "zmq.h"

void RegisterZMQ(void)
{
  qRegisterMetaType < QtZMQ::Endpoint > ( "QtZMQ::Endpoint" ) ;
  qRegisterMetaType < QtZMQ::Socket   > ( "QtZMQ::Socket"   ) ;
  qRegisterMetaType < QtZMQ::Context  > ( "QtZMQ::Context"  ) ;
  qRegisterMetaType < QtZMQ::Message  > ( "QtZMQ::Message"  ) ;
  qRegisterMetaType < QtZMQ::Poll     > ( "QtZMQ::Poll"     ) ;
}

BEGIN_QTZMQ_NAMESPACE

QString Version(void)
{
  int major                                                   ;
  int minor                                                   ;
  int patch                                                   ;
  ::zmq_version ( &major , &minor , &patch )                  ;
  return QString("%1.%2.%3").arg(major).arg(minor).arg(patch) ;
}

int Error(void)
{
  return ::zmq_errno ( ) ;
}

QString Error(int err)
{
  const char * p = ::zmq_strerror ( err ) ;
  if ( NULL == p ) return ""              ;
  return QString::fromUtf8        ( p   ) ;
}

bool Has(QString capability)
{
  if ( capability . length ( ) <= 0 ) return false ;
  QByteArray B = capability . toUtf8 ( )           ;
  return ::zmq_has ( B . constData ( ) )           ;
}

int Proxy(Socket & frontend,Socket & backend)
{
  return ::zmq_proxy ( frontend ( ) , backend ( ) , NULL ) ;
}

int Proxy(Socket & frontend,Socket & backend,Socket & capture)
{
  return ::zmq_proxy ( frontend ( ) , backend ( ) , capture ( ) ) ;
}

int Proxy(Socket & frontend,Socket & backend,Socket & capture,Socket & control)
{
  return ::zmq_proxy_steerable (
           frontend ( )        ,
           backend  ( )        ,
           capture  ( )        ,
           control  ( )      ) ;
}

END_QTZMQ_NAMESPACE
