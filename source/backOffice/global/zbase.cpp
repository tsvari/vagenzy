#include "data_globals.h"
#include "../../global/message_globals.h"
#include "zbase.h"

//////////////////////////////////////////////////////////////////////////
/// \brief ZBase::ZBase: Base class for all controler classes
/// 'AddEmployeeToJob', 'RemoveEmployeeFromJob', 'RemoveEmployee', 'CheckJob'
/// \param employeeToJobCompany: Global data-map
/// \param lock_mode: using method by posix thread ot not
///
ZBase::ZBase(messMAP& employeeToJobCompany, bool lock_mode):
    _employeeToJobCompany(employeeToJobCompany),
    _lock_mode(lock_mode)
{
	_rwlock = PTHREAD_RWLOCK_INITIALIZER;
}

int ZBase::Dojob(ZData&)
{
    return MESS_OK;
}
