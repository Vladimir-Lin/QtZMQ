#include <qtzmq.h>
#include "sodium.h"

BEGIN_SODIUM_NAMESPACE

QString Version(void)
{
  const char * svs = sodium_version_string ( ) ;
  if ( NULL == svs ) return ""                 ;
  return QString::fromUtf8 ( svs )             ;
}

END_SODIUM_NAMESPACE
