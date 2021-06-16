#include <qtzmq.h>
#include "zmq.h"

BEGIN_QTZMQ_NAMESPACE

Message:: Message(void)
{
  message     = (void *) ::malloc ( sizeof(zmq_msg_t) ) ;
  initialized = true                                    ;
  ::zmq_msg_init ( (zmq_msg_t *) message )              ;
}

Message::~Message(void)
{
  if ( NULL != message ) {
    close  (         )   ;
    ::free ( message )   ;
  }                      ;
  message = NULL         ;
}

void * Message::operator ( ) (void)
{
  return message ;
}

void * Message::data(void)
{
  if ( NULL == message ) return NULL              ;
  if ( ! initialized   ) return NULL              ;
  return ::zmq_msg_data ( (zmq_msg_t *) message ) ;
}

bool Message::Initialize(void)
{
  if ( NULL == message ) return false      ;
  if ( initialized     ) return true       ;
  initialized = true                       ;
  ::zmq_msg_init ( (zmq_msg_t *) message ) ;
  return true                              ;
}

bool Message::setSize(size_t size)
{
  if ( NULL == message ) return false                               ;
  bool c                                                            ;
  c = ( 0 == ::zmq_msg_init_size ( (zmq_msg_t *) message , size ) ) ;
  initialized = c                                                   ;
  return c                                                          ;
}

size_t Message::size(void)
{
  if ( NULL == message ) return 0                 ;
  if ( ! initialized   ) return 0                 ;
  return ::zmq_msg_size ( (zmq_msg_t *) message ) ;
}

bool Message::setData     (
       void        * data ,
       size_t        size ,
       FreeMessage * fmf  ,
       void        * hint )
{
  if ( NULL == message ) return false ;
  if ( ! initialized   ) return false ;
  int r                               ;
  r = ::zmq_msg_init_data             (
        (zmq_msg_t *) message         ,
        data                          ,
        size                          ,
        (zmq_free_fn *) fmf           ,
        hint                        ) ;
  return ( 0 == r )                   ;
}

bool Message::close(void)
{
  if ( NULL == message ) return false                         ;
  bool c = ( 0 == ::zmq_msg_close ( (zmq_msg_t *) message ) ) ;
  initialized = false                                         ;
  return c                                                    ;
}

bool Message::more(void)
{
  if ( NULL == message ) return false                     ;
  if ( ! initialized   ) return false                     ;
  return ( ::zmq_msg_more ( (zmq_msg_t *) message ) > 0 ) ;
}

bool Message::copy(Message & msg)
{
  if ( NULL ==       message ) return false          ;
  if ( !       initialized   ) return false          ;
  if ( NULL == msg . message ) return false          ;
  if ( ! msg . initialized   ) return false          ;
  int r                                              ;
  r = ::zmq_msg_copy ( (zmq_msg_t *)       message   ,
                       (zmq_msg_t *) msg . message ) ;
  return ( 0 == r )                                  ;
}

bool Message::move(Message & msg)
{
  if ( NULL ==       message ) return false          ;
  if ( !       initialized   ) return false          ;
  if ( NULL == msg . message ) return false          ;
  if ( ! msg . initialized   ) return false          ;
  int r                                              ;
  r = ::zmq_msg_move ( (zmq_msg_t *)       message   ,
                       (zmq_msg_t *) msg . message ) ;
  return ( 0 == r )                                  ;
}

bool Message::operator = (Message & msg)
{
  return copy ( msg ) ;
}

int Message::set(int property,int value)
{
  if ( NULL == message ) return -1                                  ;
  if ( ! initialized   ) return -1                                  ;
  return ::zmq_msg_set ( (zmq_msg_t *) message , property , value ) ;
}

int Message::set(Options property,int value)
{
  if ( NULL == message ) return -1                                        ;
  if ( ! initialized   ) return -1                                        ;
  return ::zmq_msg_set ( (zmq_msg_t *) message , (int) property , value ) ;
}

int Message::get(int property)
{
  if ( NULL == message ) return -1                          ;
  if ( ! initialized   ) return -1                          ;
  return ::zmq_msg_get ( (zmq_msg_t *) message , property ) ;
}

int Message::get(Options property)
{
  if ( NULL == message ) return -1                                ;
  if ( ! initialized   ) return -1                                ;
  return ::zmq_msg_get ( (zmq_msg_t *) message , (int) property ) ;
}

QString Message::get(QString property)
{
  if ( property . length ( ) <= 0 ) return ""                      ;
  QByteArray   B = property . toUtf8 ( )                           ;
  const char * c                                                   ;
  c = ::zmq_msg_gets ( (zmq_msg_t *) message , B . constData ( ) ) ;
  if ( NULL == c ) return ""                                       ;
  return QString::fromUtf8 ( c )                                   ;
}

int Message::operator [ ] (int property)
{
  return get ( property ) ;
}

int Message::operator [ ] (Options property)
{
  return get ( property ) ;
}

QString Message::operator [ ] (QString property)
{
  return get ( property ) ;
}

END_QTZMQ_NAMESPACE
