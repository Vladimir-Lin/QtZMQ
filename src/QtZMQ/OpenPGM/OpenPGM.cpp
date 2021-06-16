#include <qtzmq.h>
#include "pgm.h"

BEGIN_OPENPGM_NAMESPACE

QString Version(void)
{
  int major = (int) pgm_major_version                         ;
  int minor = (int) pgm_minor_version                         ;
  int patch = (int) pgm_micro_version                         ;
  return QString("%1.%2.%3").arg(major).arg(minor).arg(patch) ;
}

END_OPENPGM_NAMESPACE
