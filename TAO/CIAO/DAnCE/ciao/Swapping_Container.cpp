// $Id$

#include "Container_Base.h"
#include "Swapping_Container.h"
#include "ace/DLL.h"
#include "tao/Utils/PolicyList_Destroyer.h"
#include "ace/OS_NS_stdio.h"

#if !defined (__ACE_INLINE__)
# include "Swapping_Container.inl"
#endif /* __ACE_INLINE__ */

namespace CIAO
{

  ACE_Atomic_Op <ACE_SYNCH_MUTEX, long>
  Swapping_Container::serial_number_ (0);

  Swapping_Container::Swapping_Container (CORBA::ORB_ptr o)
  : Session_Container (o),
    number_ (0)
  {
  }

  Swapping_Container::~Swapping_Container ()
  {
  }

  PortableServer::POA_ptr
  Swapping_Container::the_home_servant_POA (void) const
  {
    return this->home_servant_poa_.in ();
  }

  CORBA::Object_ptr
  Swapping_Container::get_home_objref (PortableServer::Servant p
                                       ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
  {
    ACE_DEBUG ((LM_DEBUG, "i am inside get home objref \n"));
    return this->the_home_servant_POA ()->servant_to_reference (p
       ACE_ENV_ARG_PARAMETER);
  }

  int
  Swapping_Container::init (const char *name,
                            const CORBA::PolicyList *more_policies
                            ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
  {
    char buffer[MAXPATHLEN];

    if (name == 0)
      {
        this->number_ = ++Swapping_Container::serial_number_;
        ACE_OS::sprintf (buffer, "CIAO::Swapping_Container-%ld",
                         this->number_);
        name = buffer;
      }

    CORBA::Object_var poa_object =
      this->orb_->resolve_initial_references("RootPOA"
                                             ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);

    if (CORBA::is_nil (poa_object.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         " (%P|%t) Unable to initialize the POA.\n"),
                        -1);

    PortableServer::POA_var root_poa =
      PortableServer::POA::_narrow (poa_object.in ()
                                    ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);


    this->create_servant_POA (name,
                              more_policies,
                              root_poa.in ()
                              ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);



    this->create_home_servant_POA ("home servant POA",
                                   more_policies,
                                   root_poa.in ()
                                   ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);

    this->create_connections_POA (root_poa.in ()
                           ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);

    PortableServer::POAManager_var poa_manager =
      root_poa->the_POAManager (ACE_ENV_SINGLE_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);

    poa_manager->activate (ACE_ENV_SINGLE_ARG_PARAMETER);
    ACE_CHECK_RETURN (-1);

    return 0;
  }

  void
  Swapping_Container::add_servant_map
    (PortableServer::ObjectId &oid,
     Dynamic_Component_Servant_Base* servant
     ACE_ENV_ARG_DECL)
  {
    ACE_DEBUG ((LM_DEBUG, "i am in add servant map\n"));
    this->dsa_->add_servant_map (oid, servant);
  }

  void
  Swapping_Container::delete_servant_map
    (PortableServer::ObjectId &oid
     ACE_ENV_ARG_DECL)
  {
    ACE_DEBUG ((LM_DEBUG, "i am in delete servant map\n"));
    this->dsa_->delete_servant_map (oid);
  }

  void
  Swapping_Container::create_home_servant_POA (const char *name,
                                          const CORBA::PolicyList *p,
                                          PortableServer::POA_ptr root
                                          ACE_ENV_ARG_DECL)
  {
    CORBA::PolicyList policies (0);

    if (p != 0)
      policies = *p;

    PortableServer::POAManager_var poa_manager =
      root->the_POAManager (ACE_ENV_SINGLE_ARG_PARAMETER);
    ACE_CHECK;


    this->home_servant_poa_ =
      root->create_POA (name,
                        poa_manager.in (),
                        policies
                        ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;
  }

  void
  Swapping_Container::create_connections_POA (
      PortableServer::POA_ptr root
      ACE_ENV_ARG_DECL)
  {
    PortableServer::POAManager_var poa_manager =
      root->the_POAManager (ACE_ENV_SINGLE_ARG_PARAMETER);
    ACE_CHECK;

    TAO::Utils::PolicyList_Destroyer policies (3);
    policies.length (3);

    policies[0] =
      root->create_id_assignment_policy (PortableServer::USER_ID
                                         ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    policies[1] =
      root->create_request_processing_policy
        (PortableServer::USE_SERVANT_MANAGER
         ACE_ENV_ARG_PARAMETER);

    ACE_CHECK;

    // Servant Retention Policy
    policies[2] =
      root->create_servant_retention_policy (PortableServer::RETAIN
                                             ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    this->facet_cons_poa_ =
      root->create_POA ("facet_consumer_poa",
                        poa_manager.in (),
                        policies
                        ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    ACE_NEW_THROW_EX (this->sa_,
                      Servant_Activator (this->orb_.in ()),
                      CORBA::NO_MEMORY ());

    this->facet_cons_poa_->set_servant_manager (
        this->sa_
        ACE_ENV_ARG_PARAMETER);

    ACE_CHECK;
  }

  void
  Swapping_Container::create_servant_POA (const char *name,
                                          const CORBA::PolicyList *p,
                                          PortableServer::POA_ptr root
                                          ACE_ENV_ARG_DECL)
  {
    CORBA::PolicyList policies (0);

    if (p != 0)
      policies = *p;

    PortableServer::POAManager_var poa_manager =
      root->the_POAManager (ACE_ENV_SINGLE_ARG_PARAMETER);
    ACE_CHECK;

    CORBA::ULong policy_length = policies.length ();
    policies.length (policy_length + 1);
    policies[policy_length] =
      root->create_id_assignment_policy (PortableServer::USER_ID
                                         ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    policy_length = policies.length ();
    policies.length (policy_length + 1);
    policies[policy_length] =
     root->create_request_processing_policy (
       PortableServer::USE_SERVANT_MANAGER
       ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    policy_length = policies.length ();
    policies.length (policy_length + 1);
    policies[policy_length] =
      root->create_servant_retention_policy (PortableServer::RETAIN
                                             ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    this->component_poa_ =
      root->create_POA (name,
                        poa_manager.in (),
                        policies
                        ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    ACE_NEW_THROW_EX (this->dsa_,
                      Dynamic_Component_Activator (this->orb_.in ()),
                      CORBA::NO_MEMORY ());

    this->component_poa_->set_servant_manager (
        this->dsa_
        ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

  }

  void
  Swapping_Container::ciao_uninstall_home (Components::CCMHome_ptr homeref
                                          ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
  {
    PortableServer::POA_ptr tmp = this->home_servant_poa_.in ();
    PortableServer::ObjectId_var oid =
      tmp->reference_to_id (homeref
                            ACE_ENV_ARG_PARAMETER);
    ACE_CHECK;

    tmp->deactivate_object (oid.in ()
                            ACE_ENV_ARG_PARAMETER);
  }

  CORBA::Object_ptr
  Swapping_Container::install_servant (PortableServer::Servant p,
                                      Container::OA_Type t
                                      ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
  {
    PortableServer::POA_ptr tmp = 0;

    if (t == Container::Component)
    {
      tmp = this->home_servant_poa_.in ();
    }
    else
      tmp = this->facet_cons_poa_.in ();

    PortableServer::ObjectId_var oid
      = tmp->activate_object (p
                              ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (0);
    
    CORBA::Object_var objref
      = tmp->id_to_reference (oid.in ()
                              ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN (0);

    return objref._retn ();
  }
}
