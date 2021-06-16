#include <qtzmq.h>
#include "zmq.h"

BEGIN_QTZMQ_NAMESPACE

Socket:: Socket    ( void  )
       : zmqsocket ( NULL  )
       , created   ( false )
{
}

Socket:: Socket    ( Context & c , int t )
       : zmqsocket ( NULL                )
       , created   ( false               )
{
  create ( c , t ) ;
}

Socket:: Socket    ( void * outside  )
       : zmqsocket (        outside  )
       , created   ( false           )
{
}

Socket:: Socket    ( const Socket & s )
       : zmqsocket ( s . zmqsocket    )
       , created   ( false            )
{
}

Socket::~Socket (void)
{
  close ( ) ;
}

void * Socket::operator ( ) (void)
{
  return zmqsocket ;
}

Socket & Socket::operator = (Socket & s)
{
  close  (     )            ;
  zmqsocket = s . zmqsocket ;
  created   = false         ;
  return (*this)            ;
}

bool Socket::create(Context & context,int type)
{
  close                    (                    ) ;
  zmqsocket = ::zmq_socket ( context ( ) , type ) ;
  created =                ( NULL != zmqsocket  ) ;
  return created                                  ;
}

bool Socket::close(void)
{
  if ( NULL == zmqsocket ) return false ;
  int r                                 ;
  if ( ! created )                      {
    r = 1                               ;
  } else                                {
    r = ::zmq_close ( zmqsocket )       ;
  }                                     ;
  zmqsocket = NULL                      ;
  created   = false                     ;
  return ( r >= 0 )                     ;
}

bool Socket::isCreated(void)
{
  if ( NULL == zmqsocket ) return false ;
  return created                        ;
}

bool Socket::isClone(void)
{
  if ( NULL == zmqsocket ) return false ;
  return ! created                      ;
}

bool Socket::bind(Endpoint & p)
{
  if ( NULL == zmqsocket ) return false            ;
  if ( ! p . isValid ( ) ) return false            ;
  return ( 0 == ::zmq_bind ( zmqsocket , p ( ) ) ) ;
}

bool Socket::unbind(Endpoint & p)
{
  if ( NULL == zmqsocket ) return false              ;
  if ( ! p . isValid ( ) ) return false              ;
  return ( 0 == ::zmq_unbind ( zmqsocket , p ( ) ) ) ;
}

bool Socket::connect(Endpoint & p)
{
  if ( NULL == zmqsocket ) return false               ;
  if ( ! p . isValid ( ) ) return false               ;
  return ( 0 == ::zmq_connect ( zmqsocket , p ( ) ) ) ;
}

bool Socket::disconnect(Endpoint & p)
{
  if ( NULL == zmqsocket ) return false                  ;
  if ( ! p . isValid ( ) ) return false                  ;
  return ( 0 == ::zmq_disconnect ( zmqsocket , p ( ) ) ) ;
}

int Socket::monitor(Endpoint & p,int e)
{
  if ( NULL == zmqsocket ) return -1                    ;
  if ( ! p . isValid ( ) ) return -1                    ;
  return ::zmq_socket_monitor ( zmqsocket , p ( ) , e ) ;
}

int Socket::monitor(Endpoint & p,Events e)
{
  if ( NULL == zmqsocket ) return -1                          ;
  if ( ! p . isValid ( ) ) return -1                          ;
  return ::zmq_socket_monitor ( zmqsocket , p ( ) , (int) e ) ;
}

int Socket::send(const QByteArray & d,int f,bool s)
{
  if ( NULL == zmqsocket ) return -1                             ;
  if ( d . size ( ) <= 0 ) return -1                             ;
  size_t       len =                d . size      ( )            ;
  const void * buf = (const void *) d . constData ( )            ;
  if ( s ) return ::zmq_send_const ( zmqsocket , buf , len , f ) ;
  return          ::zmq_send       ( zmqsocket , buf , len , f ) ;
}

int Socket::send(QByteArray & d,int f,bool s)
{
  if ( NULL == zmqsocket ) return -1                             ;
  if ( d . size ( ) <= 0 ) return -1                             ;
  size_t       len =                d . size      ( )            ;
  const void * buf = (const void *) d . constData ( )            ;
  if ( s ) return ::zmq_send_const ( zmqsocket , buf , len , f ) ;
  return          ::zmq_send       ( zmqsocket , buf , len , f ) ;
}

int Socket::send(Message & msg,int flags)
{
  if ( NULL == zmqsocket ) return -1                                  ;
  return ::zmq_msg_send ( (zmq_msg_t *) msg ( ) , zmqsocket , flags ) ;
}

int Socket::recv(Message & msg,int flags)
{
  if ( NULL == zmqsocket ) return -1                                  ;
  return ::zmq_msg_recv ( (zmq_msg_t *) msg ( ) , zmqsocket , flags ) ;
}

int Socket::recv(QByteArray & d,int f)
{
  if ( NULL == zmqsocket ) return -1              ;
  if ( d . size ( ) <= 0 ) return -1              ;
  size_t len =          d . size ( )              ;
  void * buf = (void *) d . data ( )              ;
  return ::zmq_recv ( zmqsocket , buf , len , f ) ;
}

bool Socket::setsockopt(int opt,const void * v,size_t len)
{
  if ( NULL == zmqsocket ) return false                                ;
  return ( 0 == ::zmq_setsockopt ( zmqsocket ,       opt , v , len ) ) ;
}

bool Socket::setsockopt(SocketOptions opt,const void * v,size_t len)
{
  if ( NULL == zmqsocket ) return false                                ;
  return ( 0 == ::zmq_setsockopt ( zmqsocket , (int) opt , v , len ) ) ;
}

bool Socket::getsockopt(int opt,void * v,size_t & len)
{
  if ( NULL == zmqsocket ) return false                                 ;
  return ( 0 == ::zmq_getsockopt ( zmqsocket ,       opt , v , &len ) ) ;
}

bool Socket::getsockopt(SocketOptions opt,void * v,size_t & len)
{
  if ( NULL == zmqsocket ) return false                                 ;
  return ( 0 == ::zmq_getsockopt ( zmqsocket , (int) opt , v , &len ) ) ;
}

END_QTZMQ_NAMESPACE
