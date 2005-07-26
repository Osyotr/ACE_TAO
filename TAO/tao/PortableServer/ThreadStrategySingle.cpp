// $Id$

#include "ThreadStrategySingle.h"
#include "ace/Dynamic_Service.h"
#include "ace/Log_Msg.h"

ACE_RCSID (PortableServer,
           ThreadStrategySingle,
           "$Id$")

#if (TAO_HAS_MINIMUM_POA == 0)

namespace TAO
{
  namespace Portable_Server
  {
    int
    ThreadStrategySingle::enter ()
    {
      return lock_.acquire();
    }

    int
    ThreadStrategySingle::exit ()
    {
      return lock_.release();
    }

    ::PortableServer::ThreadPolicyValue
    ThreadStrategySingle::type() const
    {
      return ::PortableServer::SINGLE_THREAD_MODEL;
    }

    ACE_FACTORY_DEFINE (ACE_Local_Service, ThreadStrategySingle)

    ACE_STATIC_SVC_DEFINE (
        ThreadStrategySingle,
        ACE_TEXT ("ThreadStrategySingle"),
        ACE_SVC_OBJ_T,
        &ACE_SVC_NAME (ThreadStrategySingle),
        ACE_Service_Type::DELETE_THIS | ACE_Service_Type::DELETE_OBJ,
        0
      )
  }
}

#endif /* TAO_HAS_MINIMUM_POA == 0 */
