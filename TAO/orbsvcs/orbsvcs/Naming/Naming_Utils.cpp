// $Id$

#include "orbsvcs/CosNamingC.h"
#include "tao/corba.h"
#include "Naming_Utils.h"
#include "ace/Arg_Shifter.h"
#include "Transient_Naming_Context.h"
#include "Persistent_Context_Index.h"
#include "ace/Auto_Ptr.h"

ACE_RCSID(Naming, Naming_Utils, "$Id$")

TAO_Naming_Server::TAO_Naming_Server (void)
  : naming_context_impl_ (0),
    naming_context_ (),
    ior_multicast_ (0),
    naming_service_ior_ ()
{
}

TAO_Naming_Server::TAO_Naming_Server (CORBA::ORB_ptr orb,
                                      PortableServer::POA_ptr poa,
                                      size_t context_size,
                                      ACE_Time_Value *timeout,
                                      int resolve_for_existing_naming_service,
                                      LPCTSTR persistence_location)
  : naming_context_impl_ (0),
    naming_context_ (),
    ior_multicast_ (0),
    naming_service_ior_ ()
{
  if (this->init (orb,
                  poa,
                  context_size,
                  timeout,
                  resolve_for_existing_naming_service,
                  persistence_location) == -1)
    ACE_ERROR ((LM_ERROR,
                "(%P|%t) %p\n",
                "TAO_Naming_Server::init"));
}


int
TAO_Naming_Server::init (CORBA::ORB_ptr orb,
                         PortableServer::POA_ptr poa,
                         size_t context_size,
                         ACE_Time_Value *timeout,
                         int resolve_for_existing_naming_service,
                         LPCTSTR persistence_location)
{
  // Don't look for a Naming Service; become one.
  if (!resolve_for_existing_naming_service)
    {
      return this->init_new_naming (orb,
                                    poa,
                                    persistence_location,
                                    context_size);
    }
  else
    {
      //
      // Try to find an existing Naming Service.
      //
      CORBA::Object_var naming_obj =
        orb->resolve_initial_references ("NameService",
                                         timeout);

      // No luck in finding an existing Naming Service.
      if (CORBA::is_nil (naming_obj.in ()))
        {
          if (TAO_debug_level > 0)
            ACE_DEBUG ((LM_DEBUG,
                        "\nNameService not resolved, so we'll become a NameService\n"));

          // Become a Naming Service.
          return this->init_new_naming (orb,
                                        poa,
                                        persistence_location,
                                        context_size);
        }
      else
        {
          //
          // Success in finding a Naming Service.
          //
          if (TAO_debug_level > 0)
            ACE_DEBUG ((LM_DEBUG,
                        "\nNameService found!\n"));

          ACE_DECLARE_NEW_CORBA_ENV;
          ACE_TRY
            {
              this->naming_context_ =
                CosNaming::NamingContext::_narrow (naming_obj.in (),
                                                   ACE_TRY_ENV);
              ACE_TRY_CHECK;

              this->naming_service_ior_ =
                orb->object_to_string (naming_obj.in (),
                                       ACE_TRY_ENV);

              ACE_TRY_CHECK;
            }
          ACE_CATCHANY
            {
              ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "TAO_Naming_Server::init");
            }
          ACE_ENDTRY;
          ACE_CHECK_RETURN (-1);
        }
    }
  return 0;
}

int
TAO_Naming_Server::init_new_naming (CORBA::ORB_ptr orb,
                                    PortableServer::POA_ptr poa,
                                    LPCTSTR persistence_location,
                                    size_t context_size)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      if (persistence_location != 0)
        {
          // This needs to be cleaned up (currently a memory leak) when
          // TAO_Naming_Server dies.
          TAO_Persistent_Context_Index *context_index;
          ACE_NEW_RETURN (context_index,
                          TAO_Persistent_Context_Index (orb, poa),
                          -1);

          if (context_index->open (persistence_location) == -1)
            ACE_DEBUG ((LM_DEBUG,
                        "context_index->open failed"));

          if (context_index->init () == -1)
            ACE_DEBUG ((LM_DEBUG,
                        "context_index->init failed"));

          // Set the ior and objref to the root naming context.
          this->naming_service_ior_= context_index->root_ior ();

          CORBA::Object_var obj =
            orb->string_to_object (this->naming_service_ior_.in (),
                                   ACE_TRY_ENV);
          ACE_TRY_CHECK;

          this->naming_context_ =
            CosNaming::NamingContext::_narrow (obj.in (),
                                               ACE_TRY_ENV);
          ACE_TRY_CHECK;

          // To make NS locatable through iioploc.  Right now not
          // checking the return value.
          orb->_tao_add_to_IOR_table ("NameService",
                                      obj.in ());
        }
      else
        {
          TAO_Transient_Naming_Context *context_impl = 0;
          ACE_NEW_RETURN (context_impl,
                          TAO_Transient_Naming_Context (poa,
                                                        "NameService",
                                                        context_size),
                          -1);

          // Put <context_impl> into the auto pointer temporarily, in case
          // next allocation fails.
          ACE_Auto_Basic_Ptr<TAO_Transient_Naming_Context> temp (context_impl);

          TAO_Naming_Context *context = 0;
          ACE_NEW_RETURN (context,
                          TAO_Naming_Context (context_impl),
                          -1);

          // Let <implementation> know about it's <interface>.
          context_impl->interface (context);

          // Change what we hold in auto pointer.
          temp.release ();
          ACE_Auto_Basic_Ptr<TAO_Naming_Context> temp2 (context);

          // Register with the POA.
          PortableServer::ObjectId_var id =
            PortableServer::string_to_ObjectId ("NameService");

          poa->activate_object_with_id (id.in (),
                                        context,
                                        ACE_TRY_ENV);
          ACE_TRY_CHECK;

          this->naming_context_ =
            context->_this (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          // Give POA the ownership of this servant.
          context->_remove_ref (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          // To make NS locatable through iioploc.  Right now not
          // checking the return value.
          orb->_tao_add_to_IOR_table ("NameService",
                                      this->naming_context_.in ());

          // Stringify the objref we'll be implementing, and print it
          // to stdout.  Someone will take that string and give it to
          // a client.
          this->naming_service_ior_=
            orb->object_to_string (this->naming_context_.in (),
                                   ACE_TRY_ENV);
          ACE_TRY_CHECK;

          if (TAO_debug_level > 0)
            ACE_DEBUG ((LM_DEBUG,
                        "NameService IOR is <%s>\n",
                        this->naming_service_ior_.in ()));

          // everything succeeded, so set the pointer, get rid of Auto_Ptr.
          this->naming_context_impl_ = context;
          temp2.release ();
        }
#if defined (ACE_HAS_IP_MULTICAST)
      // Get reactor instance from TAO.
      ACE_Reactor *reactor =
        TAO_ORB_Core_instance ()->reactor ();

      // First, see if the user has given us a multicast port number
      // for the name service on the command-line;
      u_short port =
        TAO_ORB_Core_instance ()->orb_params ()->name_service_port ();

      if (port == 0)
        {
          const char *port_number =
            ACE_OS::getenv ("NameServicePort");

          if (port_number != 0)
            port = ACE_OS::atoi (port_number);
        }

      if (port == 0)
        port = TAO_DEFAULT_NAME_SERVER_REQUEST_PORT;

      // Instantiate a server which will receive requests for an ior
      ACE_NEW_RETURN (this->ior_multicast_,
                      TAO_IOR_Multicast (this->naming_service_ior_.in (),
                                         port,
                                         ACE_DEFAULT_MULTICAST_ADDR,
                                         TAO_SERVICEID_NAMESERVICE),
                      -1);

      // Register event handler for the ior multicast.
      if (reactor->register_handler (this->ior_multicast_,
                                     ACE_Event_Handler::READ_MASK) == -1)
        {
          if (TAO_debug_level > 0)
            ACE_DEBUG ((LM_DEBUG,
                        "cannot register Event handler\n"));
          return -1;
        }
      else
        {
          if (TAO_debug_level > 0)
            ACE_DEBUG ((LM_DEBUG,
                        "The multicast server setup is done.\n"));
        }
#endif /* ACE_HAS_IP_MULTICAST */
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Naming Service");
      return -1;
    }
  ACE_ENDTRY;
  ACE_CHECK_RETURN (-1);

  return 0;
}

// Returns the "NameService" NamingContext implementation object.

TAO_Naming_Context &
TAO_Naming_Server::get_naming_context (void)
{
  return *this->naming_context_impl_;
}

CORBA::String
TAO_Naming_Server::naming_service_ior (void)
{
  return CORBA::string_dup (this->naming_service_ior_.in ());
}

// Returns a pointer to the NamingContext.

CosNaming::NamingContext_ptr
TAO_Naming_Server::operator-> (void) const
{
  return this->naming_context_.ptr ();
}

TAO_Naming_Server::~TAO_Naming_Server (void)
{
  if (this->ior_multicast_ != 0)
    {
      TAO_ORB_Core_instance ()->reactor ()->remove_handler
        (this->ior_multicast_,
         ACE_Event_Handler::READ_MASK | ACE_Event_Handler::DONT_CALL);
      delete this->ior_multicast_;
    }
  delete this->naming_context_impl_;
}

// Returns a pointer to the NamingContext.

CosNaming::NamingContext_ptr
TAO_Naming_Client::operator -> (void) const
{
  return this->naming_context_.ptr ();
}

// Returns a pointer to the NamingContext.

CosNaming::NamingContext_ptr
TAO_Naming_Client::get_context (void) const
{
  return this->naming_context_.ptr ();
}

int
TAO_Naming_Client::init (CORBA::ORB_ptr orb,
                         ACE_Time_Value *timeout)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      CORBA::Object_var naming_obj =
        orb->resolve_initial_references ("NameService", timeout);

      if (CORBA::is_nil (naming_obj.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           " (%P|%t) Unable to initialize the NameService.\n"),
                          -1);
      this->naming_context_ =
        CosNaming::NamingContext::_narrow (naming_obj.in (),
                                           ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "init");
      return -1;
    }
  ACE_ENDTRY;
  ACE_CHECK_RETURN (-1);

  return 0;
}

TAO_Naming_Client::TAO_Naming_Client (void)
{
  // Do nothing
}

TAO_Naming_Client::~TAO_Naming_Client (void)
{
  // Do nothing
}
