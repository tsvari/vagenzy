#include "messagelib.h"
#include "../../global/zmq.hpp"
#include "../global/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

/* parsing request from any client
*/
bool parseRequest(string& sRequest, string& sFunctionName, int& nEmployee, int& nJob, int& nCompany);
long time_diff_mlsec(std::chrono::system_clock::time_point startTime, std::chrono::system_clock::time_point endTime);

MessageLib mesl;

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

        //  Wait for next request from client
        socket.recv (&request);

        int nResult = MESS_OK;
        string strRequest = static_cast<char*>(request.data());
        //std::cout << "Received - " << strRequest << std::endl;
        //==========================================================
        string sFunctionName;
        int nEmployee, nJob, nCompany;

        // try to parse request
        if(!parseRequest(strRequest, sFunctionName, nEmployee, nJob, nCompany))
        {
            nResult = MESS_ERR_PARSING;
            cout << "parsing problem " << strRequest << endl;
        }

        // with parsing is ok, now try to run functions
        if(sFunctionName == string("addEmployeeToJob"))
            nResult = mesl.addEmployeeToJob(nEmployee, nJob, nCompany);
        else if(sFunctionName == string("removeEmployeeFromJob"))
            nResult = mesl.removeEmployeeFromJob(nEmployee, nJob);
        else if(sFunctionName == string("removeEmployee"))
            nResult = mesl.removeEmployee(nEmployee, nCompany);
        else if(sFunctionName == string("checkJob"))
            nResult = mesl.checkJob(nEmployee);
        else
        {
            nResult = MESS_ERR_FUNCTION_NAME;
            LOG(ERROR) << "problem with function name : " << "someone needs to hack this stupid App?";
        }

        //==========================================================
        string strReply(to_string(nResult));
        zmq_send (socket, strReply.c_str(), strReply.length()+1, 0);
    }
    return (NULL);
}

int main()
{
    // define log file
    string logFile = string(LOG_FOLDER) + string("/") + string(PROJECT_NAME) + string(".log");
    // set name of new log file to "logger" config
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, logFile);

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

    return 0;
}

bool parseRequest(string& sRequest, string& sFunctionName, int& nEmployee, int& nJob, int& nCompany)
{
    string::size_type foundStart = 0;
    string::size_type foundEnd = sRequest.find(";");

    // fill fuction name
    if (foundEnd == std::string::npos)
        return false;
    sFunctionName = sRequest.substr(foundStart,foundEnd);

    // fill emploee
    foundStart = foundEnd + 1;
    foundEnd = sRequest.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return false;
    nEmployee = atoi(sRequest.substr(foundStart,foundEnd-foundStart).c_str());

    // fill job
    foundStart = foundEnd + 1;
    foundEnd = sRequest.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return false;
    nJob = atoi(sRequest.substr(foundStart,foundEnd-foundStart).c_str());

    // fill company
    foundStart = foundEnd + 1;
    foundEnd = sRequest.find(";", foundStart);
    if (foundEnd == std::string::npos)
        return false;
    nCompany = atoi(sRequest.substr(foundStart,foundEnd-foundStart).c_str());

    return true;
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
