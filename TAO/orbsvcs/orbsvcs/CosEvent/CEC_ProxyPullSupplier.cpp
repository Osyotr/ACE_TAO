// $Id$

#include "CEC_ProxyPullSupplier.h"
#include "CEC_Dispatching.h"
#include "CEC_EventChannel.h"

#include "ace/Reverse_Lock_T.h"

#if ! defined (__ACE_INLINE__)
#include "CEC_ProxyPullSupplier.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID (CosEvent,
           CEC_ProxyPullSupplier,
           "$Id$")

typedef ACE_Reverse_Lock<ACE_Lock> TAO_CEC_Unlock;

TAO_CEC_ProxyPullSupplier::TAO_CEC_ProxyPullSupplier (TAO_CEC_EventChannel* ec)
  : event_channel_ (ec),
    refcount_ (1),
    connected_ (0),
    wait_not_empty_ (queue_lock_)
{
  this->lock_ =
    this->event_channel_->create_supplier_lock ();

  this->default_POA_ =
    this->event_channel_->supplier_poa ();

  this->event_channel_->get_servant_retry_map ().bind (this, 0);
}

TAO_CEC_ProxyPullSupplier::~TAO_CEC_ProxyPullSupplier (void)
{
  this->event_channel_->get_servant_retry_map ().unbind (this);
  this->event_channel_->destroy_supplier_lock (this->lock_);
}

void
TAO_CEC_ProxyPullSupplier::activate (
    CosEventChannelAdmin::ProxyPullSupplier_ptr &activated_proxy
    ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  CosEventChannelAdmin::ProxyPullSupplier_var result;
  ACE_TRY
    {
      result = this->_this (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      result = CosEventChannelAdmin::ProxyPullSupplier::_nil ();
    }
  ACE_ENDTRY;
  activated_proxy = result._retn ();
}

void
TAO_CEC_ProxyPullSupplier::deactivate (ACE_ENV_SINGLE_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TRY
    {
      PortableServer::POA_var poa =
        this->_default_POA (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_TRY_CHECK;
      PortableServer::ObjectId_var id =
        poa->servant_to_id (this ACE_ENV_ARG_PARAMETER);
      ACE_TRY_CHECK;
      poa->deactivate_object (id.in () ACE_ENV_ARG_PARAMETER);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      // Exceptions here should not be propagated.  They usually
      // indicate that an object is beign disconnected twice, or some
      // race condition, but not a fault that the user needs to know
      // about.
    }
  ACE_ENDTRY;
}

void
TAO_CEC_ProxyPullSupplier::shutdown (ACE_ENV_SINGLE_ARG_DECL)
{
  // Save the consumer we where connected to, we need to send a
  // disconnect message to it.
  CosEventComm::PullConsumer_var consumer;

  {
    ACE_GUARD_THROW_EX (
        ACE_Lock, ace_mon, *this->lock_,
        CORBA::INTERNAL ());
    // @@ CosEventChannelAdmin::EventChannel::SYNCHRONIZATION_ERROR ());
    ACE_CHECK;

    consumer = this->consumer_._retn ();
  }

  this->deactivate (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK;

  if (CORBA::is_nil (consumer.in ()))
    return;

  ACE_TRY
    {
      consumer->disconnect_pull_consumer (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      // Ignore exceptions, we must isolate other clients from
      // problems on this one.
    }
  ACE_ENDTRY;
}

CORBA::Boolean
TAO_CEC_ProxyPullSupplier::consumer_non_existent (
      CORBA::Boolean_out disconnected
      ACE_ENV_ARG_DECL)
{
  CORBA::Object_var consumer;
  {
    ACE_GUARD_THROW_EX (
        ACE_Lock, ace_mon, *this->lock_,
        CORBA::INTERNAL ());
    ACE_CHECK_RETURN (0);

    disconnected = 0;
    if (this->is_connected_i () == 0)
      {
        disconnected = 1;
        return 0;
      }
    if (CORBA::is_nil (this->consumer_.in ()))
      {
        return 0;
      }
    consumer = CORBA::Object::_duplicate (this->consumer_.in ());
  }

#if (TAO_HAS_MINIMUM_CORBA == 0)
  return consumer->_non_existent (ACE_ENV_SINGLE_ARG_PARAMETER);
#else
  return 0;
#endif /* TAO_HAS_MINIMUM_CORBA */
}

void
TAO_CEC_ProxyPullSupplier::push (const CORBA::Any &event
                                 ACE_ENV_ARG_DECL_NOT_USED)
{
  if (this->is_connected () == 0)
    return;

  ACE_GUARD (TAO_SYNCH_MUTEX, ace_mon, this->queue_lock_);

  // Ignore errors
  (void) this->queue_.enqueue_tail (event);

  this->wait_not_empty_.signal ();
}

CORBA::Any *
TAO_CEC_ProxyPullSupplier::pull (ACE_ENV_SINGLE_ARG_DECL)
      ACE_THROW_SPEC ((CORBA::SystemException,
                       CosEventComm::Disconnected))
{
  if (this->is_connected () == 0)
    ACE_THROW_RETURN (CosEventComm::Disconnected (), 0);

  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, queue_lock_, 0);
  while (this->queue_.is_empty ())
    {
      this->wait_not_empty_.wait ();
    }
  CORBA::Any any;
  if (this->queue_.dequeue_head (any) != 0)
    {
      ACE_THROW_RETURN (CORBA::INTERNAL (), 0);
    }
  return new CORBA::Any (any);
}

CORBA::Any *
TAO_CEC_ProxyPullSupplier::try_pull (CORBA::Boolean_out has_event
                                     ACE_ENV_ARG_DECL)
      ACE_THROW_SPEC ((CORBA::SystemException,CosEventComm::Disconnected))
{
  has_event = 0;
  if (this->is_connected () == 0)
    ACE_THROW_RETURN (CosEventComm::Disconnected (), 0);

  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, queue_lock_, 0);
  CORBA::Any any;
  if (this->queue_.is_empty ())
    {
      any <<= CORBA::Long(0);
      return new CORBA::Any (any);
    }

  if (this->queue_.dequeue_head (any) != 0)
    {
      ACE_THROW_RETURN (CORBA::INTERNAL (), 0);
    }
  has_event = 1;
  return new CORBA::Any (any);
}

void
TAO_CEC_ProxyPullSupplier::cleanup_i (void)
{
  this->consumer_ =
    CosEventComm::PullConsumer::_nil ();
  this->connected_ = 0;
}

CORBA::ULong
TAO_CEC_ProxyPullSupplier::_incr_refcnt (void)
{
  ACE_GUARD_RETURN (ACE_Lock, ace_mon, *this->lock_, 0);
  return this->refcount_++;
}

CORBA::ULong
TAO_CEC_ProxyPullSupplier::_decr_refcnt (void)
{
  {
    ACE_GUARD_RETURN (ACE_Lock, ace_mon, *this->lock_, 0);
    this->refcount_--;
    if (this->refcount_ != 0)
      return this->refcount_;
  }

  // Notify the event channel
  this->event_channel_->destroy_proxy (this);
  return 0;
}

void
TAO_CEC_ProxyPullSupplier::connect_pull_consumer (
      CosEventComm::PullConsumer_ptr pull_consumer
      ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosEventChannelAdmin::AlreadyConnected))
{
  {
    ACE_GUARD_THROW_EX (
        ACE_Lock, ace_mon, *this->lock_,
        CORBA::INTERNAL ());
    // @@ CosEventChannelAdmin::EventChannel::SYNCHRONIZATION_ERROR ());
    ACE_CHECK;

    if (this->is_connected_i ())
      {
        if (this->event_channel_->consumer_reconnect () == 0)
          ACE_THROW (CosEventChannelAdmin::AlreadyConnected ());

        // Re-connections are allowed....
        this->cleanup_i ();

        this->consumer_ =
          CosEventComm::PullConsumer::_duplicate (pull_consumer);
        this->connected_ = 1;

        TAO_CEC_Unlock reverse_lock (*this->lock_);

        {
          ACE_GUARD_THROW_EX (
              TAO_CEC_Unlock, ace_mon, reverse_lock,
              CORBA::INTERNAL ());
          // @@ CosEventChannelAdmin::EventChannel::SYNCHRONIZATION_ERROR ());
          ACE_CHECK;

          this->event_channel_->reconnected (this ACE_ENV_ARG_PARAMETER);
          ACE_CHECK;
        }
        return;
      }

    this->consumer_ =
      CosEventComm::PullConsumer::_duplicate (pull_consumer);
    this->connected_ = 1;
  }

  // Notify the event channel...
  this->event_channel_->connected (this ACE_ENV_ARG_PARAMETER);
}

void
TAO_CEC_ProxyPullSupplier::disconnect_pull_supplier (
      ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  CosEventComm::PullConsumer_var consumer;

  {
    ACE_GUARD_THROW_EX (
        ACE_Lock, ace_mon, *this->lock_,
        CORBA::INTERNAL ());
    // @@ CosEventChannelAdmin::EventChannel::SYNCHRONIZATION_ERROR ());
    ACE_CHECK;

    if (this->is_connected_i () == 0)
      ACE_THROW (CORBA::BAD_INV_ORDER ());

    consumer = this->consumer_._retn ();

    this->cleanup_i ();
  }

  // Notify the event channel....
  this->event_channel_->disconnected (this ACE_ENV_ARG_PARAMETER);
  ACE_CHECK;

  if (CORBA::is_nil (consumer.in ()))
    return;

  if (this->event_channel_->disconnect_callbacks ())
    {
      ACE_TRY
        {
          consumer->disconnect_pull_consumer (ACE_ENV_SINGLE_ARG_PARAMETER);
          ACE_TRY_CHECK;
        }
      ACE_CATCHANY
        {
          // Ignore exceptions, we must isolate other clients from
          // problems on this one.
          ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                               "ProxySupplier::disconnect_pull_supplier");
        }
      ACE_ENDTRY;
    }
}

PortableServer::POA_ptr
TAO_CEC_ProxyPullSupplier::_default_POA (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
{
  return PortableServer::POA::_duplicate (this->default_POA_.in ());
}

void
TAO_CEC_ProxyPullSupplier::_add_ref (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
{
  this->_incr_refcnt ();
}

void
TAO_CEC_ProxyPullSupplier::_remove_ref (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
{
  this->_decr_refcnt ();
}
