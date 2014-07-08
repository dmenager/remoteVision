/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "server.h"
#include "urg/UrgCtrl.h"
#include "urg/Angle.h"
#include <alproxies/altexttospeechproxy.h>
#include "avcaptureremote.h"


using namespace AL;

boost::shared_ptr<AL::ALBroker> brokerInst;\

DMFunctions* server::dm = new DMFunctions();

server::server(boost::shared_ptr<ALBroker> broker, const std::string& name):
    ALModule(broker, name),fCallbackMutex(AL::ALMutex::createALMutex())
{
  /** Describe the module here. This will appear on the webpage*/
  setModuleDescription("Handles ..");

  /** Define callable methods with their descriptions:
  * This makes the method available to other cpp modules
  * and to python.
  * The name given will be the one visible from outside the module.
  * This method has no parameters or return value to describe
  */
  functionName("stringToCharS", getName(), "Say a given sentence.");
  functionName("HandleTCPClient", getName(), "Moves its head");
  functionName("ThreadMain", getName(), "Stans up");
  functionName("listen", getName(), "Method called when the right bumper is pressed. Makes a LED animation.");
  BIND_METHOD(server::listen);
}


server::~server() {delete dm;}

using namespace std;

void server::init()
{
    try{
    brokerInst=getParentBroker();
    getParentBroker()->getProxy(getName())->pCall("listen");
    }
    catch (const AL::ALError& e) {
      std::cout<<e.what()<<std::endl;
    }


}

char* stringToCharS(string text)
{
    char *a=new char[text.size()+1];
    a[text.size()]=0;
    memcpy(a,text.c_str(),text.size());
    return a;
}

string tostring(int number){
    string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
            default :ones_char = '9';
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}

string floatToStr(float val)
{
  stringstream ss (stringstream::in | stringstream::out);
  ss << val;
  string test = ss.str();
  return test;
}

void server::HandleTCPClient(TCPSocket *sock) {

  AL::ALTextToSpeechProxy* voice = new ALTextToSpeechProxy(brokerInst);

  const int RCVBUFSIZE = 32;

  cout << "Handling client ";
  try {
    cout << sock->getForeignAddress() << ":";
  } catch (SocketException &e) {
    cerr << "Unable to get foreign address" << endl;
  }
  try {
    cout << sock->getForeignPort();
  } catch (SocketException &e) {
    cerr << "Unable to get foreign port" << endl;
  }
  cout << " with thread " << pthread_self() << endl;

  // Send received string and receive again until the end of transmission
  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize;

  recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE);

   std::vector<char> v(echoBuffer,echoBuffer+recvMsgSize);
   std::string theStr;

   for(unsigned int i=0;i<v.size();i++)
   {
     if(v[i]<32 || v[i]>=0x7f);//Remove non-ascii char
     else theStr.insert(theStr.end(),v[i]);
   }

   if (theStr == "recognize")
   {
       //call function
       //nao na(brokerInst,"nao");

       //AVCaptureRemote av(brokerInst,"AVCaptureRemote");
       cout << "here\n";
       int ans = dm->DisplayVid(AVCaptureRemote::lImage);
       cout << "made it\n";

       if(ans == 0)
       {
           voice->say("zero");
       }
       else if(ans == 1)
       {
           voice->say("one");
       }
       else if(ans == 2)
       {
           voice->say("two");
       }
       else if(ans == 3)
       {
           voice->say("three");
       }
       else if(ans == 4)
       {
           voice->say("four");
       }
       else if(ans == 5)
       {
           voice->say("five");
       }
       else if(ans == 6)
       {
           voice->say("six");
       }
       else if(ans == 7)
       {
           voice->say("seven");
       }
       else if(ans == 8)
       {
           voice->say("eight");
       }
       else if(ans == 9)
       {
           voice->say("nine");
       }
       else
       {
           voice->say("I don't know what that number is.");
       }

       sock->send("done",4);

       cout << "Ended\n";

   }
   else if(theStr == "build")
   {
       dm->init();
   }

}

void *server::ThreadMain(void *clntSock) {
  // Guarantees that thread resources are deallocated upon return
  pthread_detach(pthread_self());

  // Extract socket file descriptor from argument
  HandleTCPClient((TCPSocket *) clntSock);

  delete (TCPSocket *) clntSock;
  return NULL;
}

void *server::listen()
{
    TCPServerSocket servSock(6000);   // Socket descriptor for server

    for (;;) {      // Run forever
          // Create separate memory for client argument
          clntSock = servSock.accept();

          // Create client thread
          pthread_t threadID;              // Thread ID from pthread_create()
          if (pthread_create(&threadID, NULL, &(server::ThreadMain),
                  (void *) clntSock) != 0) {
            cerr << "Unable to create thread" << endl;
           //exit(1);
          }
        }
}
