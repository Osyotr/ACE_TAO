// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_codegen.cpp:314


#include "Messaging_SyncScope_PolicyC.h"
#include "tao/Stub.h"

#if defined (__BORLANDC__)
#pragma option -w-rvl -w-rch -w-ccc -w-aus -w-sig
#endif /* __BORLANDC__ */

#if !defined (__ACE_INLINE__)
#include "Messaging_SyncScope_PolicyC.i"
#endif /* !defined INLINE */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/interface_cs.cpp:61

int Messaging::SyncScopePolicy::_tao_class_id = 0;

Messaging::SyncScopePolicy_ptr
Messaging::tao_SyncScopePolicy_life::tao_duplicate (
    Messaging::SyncScopePolicy_ptr p
  )
{
  return Messaging::SyncScopePolicy::_duplicate (p);
}

void
Messaging::tao_SyncScopePolicy_life::tao_release (
    Messaging::SyncScopePolicy_ptr p
  )
{
  CORBA::release (p);
}

Messaging::SyncScopePolicy_ptr
Messaging::tao_SyncScopePolicy_life::tao_nil (
    void
  )
{
  return Messaging::SyncScopePolicy::_nil ();
}

CORBA::Boolean
Messaging::tao_SyncScopePolicy_life::tao_marshal (
    Messaging::SyncScopePolicy_ptr p,
    TAO_OutputCDR &cdr
  )
{
  return p->marshal (cdr);
}

Messaging::SyncScopePolicy_ptr
Messaging::tao_SyncScopePolicy_cast::tao_narrow (
    CORBA::Object *p
    ACE_ENV_ARG_DECL
  )
{
  return Messaging::SyncScopePolicy::_narrow (p ACE_ENV_ARG_PARAMETER);
}

CORBA::Object *
Messaging::tao_SyncScopePolicy_cast::tao_upcast (
    void *src
  )
{
  Messaging::SyncScopePolicy **tmp =
    ACE_static_cast (Messaging::SyncScopePolicy **, src);
  return *tmp;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
  template class
    TAO_Objref_Var_T<
        Messaging::SyncScopePolicy,
        Messaging::tao_SyncScopePolicy_life
      >;
  template class
    TAO_Objref_Out_T<
        Messaging::SyncScopePolicy,
        Messaging::tao_SyncScopePolicy_life
      >;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
# pragma instantiate \
    TAO_Objref_Var_T< \
        Messaging::SyncScopePolicy, \
        Messaging::tao_SyncScopePolicy_life \
      >
# pragma instantiate \
    TAO_Objref_Out_T< \
        Messaging::SyncScopePolicy, \
        Messaging::tao_SyncScopePolicy_life \
      >
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/interface_cs.cpp:232

Messaging::SyncScopePolicy::SyncScopePolicy (void)
{}

Messaging::SyncScopePolicy::~SyncScopePolicy (void)
{}

void
Messaging::SyncScopePolicy::_tao_any_destructor (void *_tao_void_pointer)
{
  SyncScopePolicy *tmp = ACE_static_cast (SyncScopePolicy *, _tao_void_pointer);
  CORBA::release (tmp);
}

Messaging::SyncScopePolicy_ptr
Messaging::SyncScopePolicy::_narrow (
    CORBA::Object_ptr obj
    ACE_ENV_ARG_DECL
  )
{
  return SyncScopePolicy::_unchecked_narrow (obj ACE_ENV_ARG_PARAMETER);
}

Messaging::SyncScopePolicy_ptr
Messaging::SyncScopePolicy::_unchecked_narrow (
    CORBA::Object_ptr obj
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  if (CORBA::is_nil (obj))
    {
      return SyncScopePolicy::_nil ();
    }

  return
      ACE_reinterpret_cast (
          SyncScopePolicy_ptr,
          obj->_tao_QueryInterface (
              ACE_reinterpret_cast (
                  ptr_arith_t,
                  &SyncScopePolicy::_tao_class_id
                )
            )
        );
}

Messaging::SyncScopePolicy_ptr
Messaging::SyncScopePolicy::_duplicate (SyncScopePolicy_ptr obj)
{
  if (! CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }

  return obj;
}

void *Messaging::SyncScopePolicy::_tao_QueryInterface (ptr_arith_t type)
{
  void *retv = 0;

  if (type == ACE_reinterpret_cast (
              ptr_arith_t,
              &ACE_NESTED_CLASS (::Messaging, SyncScopePolicy)::_tao_class_id)
            )
    {
      retv = ACE_reinterpret_cast (void*, this);
    }
  else if (type == ACE_reinterpret_cast (
              ptr_arith_t,
              &::CORBA::Policy::_tao_class_id)
            )
    {
      retv =
        ACE_reinterpret_cast (
            void *,
            ACE_static_cast (
                CORBA::Policy_ptr,
                this
              )
          );
    }
  else if (type == ACE_reinterpret_cast (
               ptr_arith_t,
               &CORBA::Object::_tao_class_id)
             )
    {
      retv =
        ACE_reinterpret_cast (
            void *,
            ACE_static_cast (CORBA::Object_ptr, this)
          );
    }

  if (retv != 0)
    {
      this->_add_ref ();
    }

  return retv;
}

const char* Messaging::SyncScopePolicy::_interface_repository_id (void) const
{
  return "IDL:omg.org/Messaging/SyncScopePolicy:1.0";
}

CORBA::Boolean
Messaging::SyncScopePolicy::marshal (TAO_OutputCDR &)
{
  return 0;
}

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_typecode/typecode_defn.cpp:284

static const CORBA::Long _oc_Messaging_SyncScopePolicy[] =
{
    TAO_ENCAP_BYTE_ORDER, // byte order
  42,
  ACE_NTOHL (0x49444c3a),
  ACE_NTOHL (0x6f6d672e),
  ACE_NTOHL (0x6f72672f),
  ACE_NTOHL (0x4d657373),
  ACE_NTOHL (0x6167696e),
  ACE_NTOHL (0x672f5379),
  ACE_NTOHL (0x6e635363),
  ACE_NTOHL (0x6f706550),
  ACE_NTOHL (0x6f6c6963),
  ACE_NTOHL (0x793a312e),
  ACE_NTOHL (0x30000000),  // repository ID = IDL:omg.org/Messaging/SyncScopePolicy:1.0
    16,
  ACE_NTOHL (0x53796e63),
  ACE_NTOHL (0x53636f70),
  ACE_NTOHL (0x65506f6c),
  ACE_NTOHL (0x69637900),  // name = SyncScopePolicy
  };

static CORBA::TypeCode _tc_TAO_tc_Messaging_SyncScopePolicy (
    CORBA::tk_objref,
    sizeof (_oc_Messaging_SyncScopePolicy),
    (char *) &_oc_Messaging_SyncScopePolicy,
    0,
    sizeof (Messaging::SyncScopePolicy)
  );

TAO_NAMESPACE_TYPE (CORBA::TypeCode_ptr)
TAO_NAMESPACE_BEGIN (Messaging)
TAO_NAMESPACE_DEFINE (
    ::CORBA::TypeCode_ptr,
    _tc_SyncScopePolicy,
    &_tc_TAO_tc_Messaging_SyncScopePolicy
  )
TAO_NAMESPACE_END

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/any_op_cs.cpp:52

// Copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    Messaging::SyncScopePolicy_ptr _tao_elem
  )
{
  Messaging::SyncScopePolicy_ptr _tao_objptr =
    Messaging::SyncScopePolicy::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

// Non-copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    Messaging::SyncScopePolicy_ptr *_tao_elem
  )
{
  TAO::Any_Impl_T<Messaging::SyncScopePolicy>::insert (
      _tao_any,
      Messaging::SyncScopePolicy::_tao_any_destructor,
      Messaging::_tc_SyncScopePolicy,
      *_tao_elem
    );
}

CORBA::Boolean
operator>>= (
    const CORBA::Any &_tao_any,
    Messaging::SyncScopePolicy_ptr &_tao_elem
  )
{
  return
    TAO::Any_Impl_T<Messaging::SyncScopePolicy>::extract (
        _tao_any,
        Messaging::SyncScopePolicy::_tao_any_destructor,
        Messaging::_tc_SyncScopePolicy,
        _tao_elem
      );
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)  || \
    defined (ACE_HAS_GNU_REPO)
  template class TAO_Object_Manager<Messaging::SyncScopePolicy,Messaging::SyncScopePolicy_var>;
  template class TAO::Any_Impl_T<Messaging::SyncScopePolicy>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
# pragma instantiate TAO_Object_Manager<Messaging::SyncScopePolicy, Messaging::SyncScopePolicy_var>
# pragma instantiate TAO::Any_Impl_T<Messaging::SyncScopePolicy>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
