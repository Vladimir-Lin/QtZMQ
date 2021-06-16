// Manipulate --js UpdateSODIUM D:\CIOS\Scripts\Softwares\Update-SODIUM.js

var url      = "www.libsodium.org" ;
var filename = "G:/Temp/sodium.html"                               ;
var lastest  = "G:/Temp/sodium-download.html"                      ;
var timeout  = 60 * 1000                                           ;
var version  = "libsodium-1.0.9.tar.gz"                            ;
var temp     = "G:/Qt/Src/QtZMQ/3rdparty/sources/"                 ;

function Fetch(url,filename,timeout)
{
  var msg                                         ;
  var r                                           ;
  mt  = new MtJS ( )                              ;
  ftp = new FTP  ( )                              ;
  msg = "下載 " + url + " 到 " + filename          ;
  mt  . toConsoleLn  ( msg                      ) ;
  r = ftp . Download ( url , filename , timeout ) ;
  delete ftp                                      ;
  delete mt                                       ;
  return r                                        ;
}

function CheckLZO()
{
  var msg                                     ;
  var lzs                                     ;
  var obs                                     ;
  var nvl                                     ;
  nvl  = false                                ;
  lzob = new ByteArray ( )                    ;
  ober = new ByteArray ( )                    ;
  if ( ! Fetch ( url , filename , timeout ) ) {
    return false                              ;
  }                                           ;
  lzob . Load ( lastest                     ) ;
  ober . Load ( filename                    ) ;
  lzs = lzob . Size ( )                       ;
  obs = ober . Size ( )                       ;
  if ( lzs !== obs )                          {
    ober . Save ( lastest            )        ;
    if ( ober . Contains ( version ) )        {
      msg = "New version : " + version        ;
      print ( msg )                           ;
      nvl = true                              ;
    }                                         ;
  }                                           ;
  delete lzob                                 ;
  delete ober                                 ;
  return nvl                                  ;
}

function UpdateSODIUM()
{
  var lzo                                  ;
  var lzf                                  ;
  if ( ! CheckLZO ( ) ) return false       ;
  lzo = url  + version                     ;
  lzf = temp + version                     ;
  return Fetch ( lzo , lzf , timeout * 4 ) ;
}
