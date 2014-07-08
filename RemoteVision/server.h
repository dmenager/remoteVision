#ifndef __SERVER_H__
#define __SERVER_H__


#include <fstream>
#include <iostream>           // For cout, cerr
#include <cstdlib>            // For atoi()
#include <pthread.h>          // For POSIX threads
#include <string.h>
#include <vector>

#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include <alcommon/alproxy.h>
#include <almath/types/alposition6d.h>

#include <qi/log.hpp>

#include <alproxies/almemoryproxy.h>
#include <alproxies/allaserproxy.h>

#include <althread/alcriticalsection.h>
#include <althread/almutex.h>

#include <alerror/alerror.h>

#include <boost/shared_ptr.hpp>

#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include "dmfunctions.h"

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

class server : public AL::ALModule
{
  public:
    server(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);

    virtual ~server();
    virtual void init();
    static void HandleTCPClient(TCPSocket *sock);
    static void *ThreadMain(void *arg);
    void *listen();

   private:
    TCPSocket *clntSock;
    boost::shared_ptr<AL::ALMutex> fCallbackMutex;
    static DMFunctions* dm;

};



#endif
