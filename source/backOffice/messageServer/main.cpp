#include "../../global/message_globals.h"
#include "../../global/zmq.hpp"
#include "../global/data_globals.h"
#include "../messageServer/zparser.h"
#include "../messageServer/zrpc.h"
#include "../messageServer/zvalidator.h"
#include "../messageServer/dbjobsloader.h"
#include "../messageServer/configfile.h"
#include "../messageServer/checkjob.h"
#include "../messageServer/addemployeetojob.h"
#include "../messageServer/removeemployee.h"
#include "../messageServer/removeemployeefromjob.h"

#include <string>

using std::string;
using std::to_string;

messMAP employeeToJobCompany;
std::map<std::string, ZBase*> globalDriverData;

void *message_routine (void *arg)
{

    // get context from 'main' thread
    zmq::context_t *context = (zmq::context_t *) arg;

    // create REP socket for reply tp client socket
    zmq::socket_t socket (*context, ZMQ_REP);
    socket.connect ("inproc://workers");

    for(;;)
    {
        zmq::message_t request;

        //  get request from client
        socket.recv (&request);

        int nClientResponse = MESS_OK;
        const char* str_request = static_cast<const char*>(request.data());

        // start proccessing recieved data
        //--------------------------------
        ZParser parser;
        ZData zdata;

        // try to parse client data
        nClientResponse = parser.Parse(str_request, zdata);
        if( nClientResponse != MESS_OK )
        {
            // log error here
            goto client_response;
        }

        // validate client data
        if(!ZValidator::Validate(zdata))
        {
            // log error here
            goto client_response;

        }

        // try to call RPC function
        nClientResponse = ZRPC::CallProc(zdata);
        if( nClientResponse != MESS_OK)
        {
            // log error here
            goto client_response;
        }

        //--------------------------------------
        // return result to client
        client_response:
        string strReply(to_string(nClientResponse));
        zmq_send (socket, strReply.c_str(), strReply.length()+1, 0);
    }
    return (NULL);
}

int main()
{
    globalDriverData.insert(std::pair<std::string, ZBase*>("checkJob", new CheckJob(employeeToJobCompany, true)));
    globalDriverData.insert(std::pair<std::string, ZBase*>("addEmployeeToJob", new AddEmployeeToJob(employeeToJobCompany,true)));
    globalDriverData.insert(std::pair<std::string, ZBase*>("removeEmployeeFromJob", new RemoveEmployeeFromJob(employeeToJobCompany, true)));
    globalDriverData.insert(std::pair<std::string, ZBase*>("removeEmployee", new RemoveEmployee(employeeToJobCompany, true)));

    // define log file
    //string logFile = string(LOG_FOLDER) + string("/") + string(PROJECT_NAME) + string(".log");
    // set name of new log file to "logger" config
    //el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, logFile);

    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t clients (context, ZMQ_ROUTER);
    clients.bind ("tcp://127.0.0.1:5556");

    zmq::socket_t workers (context, ZMQ_DEALER);
    workers.bind ("inproc://workers");

    //  Launch pool of worker threads
    for (int thread_nbr = 0; thread_nbr < 5; thread_nbr++)
    {
        pthread_t worker;
        pthread_create (&worker, NULL, message_routine, (void *) &context);
    }
    //  Connect work threads to client threads via a queue
    zmq::proxy (clients, workers, NULL);

    for(auto& ob : globalDriverData)
    {
        delete dynamic_cast<ZBase*>(ob.second);
    }

    return 0;
}

