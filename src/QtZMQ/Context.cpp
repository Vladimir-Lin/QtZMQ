#include <qtzmq.h>
#include "zmq.h"

BEGIN_QTZMQ_NAMESPACE

Context:: Context(void)
{
  context = ::zmq_ctx_new ( ) ;
}

Context::~Context(void)
{
  Terminate ( ) ;
}

bool Context::Shutdown (void)
{
  if ( NULL == context ) return false ;
  ::zmq_ctx_shutdown ( context )      ;
  return true                         ;
}

bool Context::Terminate (void)
{
  if ( NULL == context ) return false ;
  ::zmq_ctx_term ( context )          ;
  return true                         ;
}

bool Context::set(int option,int value)
{
  if ( NULL == context ) return false                              ;
  return ( 0 == ::zmq_ctx_set ( context ,       option , value ) ) ;
}

bool Context::set(Options option,int value)
{
  if ( NULL == context ) return false                              ;
  return ( 0 == ::zmq_ctx_set ( context , (int) option , value ) ) ;
}

int Context::get(int option)
{
  if ( NULL == context ) return -1                ;
  return ::zmq_ctx_get ( context ,       option ) ;
}

int Context::get(Options option)
{
  if ( NULL == context ) return -1                ;
  return ::zmq_ctx_get ( context , (int) option ) ;
}

int Context::operator [ ] (int option)
{
  return get ( option ) ;
}

int Context::operator [ ] (Options option)
{
  return get ( option ) ;
}

void * Context::operator ( ) (void)
{
  return context ;
}

END_QTZMQ_NAMESPACE
