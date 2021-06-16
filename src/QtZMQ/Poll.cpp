#include <qtzmq.h>
#include "zmq.h"

BEGIN_QTZMQ_NAMESPACE

Poll:: Poll  ( void )
     : items ( NULL )
     , total ( 0    )
{
  setItems ( 1 ) ;
}

Poll:: Poll  ( int t )
     : items ( NULL  )
     , total ( 0     )
{
  setItems ( t ) ;
}

Poll::~Poll (void)
{
  if ( NULL != items ) {
    ::free ( items )   ;
  }                    ;
  items = NULL         ;
  total = 0            ;
}

int Poll::count(void)
{
  return total ;
}

int Poll::setItems(int t)
{
  if ( t <= 0                  ) t = 1                             ;
  if ( t >  ZMQ_POLLITEMS_DFLT ) t = ZMQ_POLLITEMS_DFLT            ;
  zmq_pollitem_t * opi = (zmq_pollitem_t *) items                  ;
  zmq_pollitem_t * zpi                                             ;
  zpi = (zmq_pollitem_t *) ::malloc ( sizeof(zmq_pollitem_t) * t ) ;
  items = NULL                                                     ;
  total = 0                                                        ;
  if ( NULL != opi ) ::free ( opi )                                ;
  if ( NULL != zpi )                                               {
    items = zpi                                                    ;
    total = t                                                      ;
    ::memset ( zpi , 0 , sizeof(zmq_pollitem_t) * t )              ;
  }                                                                ;
  return total                                                     ;
}

int Poll::poll(int timeout,int t)
{
  if ( t    <= 0                  ) t = total              ;
  if ( t    >  total              ) t = total              ;
  if ( t    >  ZMQ_POLLITEMS_DFLT ) t = ZMQ_POLLITEMS_DFLT ;
  if ( NULL == items              ) return -1              ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items          ;
  return ::zmq_poll ( zpi , t , timeout )                  ;
}

Socket Poll::setSocket (int i,Socket & s)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) {
    Socket r                                             ;
    return r                                             ;
  }                                                      ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items        ;
  zpi [ i ] . socket = s ( )                             ;
  return Socket ( zpi [ i ] . socket )                   ;
}

#ifdef Q_OS_WIN

SOCKET Poll::setDescriptor (int i,SOCKET s)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) return -1 ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items                  ;
  zpi [ i ] . fd = s                                               ;
  return zpi [ i ] . fd                                            ;
}

#else

int Poll::setDescriptor(int i,int s)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) return -1 ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items                  ;
  zpi [ i ] . fd = s                                               ;
  return zpi [ i ] . fd                                            ;
}

#endif

int Poll::setEvent(int i,int e,bool r)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) return -1 ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items                  ;
  if ( r ) zpi [ i ] . revents = e                                 ;
      else zpi [ i ] . events  = e                                 ;
  return r ? (int) zpi [ i ] . revents : (int) zpi [ i ] . events  ;
}

Socket Poll::getSocket (int i)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) {
    Socket r                                             ;
    return r                                             ;
  }                                                      ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items        ;
  return Socket ( zpi [ i ] . socket )                   ;
}

#ifdef Q_OS_WIN

SOCKET Poll::getDescriptor (int i)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) return -1 ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items                  ;
  return zpi [ i ] . fd                                            ;
}

#else

int Poll::getDescriptor(int i)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) return -1 ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items                  ;
  return zpi [ i ] . fd                                            ;
}

#endif

int Poll::getEvent(int i,bool r)
{
  if ( ( i < 0 ) || ( i >= total ) || ( NULL == items )) return -1 ;
  zmq_pollitem_t * zpi = (zmq_pollitem_t *) items                  ;
  return r ? (int) zpi [ i ] . revents : (int) zpi [ i ] . events  ;
}

END_QTZMQ_NAMESPACE
