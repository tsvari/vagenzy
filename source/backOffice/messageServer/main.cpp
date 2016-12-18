#include "messagelib.h"

/* parsing request from any client
*/
bool parseRequest(string& sRequest, string& sFunctionName, int& nEmployee, int& nJob, int& nCompany);

int main()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://127.0.0.1:5556");

    MessageLib mesl;

    for(;;)
    {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);


        int nResult = MESS_OK;
        string strRequest = static_cast<char*>(request.data());
        std::cout << "Received - " << strRequest << std::endl;
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
            cout << "problem with function name " << sFunctionName << endl;
        }
        //==========================================================

        //  temporary waiting
        sleep(1);


        string strReply(to_string(nResult));
        zmq_send (socket, strReply.c_str(), strReply.length()+1, 0);
    }

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

