#include <iostream>
#include <map>
#include "../../global/zmq.hpp"
#include "../../global/message_globals.h"

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

using namespace std;

typedef map<int,map<int, int>> typeTABLE;
typedef unsigned short int SUINT;
/* map to quickly find job for employee
 * key is Employee ID and value is map with job ID as key and company as value
 * one employee may have more then one current job per company or within multi company
*/
static typeTABLE employeeToJobCompany;

/* parsing request from any client
*/
bool parseRequest(string& sRequest, string& sFunctionName, int& nEmployee, int& nJob, int& nCompany);

static SUINT addEmployeeJob(int nEmployee, int nJob, int nCompany);
static SUINT removeEmployeeFromJob(int nEmployee, int nJob);
static SUINT removeEmployee(int nEmployee, int nCompany);
static int checkJob(int nEmployee);

int main()
{
    //  Prepare our context and socket
        zmq::context_t context (1);
        zmq::socket_t socket (context, ZMQ_REP);
        socket.bind ("tcp://0.0.0.0:5555");

        while (true) {
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
            if(sFunctionName == string("addEmployeeJob"))
                nResult = addEmployeeJob(nEmployee, nJob, nCompany);
            else if(sFunctionName == string("removeEmployeeFromJob"))
                nResult = removeEmployeeFromJob(nEmployee, nJob);
            else if(sFunctionName == string("removeEmployee"))
                nResult = removeEmployee(nEmployee, nCompany);
            else if(sFunctionName == string("checkJob"))
                nResult = checkJob(nEmployee);
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

SUINT addEmployeeJob(int nEmployee, int nJob, int nCompany)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);

    if(itEmployee != employeeToJobCompany.end())
    {   // employee already exists in list (has anothernot closed job)
        std::map<int,int> &jobCompanyMap = itEmployee->second;
        jobCompanyMap.insert(std::pair<int,int>(nJob,nCompany));
    }
    else
    {   // no employee there
        std::map<int,int> jobCompanyPair;
        jobCompanyPair.insert(std::pair<int,int>(nJob,nCompany));
        employeeToJobCompany[nEmployee]=jobCompanyPair;
    }

    return MESS_OK;
}

SUINT removeEmployeeFromJob(int nEmployee, int nJob)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);
    if(itEmployee == employeeToJobCompany.end()) // no employee there
        return MESS_ERR_EMPLOYEE;

    // clean job-company pair associated to this employee
    std::map<int,int> &jobCompanyMap = itEmployee->second;
    jobCompanyMap.erase(nJob);

    // if job-company AP is empty delete employee too
    if(jobCompanyMap.empty())
        employeeToJobCompany.erase(itEmployee);

    return MESS_OK;
}

/* ----------------------------------------------------------------------
*/
SUINT removeEmployee(int nEmployee, int nCompany)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);
    if(itEmployee == employeeToJobCompany.end()) // no employee there
        return MESS_ERR_EMPLOYEE;

    // remove job-company pair associated to this employee
    std::map<int,int>& jobCompanyMap = itEmployee->second;
    std::map<int,int>::iterator itJobCompany = jobCompanyMap.begin();

    while(itJobCompany != jobCompanyMap.end())
    {
        if(itJobCompany->second == nCompany)
        {
            std::map<int,int>::iterator itToErase = itJobCompany;
            ++itJobCompany;
            jobCompanyMap.erase(itToErase);
        }
        else
            ++itJobCompany;
    }

    // if job-company AP is empty delete employee too
    if(jobCompanyMap.empty())
        employeeToJobCompany.erase(itEmployee);

    return MESS_OK;
}

/* ----------------------------------------------------------------------
*/
int checkJob(int nEmployee)
{
    typeTABLE::iterator itEmployee = employeeToJobCompany.find(nEmployee);
    if(itEmployee == employeeToJobCompany.end()) // no employee and job there
        return 0;

    std::map<int,int> jobCompanyMap(itEmployee->second);

    return static_cast<int>(jobCompanyMap.size());
}
