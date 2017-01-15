#include "../../global/zmq.hpp"
#include <string>
#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

long time_diff_mlsec(std::chrono::system_clock::time_point startTime, std::chrono::system_clock::time_point endTime);

int main ()
{
    srand((unsigned)time(0));

    std::string sendStr = "";
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://127.0.0.1:5556");

    chrono::system_clock::time_point timeBefore = chrono::system_clock::now();
    //  Do 10 requests, waiting each time for a response
    for (int i = 0; i < 50000; i++)
    {
        string strFunction[3] = {"addEmployeeToJob", "removeEmployeeFromJob", "removeEmployee"};
        int indexFunction = 0;
        int nEmployee = 0;
        int nJob = 0;
        int nCompany = 0;
/*
        cout<<"Enter function index addEmployeeJob - 0;\n"
              "removeEmployeeFromJob - 1;"
              "addEmployeeJob - 2; :";

        cin>>indexFunction;

        cout<<"Employee: ";
        cin>>nEmployee;
        cout<<"Job: ";
        cin>>nJob;
        cout<<"Company: ";
        cin>>nCompany;


        //sendStr = strFunction[0] + ";" +
                  //to_string(rand() % 100000 + 1) + ";" +
                  //to_string(rand() % 100000 + 1)+ ";" +
                  //to_string(rand() % 100000 + 1)+ ";" ;


        sendStr = strFunction[(indexFunction>2 || indexFunction<0)?0:indexFunction] + ";" +
                  to_string(nEmployee) + ";" +
                  to_string(nJob)+ ";" +
                  to_string(nCompany)+ ";" ;
*/
        //nJob = nEmployee = nCompany = 10;

        sendStr = strFunction[indexFunction] + ";" +
                  to_string(rand() % 100000 + 1) + ";" +
                  to_string(rand() % 100000 + 1)+ ";" +
                  to_string(rand() % 100000 + 1)+ ";" ;
        nCompany = ++nJob;
        nCompany++;


        zmq::message_t request (sendStr.length());
        memcpy (request.data (), sendStr.c_str(), sendStr.length());
        cout << sendStr << endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        string strReply = static_cast<char*>(reply.data())+string("\0");
        //cout << "Reply status: " << strReply << endl;
    }

    chrono::system_clock::time_point timeAfter = chrono::system_clock::now();

    cout<<time_diff_mlsec(timeBefore, timeAfter)<<endl;
    return 0;
}

long time_diff_mlsec(std::chrono::system_clock::time_point startTime,
                    std::chrono::system_clock::time_point endTime)
{
    auto duration = startTime.time_since_epoch();
    auto duration2 = endTime.time_since_epoch();

    return
    static_cast<long>(std::chrono::duration_cast<std::chrono::milliseconds>(duration2).count() -
    std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}
