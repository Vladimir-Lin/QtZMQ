#include <QtCore>
#include <QtZMQ>

void nprintf(QString message,bool lf,bool cr)
{
  QTextCodec * codec = QTextCodec::codecForLocale() ;
  QByteArray   M     = codec->fromUnicode(message)  ;
  int          L     = M . size ( )                 ;
  ///////////////////////////////////////////////////
  if ( L <= 0 )                                     {
    if (lf || cr)                                   {
      char f [ 64 ]                                 ;
      ::strcpy         ( f    , ""    )             ;
      if (cr) ::strcat ( f    , "\r"  )             ;
      if (lf) ::strcat ( f    , "\n"  )             ;
      ::printf         ( "%s" , f     )             ;
    }                                               ;
    return                                          ;
  }                                                 ;
  ///////////////////////////////////////////////////
  char * p = new char[L+16]                         ;
  memset   ( p , 0        , L+16 )                  ;
  memcpy   ( p , M.data() , L    )                  ;
  if (lf || cr)                                     {
    char f [ 64 ]                                   ;
    ::strcpy         ( f , ""      )                ;
    if (cr) ::strcat ( f , "\r"    )                ;
    if (lf) ::strcat ( f , "\n"    )                ;
    ::strcat         ( p , f       )                ;
  }                                                 ;
  ::printf           ( "%s" , p    )                ;
  delete [] p                                       ;
}

QStringList ToArgs(int argc,char ** argv)
{
  QTextCodec * codec = QTextCodec::codecForLocale ( ) ;
  QStringList  s                                      ;
  for (int i = 0 ; i < argc ; i++ )                   {
    s << codec -> toUnicode ( argv [ i ] )            ;
  }                                                   ;
  return s                                            ;
}

void BindAsServer (int port)
{
  QtZMQ::Endpoint bh  ( QtZMQ::Endpoint::TCP , "*" , port ) ;
  QtZMQ::Context  ctx                                       ;
  QtZMQ::Socket   slc ( ctx , QtZMQ::Socket::Service      ) ;
  int             rc = slc . bind ( bh )                    ;
  QByteArray      data                                      ;
  QByteArray      hello                                     ;
  QString         world = QString ( "World" )               ;
  hello = world . toUtf8 ( )                                ;
  data . resize ( 10 )                                      ;
  while ( true )                                            {
    data . fill ( 0 )                                       ;
    rc = slc . recv ( data )                                ;
    printf ( "Received Hello : %d => %s\n",rc,data.data() ) ;
    ::Sleep ( 100 )                                         ;
    slc . send ( hello )                                    ;
  }
}

void ActAsClient(QString host,int port)
{
  QtZMQ::Endpoint ep  ( QtZMQ::Endpoint::TCP , host , port ) ;
  QtZMQ::Context  ctx                                        ;
  QtZMQ::Socket   skt ( ctx , QtZMQ::Socket::Client        ) ;
  int             request_nbr                                ;
  QByteArray      data                                       ;
  QByteArray      hello                                      ;
  QString         world = "Hello"                            ;
  int             rc                                         ;
  ////////////////////////////////////////////////////////////
  hello = world . toUtf8 ( )                                 ;
  data  . resize ( 10 )                                      ;
  printf ( "Connecting to hello world server\n" )            ;
  skt . connect ( ep )                                       ;
  for (request_nbr = 0; request_nbr != 10; request_nbr++)    {
    printf ("Sending Hello (%d)\n", request_nbr)             ;
    skt      . send ( hello )                                ;
    data     . fill ( 0     )                                ;
    rc = skt . recv ( data  )                                ;
    printf ("Received World %d => %s\n", request_nbr,data.data()) ;
  }                                                          ;
  skt . close ( )                                            ;
}

void Help (void)
{
  nprintf ( QString("zmqtool -b : bind as server") , true , true ) ;
  nprintf ( QString("zmqtool -c : act as client" ) , true , true ) ;
}

int Interpret(QStringList cmds)
{
  if ( cmds . count ( ) < 2 )          {
    Help ( )                           ;
    return 1                           ;
  }                                    ;
  int     ioa  = -1                    ;
  int     port = 5555                  ;
  QString host = "localhost"           ;
  //////////////////////////////////////
  cmds . takeAt ( 0 )                  ;
  if ( "-b" == cmds [ 0 ] )            {
    ioa = 1                            ;
  }                                    ;
  if ( "-c" == cmds [ 0 ] )            {
    ioa = 2                            ;
  }                                    ;
  if ( ( ioa < 1 ) || ( ioa > 2 ) )    {
    Help ( )                           ;
    return 1                           ;
  }                                    ;
  //////////////////////////////////////
  int i = 0                            ;
  while (  i < cmds . count ( ) )      {
    if ( "-h" == cmds [ i ] )          {
      i++                              ;
      if ( i < cmds . count ( ) )      {
        host = cmds [ i ]              ;
        i++                            ;
      }                                ;
    } else i++                         ;
  }                                    ;
  //////////////////////////////////////
  switch ( ioa )                       {
    case 1                             :
      BindAsServer (        port )     ;
    return 0                           ;
    case 2                             :
      ActAsClient  ( host , port )     ;
    return 0                           ;
    case 3                             :
    break                              ;
  }                                    ;
  //////////////////////////////////////
  Help ( )                             ;
  return 1                             ;
}

int main(int argc,char ** argv)
{
  QStringList      args = ToArgs ( argc , argv ) ;
  QCoreApplication core          ( argc , argv ) ;
  return Interpret               ( args        ) ;
}
