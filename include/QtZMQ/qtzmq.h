/****************************************************************************
 *                                                                          *
 * Copyright (C) 2001 ~ 2016 Neutrino International Inc.                    *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_ZMQ_H
#define QT_ZMQ_H

#include <QtCore>
#include <QtNetwork>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined _WIN32_WCE
#include <errno.h>
#endif

#include <stddef.h>
#include <stdio.h>

#if defined Q_OS_WIN
#include <winsock2.h>
#endif

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTZMQ_LIB)
#      define Q_ZMQ_EXPORT Q_DECL_EXPORT
#    else
#      define Q_ZMQ_EXPORT Q_DECL_IMPORT
#    endif
#else
#      define Q_ZMQ_EXPORT
#endif

#ifndef QT_ZMQ_LIB
#define QT_ZMQ_LIB 1
#endif

#define BEGIN_SODIUM_NAMESPACE namespace Sodium   {
#define END_SODIUM_NAMESPACE                      }

#define BEGIN_OPENPGM_NAMESPACE namespace OpenPGM {
#define END_OPENPGM_NAMESPACE                     }

#define BEGIN_QTZMQ_NAMESPACE namespace QtZMQ     {
#define END_QTZMQ_NAMESPACE                       }

//////////////////////////////////////////////////////////////////////////////

BEGIN_SODIUM_NAMESPACE

Q_ZMQ_EXPORT QString Version(void) ;

END_SODIUM_NAMESPACE

//////////////////////////////////////////////////////////////////////////////

BEGIN_OPENPGM_NAMESPACE

Q_ZMQ_EXPORT QString Version(void) ;

END_OPENPGM_NAMESPACE

//////////////////////////////////////////////////////////////////////////////

BEGIN_QTZMQ_NAMESPACE

class Q_ZMQ_EXPORT Endpoint ;
class Q_ZMQ_EXPORT Socket   ;
class Q_ZMQ_EXPORT Context  ;
class Q_ZMQ_EXPORT Message  ;
class Q_ZMQ_EXPORT Poll     ;

typedef void (FreeMessage) (void * data,void * hint) ;

Q_ZMQ_EXPORT QString Version (void) ;
Q_ZMQ_EXPORT int     Error   (void) ;
Q_ZMQ_EXPORT QString Error   (int error) ;
Q_ZMQ_EXPORT bool    Has     (QString capability) ;

Q_ZMQ_EXPORT int     Proxy   (Socket & frontend   ,
                              Socket & backend  ) ;
Q_ZMQ_EXPORT int     Proxy   (Socket & frontend   ,
                              Socket & backend    ,
                              Socket & capture  ) ;
Q_ZMQ_EXPORT int     Proxy   (Socket & frontend   ,
                              Socket & backend    ,
                              Socket & capture    ,
                              Socket & control  ) ;

class Q_ZMQ_EXPORT Endpoint
{
  public:

    typedef enum {
      NONE   = 0 ,
      TCP    = 1 ,
      IPC    = 2 ,
      TIPC   = 3 ,
      INPROC = 4 ,
      NORM   = 5 ,
      PGM    = 6 ,
      EPGM   = 7 }
      Transports ;

    explicit             Endpoint     (void) ;
    explicit             Endpoint     (QString    endpoint  ) ;
    explicit             Endpoint     (int        transport   ,
                                       QString    path        ,
                                       int        port = -1 ) ;
    virtual             ~Endpoint     (void) ;

    const char *         operator ( ) (void) ;
    virtual Transports & Protocol     (void) ;
    virtual QString    & Path         (void) ;
    virtual int        & Port         (void) ;
    virtual bool         isValid      (void) ;

    virtual bool         set          (QString    endpoint  ) ;
    virtual bool         setProtocol  (int        transport ) ;
    virtual bool         setProtocol  (Transports transport ) ;
    virtual bool         setProtocol  (QString    transport ) ;
    virtual bool         setPath      (QString    hostOrPath) ;
    virtual bool         setPort      (int        port      ) ;

  protected:

    Transports transport ;
    QString    path      ;
    int        port      ;
    QByteArray body      ;

    virtual bool         Prepare      (void) ;

  private:

} ;

class Q_ZMQ_EXPORT Socket
{
  public:

    typedef enum                        {
      Pair                     =  0     ,
      Publisher                =  1     ,
      Subscriber               =  2     ,
      Client                   =  3     ,
      Service                  =  4     ,
      Dealer                   =  5     ,
      Router                   =  6     ,
      Pull                     =  7     ,
      Push                     =  8     ,
      ReceiveSubscriptions     =  9     ,
      SendSubscriptions        = 10     ,
      Stream                   = 11     }
      Types                             ;

    typedef enum                        {
      Connected                = 0x0001 ,
      ConnectDelayed           = 0x0002 ,
      ConnectRetried           = 0x0004 ,
      Listening                = 0x0008 ,
      BindFailed               = 0x0010 ,
      Accepted                 = 0x0020 ,
      AcceptFailed             = 0x0040 ,
      Closed                   = 0x0080 ,
      CloseFailed              = 0x0100 ,
      Disconnected             = 0x0200 ,
      MonitorStopped           = 0x0400 ,
      All                      = 0xFFFF }
      Events                            ;

    typedef enum                        {
      DontWait                 =  1     ,
      SendMore                 =  2     }
      Options                           ;

    typedef enum                        {
      AFFINITY                 =  4     ,
      IDENTITY                 =  5     ,
      SUBSCRIBE                =  6     ,
      UNSUBSCRIBE              =  7     ,
      RATE                     =  8     ,
      RECOVERY_IVL             =  9     ,
      SNDBUF                   = 11     ,
      RCVBUF                   = 12     ,
      RCVMORE                  = 13     ,
      FD                       = 14     ,
      EVENTS                   = 15     ,
      TYPE                     = 16     ,
      LINGER                   = 17     ,
      RECONNECT_IVL            = 18     ,
      BACKLOG                  = 19     ,
      RECONNECT_IVL_MAX        = 21     ,
      MAXMSGSIZE               = 22     ,
      SNDHWM                   = 23     ,
      RCVHWM                   = 24     ,
      MULTICAST_HOPS           = 25     ,
      RCVTIMEO                 = 27     ,
      SNDTIMEO                 = 28     ,
      LAST_ENDPOINT            = 32     ,
      ROUTER_MANDATORY         = 33     ,
      TCP_KEEPALIVE            = 34     ,
      TCP_KEEPALIVE_CNT        = 35     ,
      TCP_KEEPALIVE_IDLE       = 36     ,
      TCP_KEEPALIVE_INTVL      = 37     ,
      IMMEDIATE                = 39     ,
      XPUB_VERBOSE             = 40     ,
      ROUTER_RAW               = 41     ,
      IPV6                     = 42     ,
      MECHANISM                = 43     ,
      PLAIN_SERVER             = 44     ,
      PLAIN_USERNAME           = 45     ,
      PLAIN_PASSWORD           = 46     ,
      CURVE_SERVER             = 47     ,
      CURVE_PUBLICKEY          = 48     ,
      CURVE_SECRETKEY          = 49     ,
      CURVE_SERVERKEY          = 50     ,
      PROBE_ROUTER             = 51     ,
      REQ_CORRELATE            = 52     ,
      REQ_RELAXED              = 53     ,
      CONFLATE                 = 54     ,
      ZAP_DOMAIN               = 55     ,
      ROUTER_HANDOVER          = 56     ,
      TOS                      = 57     ,
      CONNECT_RID              = 61     ,
      GSSAPI_SERVER            = 62     ,
      GSSAPI_PRINCIPAL         = 63     ,
      GSSAPI_SERVICE_PRINCIPAL = 64     ,
      GSSAPI_PLAINTEXT         = 65     ,
      HANDSHAKE_IVL            = 66     ,
      SOCKS_PROXY              = 68     ,
      XPUB_NODROP              = 69     }
      SocketOptions                     ;

    explicit     Socket       (void) ;
    explicit     Socket       (Context & context,int type) ;
    explicit     Socket       (void * outside) ;
                 Socket       (const Socket & socket) ;
    virtual     ~Socket       (void) ;

    void *       operator ( ) (void) ;
    Socket &     operator =   (Socket & socket) ;

    virtual bool create       (Context & context,int type) ;
    virtual bool close        (void) ;

    virtual bool isCreated    (void) ;
    virtual bool isClone      (void) ;

    virtual bool bind         (Endpoint & endpoint) ;
    virtual bool unbind       (Endpoint & endpoint) ;
    virtual bool connect      (Endpoint & endpoint) ;
    virtual bool disconnect   (Endpoint & endpoint) ;
    virtual int  monitor      (Endpoint & endpoint,int    events) ;
    virtual int  monitor      (Endpoint & endpoint,Events events) ;

    virtual int  send         (const QByteArray & data,int flags = 0,bool sendconst = false) ;
    virtual int  send         (      QByteArray & data,int flags = 0,bool sendconst = false) ;
    virtual int  send         (      Message    & msg ,int flags = 0) ;
    virtual int  recv         (      QByteArray & data,int flags = 0) ;
    virtual int  recv         (      Message    & msg ,int flags = 0) ;

    virtual bool setsockopt   (int           option,const void * optval,size_t   optvallen) ;
    virtual bool setsockopt   (SocketOptions option,const void * optval,size_t   optvallen) ;
    virtual bool getsockopt   (int           option,      void * optval,size_t & optvallen) ;
    virtual bool getsockopt   (SocketOptions option,      void * optval,size_t & optvallen) ;

  protected:

    void * zmqsocket ;
    bool   created   ;

  private:

} ;

class Q_ZMQ_EXPORT Context
{
  public:

    typedef enum               {
      IoThreads            = 1 ,
      MaxSockets           = 2 ,
      SocketLimit          = 3 ,
      ThreadPriority       = 3 ,
      ThreadSchedulePolicy = 4 }
      Options                  ;

    explicit     Context      (void) ;
    virtual     ~Context      (void) ;

    void *       operator ( ) (void) ;

    virtual int  operator [ ] (int     option) ;
    virtual int  operator [ ] (Options option) ;
    virtual int  get          (int     option) ;
    virtual int  get          (Options option) ;
    virtual bool set          (int     option,int value) ;
    virtual bool set          (Options option,int value) ;

    virtual bool Shutdown     (void) ;
    virtual bool Terminate    (void) ;

  protected:

    void * context ;

  private:

} ;

class Q_ZMQ_EXPORT Message
{
  public:

    typedef enum {
      MORE   = 1 ,
      SRCFD  = 2 ,
      SHARED = 3 }
      Options    ;

    explicit        Message      (void) ;
    virtual        ~Message      (void) ;

    void *          operator ( ) (void) ;
    void *          data         (void) ;

    virtual bool    Initialize   (void) ;
    virtual bool    setSize      (size_t size) ;
    virtual size_t  size         (void) ;
    virtual bool    setData      (void        * data          ,
                                  size_t        size          ,
                                  FreeMessage * fmf  = NULL   ,
                                  void        * hint = NULL ) ;
    virtual bool    close        (void) ;

    virtual bool    more         (void) ;

    virtual int     set          (int     property,int value) ;
    virtual int     set          (Options property,int value) ;

    virtual int     get          (int     property) ;
    virtual int     get          (Options property) ;
    virtual QString get          (QString property) ;

    virtual bool    copy         (Message & message) ;
    virtual bool    move         (Message & message) ;

    virtual bool    operator =   (Message & message) ;
    virtual int     operator [ ] (int     property) ;
    virtual int     operator [ ] (Options property) ;
    virtual QString operator [ ] (QString property) ;

  protected:

    void * message     ;
    bool   initialized ;

  private:

} ;

class Q_ZMQ_EXPORT Poll
{
  public:

    typedef enum  {
      PollIn  = 1 ,
      PollOut = 2 ,
      PollErr = 4 }
      Events      ;

    explicit         Poll          (void) ;
    explicit         Poll          (int items) ;
    virtual         ~Poll          (void) ;

    virtual int      count         (void) ;
    virtual int      setItems      (int items) ;

    virtual int      poll          (int timeout = -1,int items = -1) ;

    virtual Socket   setSocket     (int index,Socket & socket) ;
    #ifdef Q_OS_WIN
    virtual SOCKET   setDescriptor (int index,SOCKET   socket) ;
    #else
    virtual int      setDescriptor (int index,int      socket) ;
    #endif
    virtual int      setEvent      (int index,int      events,bool reversal = false) ;

    virtual Socket   getSocket     (int index) ;
    #ifdef Q_OS_WIN
    virtual SOCKET   getDescriptor (int index) ;
    #else
    virtual int      getDescriptor (int index) ;
    #endif
    virtual int      getEvent      (int index,bool reversal = false) ;

  protected:

    void * items ;
    int    total ;

  private:

} ;

END_QTZMQ_NAMESPACE

Q_ZMQ_EXPORT void RegisterZMQ (void) ;

//////////////////////////////////////////////////////////////////////////////

QT_END_NAMESPACE

#endif
