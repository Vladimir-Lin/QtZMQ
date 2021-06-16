#include <qtzmq.h>
#include "zmq.h"

BEGIN_QTZMQ_NAMESPACE

Endpoint:: Endpoint  ( void )
         : transport ( NONE )
         , path      ( ""   )
         , port      ( -1   )
{
}

Endpoint:: Endpoint  ( QString endpoint )
         : transport (         NONE     )
         , path      ( ""               )
         , port      ( -1               )
{
  set ( endpoint ) ;
}

Endpoint:: Endpoint  ( int t,QString p,int o )
         : transport ( (Transports) t        )
         , path      ( p                     )
         , port      ( o                     )
{
  Prepare ( ) ;
}

Endpoint::~Endpoint(void)
{
}

const char * Endpoint::operator ( ) (void)
{
  if ( body . size ( ) <= 0 ) return NULL ;
  return body . constData ( )             ;
}

Endpoint::Transports & Endpoint::Protocol(void)
{
  return transport ;
}

QString & Endpoint::Path(void)
{
  return path ;
}

int & Endpoint::Port(void)
{
  return port ;
}

bool Endpoint::isValid(void)
{
  if ( path . length ( ) <= 0 ) return false ;
  ////////////////////////////////////////////
  switch ( transport )                       {
    case NONE                                :
    return false                             ;
    case TCP                                 :
    case PGM                                 :
    case EPGM                                :
      if ( port < 0 ) return false           ;
    break                                    ;
    case IPC                                 :
    case TIPC                                :
    case INPROC                              :
    case NORM                                :
    break                                    ;
  }                                          ;
  ////////////////////////////////////////////
  return true                                ;
}

bool Endpoint::set(QString endpoint)
{
  if ( ! endpoint . contains ( "://" ) ) return false ;
  QStringList R = endpoint . split ( "://" )          ;
  if ( 2 != R . count ( )              ) return false ;
  QString p = R [ 0 ]                                 ;
  QString l = R [ 1 ]                                 ;
  if ( p . length ( ) <= 0             ) return false ;
  if ( l . length ( ) <= 0             ) return false ;
  /////////////////////////////////////////////////////
  setProtocol    ( p )                                ;
  /////////////////////////////////////////////////////
  switch ( transport )                                {
    case NONE                                         :
    return false                                      ;
    case TCP                                          :
    case PGM                                          :
    case EPGM                                         :
      R = l . split ( ":" )                           ;
      if ( 2 != R . count ( )          ) return false ;
      p = R [ 0 ]                                     ;
      l = R [ 1 ]                                     ;
      if ( p . length ( ) <= 0         ) return false ;
      if ( l . length ( ) <= 0         ) return false ;
      setPath    ( p             )                    ;
      setPort    ( l . toInt ( ) )                    ;
    break                                             ;
    case IPC                                          :
    case TIPC                                         :
    case INPROC                                       :
    case NORM                                         :
      setPath    ( l             )                    ;
    break                                             ;
  }                                                   ;
  /////////////////////////////////////////////////////
  return Prepare (               )                    ;
}

bool Endpoint::setProtocol(int t)
{
  transport = (Transports) t ;
  return Prepare ( )         ;
}

bool Endpoint::setProtocol(Transports t)
{
  transport = t      ;
  return Prepare ( ) ;
}

bool Endpoint::setProtocol(QString t)
{
  t         = t . toLower ( )             ;
  transport = NONE                        ;
  if ( "tcp"    == t ) transport = TCP    ;
  if ( "ipc"    == t ) transport = IPC    ;
  if ( "tipc"   == t ) transport = TIPC   ;
  if ( "inproc" == t ) transport = INPROC ;
  if ( "norm"   == t ) transport = NORM   ;
  if ( "pgm"    == t ) transport = PGM    ;
  if ( "epgm"   == t ) transport = EPGM   ;
  return Prepare ( )                      ;
}

bool Endpoint::setPath(QString hostOrPath)
{
  path = hostOrPath  ;
  return Prepare ( ) ;
}

bool Endpoint::setPort(int p)
{
  port = p           ;
  return Prepare ( ) ;
}

bool Endpoint::Prepare(void)
{
  QString fn = 0                                                    ;
  body . clear ( )                                                  ;
  ///////////////////////////////////////////////////////////////////
  if ( path . length ( ) <= 0 ) return false                        ;
  ///////////////////////////////////////////////////////////////////
  switch ( transport )                                              {
    case NONE                                                       :
    return false                                                    ;
    case TCP                                                        :
      if ( port < 0 ) return false                                  ;
      fn = QString ( "tcp://%1:%2"  ) . arg ( path ) . arg ( port ) ;
    break                                                           ;
    case IPC                                                        :
      fn = QString ( "ipc://%1"     ) . arg ( path )                ;
    break                                                           ;
    case TIPC                                                       :
      fn = QString ( "tipc://%1"    ) . arg ( path )                ;
    break                                                           ;
    case INPROC                                                     :
      fn = QString ( "inproc://%1"  ) . arg ( path )                ;
    break                                                           ;
    case NORM                                                       :
      fn = QString ( "norm://%1"    ) . arg ( path )                ;
    break                                                           ;
    case PGM                                                        :
      if ( port < 0 ) return false                                  ;
      fn = QString ( "pgm://%1:%2"  ) . arg ( path ) . arg ( port ) ;
    break                                                           ;
    case EPGM                                                       :
      if ( port < 0 ) return false                                  ;
      fn = QString ( "epgm://%1:%2" ) . arg ( path ) . arg ( port ) ;
    break                                                           ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  body = fn . toUtf8 ( )                                            ;
  ///////////////////////////////////////////////////////////////////
  return true                                                       ;
}

END_QTZMQ_NAMESPACE
