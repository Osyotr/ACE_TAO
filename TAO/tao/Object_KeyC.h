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
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be/be_codegen.cpp:151

#ifndef _TAO_IDL_ORIG_OBJECT_KEYC_H_
#define _TAO_IDL_ORIG_OBJECT_KEYC_H_

#include "ace/pre.h"

#include "tao/corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/TAO_Export.h"
#include "tao/Seq_Var_T.h"
#include "tao/Seq_Out_T.h"
#include "tao/Sequence_T.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO TAO_Export

#if defined (TAO_EXPORT_NESTED_CLASSES)
#  if defined (TAO_EXPORT_NESTED_MACRO)
#    undef TAO_EXPORT_NESTED_MACRO
#  endif /* defined (TAO_EXPORT_NESTED_MACRO) */
#  define TAO_EXPORT_NESTED_MACRO TAO_Export
#endif /* TAO_EXPORT_NESTED_CLASSES */

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:48

TAO_NAMESPACE  TAO
{

  // TAO_IDL - Generated from
  // be/be_visitor_sequence/sequence_ch.cpp:75

  class ObjectKey;

  typedef
    TAO_FixedSeq_Var_T<
        ObjectKey,
        CORBA::Octet
      >
    ObjectKey_var;

  typedef
    TAO_Seq_Out_T<
        ObjectKey,
        ObjectKey_var,
        CORBA::Octet
      >
    ObjectKey_out;

  class TAO_Export ObjectKey
    : public
        TAO_Unbounded_Sequence<
            CORBA::Octet
          >
  {
  public:
    ObjectKey (void);
    ObjectKey (CORBA::ULong max);
    ObjectKey (
        CORBA::ULong max,
        CORBA::ULong length,
        CORBA::Octet* buffer,
        CORBA::Boolean release = 0
      );
    ObjectKey (const ObjectKey &);
    ~ObjectKey (void);

    static void _tao_any_destructor (void *);

    typedef ObjectKey_var _var_type;

#if (TAO_NO_COPY_OCTET_SEQUENCES == 1)
    ObjectKey (
        CORBA::ULong length,
        const ACE_Message_Block* mb
      )
      : TAO_Unbounded_Sequence<CORBA::Octet> (length, mb) {}
#endif /* TAO_NO_COPY_OCTET_SEQUENCE == 1 */

    static void encode_sequence_to_string (
        char * &str,
        const TAO_Unbounded_Sequence<CORBA::Octet> &seq
      );
    static void decode_string_to_sequence (
        TAO_Unbounded_Sequence<CORBA::Octet> &seq,
        const char *str
      );

  };

  // TAO_IDL - Generated from
  // be/be_visitor_typecode/typecode_decl.cpp:44

  TAO_NAMESPACE_STORAGE_CLASS ::CORBA::TypeCode_ptr _tc_ObjectKey;

// TAO_IDL - Generated from
// be/be_visitor_module/module_ch.cpp:67

}
TAO_NAMESPACE_CLOSE // module TAO

// TAO_IDL - Generated from
// be/be_visitor_sequence/any_op_ch.cpp:52

TAO_Export void operator<<= (CORBA::Any &, const TAO::ObjectKey &); // copying version
TAO_Export void operator<<= (CORBA::Any &, TAO::ObjectKey*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, TAO::ObjectKey *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const TAO::ObjectKey *&);

// TAO_IDL - Generated from
// be/be_visitor_root/cdr_op.cpp:48

#ifndef __ACE_INLINE__

// TAO_IDL - Generated from
// be/be_visitor_sequence/cdr_op_ch.cpp:57

#if !defined _TAO_CDR_OP_TAO_ObjectKey_H_
#define _TAO_CDR_OP_TAO_ObjectKey_H_

TAO_Export CORBA::Boolean operator<< (
    TAO_OutputCDR &,
    const TAO::ObjectKey &
  );
TAO_Export CORBA::Boolean operator>> (
    TAO_InputCDR &,
    TAO::ObjectKey &
  );

#endif /* _TAO_CDR_OP_TAO_ObjectKey_H_ */

// TAO_IDL - Generated from
// be/be_visitor_root/cdr_op.cpp:64

#endif /* __ACE_INLINE__ */

// TAO_IDL - Generated from
// be/be_codegen.cpp:1018

#if defined (__ACE_INLINE__)
#include "Object_KeyC.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#include "ace/post.h"
#endif /* ifndef */
