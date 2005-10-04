// $Id$

#include "GroupInfoPublisher.h"
#include "../Utils/resolve_init.h"
#include "IOGR_Maker.h"
#include "Identification_Service.h"
#include "FTEC_Become_Primary_Listener.h"
#include "../Utils/Log.h"

//#include "../Utils/log_obj_endpoints.h"

ACE_RCSID (EventChannel,
           GroupInfoPublisher,
           "$Id$")



GroupInfoPublisherBase::GroupInfoPublisherBase()
: info_(new Info)
{
  info_->primary = false;
}



void
GroupInfoPublisherBase::subscribe(TAO_FTEC_Become_Primary_Listener* listener)
{
  subscribers_.push_back(listener);
}

void GroupInfoPublisherBase::set_naming_context(CosNaming::NamingContext_var naming_context)
{
  naming_context_ = naming_context;
}

bool
GroupInfoPublisherBase::is_primary() const
{
  return info_->primary;
}

CORBA::Object_var
GroupInfoPublisherBase::group_reference() const
{
  return info_->iogr;
}

FtRtecEventChannelAdmin::EventChannel_var
GroupInfoPublisherBase::successor() const
{
  return info_->successor;
}



const GroupInfoPublisherBase::BackupList&
GroupInfoPublisherBase::backups() const
{
  return info_->backups;
}



GroupInfoPublisherBase::Info*
GroupInfoPublisherBase::setup_info(const FTRT::ManagerInfoList & info_list,
                                   int my_position,
                                   CORBA::ULong object_group_ref_version
                                   ACE_ENV_ARG_DECL)
{
  Info_ptr result(new Info);

  result->primary = (my_position == 0);

  /// create the object group
  size_t len = info_list.length();

  TAO_IOP::TAO_IOR_Manipulation::IORList iors;
  iors.length(len);

  size_t i;
  for (i = 0; i < len; ++i) {
    iors[i] = CORBA::Object::_duplicate(info_list[i].ior.in());
  }

  CORBA::Object_var obj =
    IOGR_Maker::instance()->make_iogr(iors,object_group_ref_version
                                      ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN(0);

  result->iogr =
    ::FtRtecEventChannelAdmin::EventChannel::_narrow(obj.in()
    ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN(0);

  ACE_DEBUG((LM_DEBUG, "In setup_info\n"));
  //log_obj_endpoints(result->iogr.in());

  /// check if sucessor changed
  size_t successors_length = info_list.length() - my_position -1;

  if (successors_length /*!= info_->backups.length() */)  {
    // successor changed, update successor
    iors.length(successors_length);
    for (i = 0; i < successors_length; ++i) {
      iors[i] = CORBA::Object::_duplicate(info_list[i+ my_position+1].ior.in());
    }

    obj =  IOGR_Maker::instance()->merge_iors(iors
      ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN(0);

    result->successor =
      FtRtecEventChannelAdmin::EventChannel::_narrow(obj.in()
      ACE_ENV_ARG_PARAMETER);
    ACE_CHECK_RETURN(0);
  }
  /*
  else {
    result->successor = info_->successor;
  }

  if (!CORBA::is_nil(result->successor.in()))
  {
    CORBA::PolicyList_var pols;
    result->successor->_validate_connection (pols.out ());
  }
  */

  // update backups
  result->backups.length(successors_length);
  for (i = 0; i < successors_length; ++i)  {
    result->backups[i] =
      FtRtecEventChannelAdmin::EventChannel::_narrow(
      info_list[i+ my_position+1].ior.in()
      ACE_ENV_ARG_PARAMETER);
    //CORBA::PolicyList_var pols;
    //result->backups[i]->_validate_connection (pols.out ());
    ACE_CHECK_RETURN(0);
  }
  return result.release();
}

void
GroupInfoPublisherBase::update_info(GroupInfoPublisherBase::Info_ptr& info)
{
  if (info->primary) {
    if (!info_->primary) {
      // now we become the primary, notify the subscribers
      for (size_t i = 0; i < subscribers_.size(); ++i)
        subscribers_[i]->become_primary();
    }

    if (!CORBA::is_nil(naming_context_.in())) {
      TAO_FTRTEC::Log(1, "Registering to the Name Service\n");
      ACE_TRY_NEW_ENV {
        naming_context_->rebind(FTRTEC::Identification_Service::instance()->name(),
          info->iogr.in() ACE_ENV_ARG_PARAMETER);
        ACE_TRY_CHECK;
      }
      ACE_CATCHALL {
        /// there's nothing we can do if the naming service is down
      }
      ACE_ENDTRY;
    }
  }
  info_ = info;
}

#if defined (ACE_HAS_EXPLICIT_STATIC_TEMPLATE_MEMBER_INSTANTIATION)

template ACE_Singleton<GroupInfoPublisherBase, ACE_Thread_Mutex> *ACE_Singleton<GroupInfoPublisherBase, ACE_Thread_Mutex>::singleton_;

#endif /* ACE_HAS_EXPLICIT_STATIC_TEMPLATE_MEMBER_INSTANTIATION */
