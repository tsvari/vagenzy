#include "../../global/zmq.hpp"
#include <string>
#include <iostream>
#include <time.h>

using namespace std;


int main()
{
    string sendStr = "";
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    cout << "Connecting to hello world server…" << endl;
    socket.connect ("tcp://0.0.0.0:5555");

    for (int i = 0; i != 10; i++)
    {
        int nEmloyee = 0;
        cout<<"Enter employee N: ";
        cin>>nEmloyee;

        sendStr = string("checkJob") + ";" +
                  to_string(nEmloyee) + ";" +
                  to_string(0)+ ";" +
                  to_string(0)+ ";" ;

        zmq::message_t request (sendStr.length());
        memcpy (request.data (), sendStr.c_str(), sendStr.length());
        std::cout << sendStr << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        std::cout << "Received quantity of jobs: " << static_cast<char*>(reply.data()) << std::endl;
    }
    return 0;
}
