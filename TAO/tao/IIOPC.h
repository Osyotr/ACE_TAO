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
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_codegen.cpp:151

#ifndef _TAO_IDL_ORIG_IIOPC_H_
#define _TAO_IDL_ORIG_IIOPC_H_

#include "ace/pre.h"
#include "tao/Sequence_T.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "CDR.h"
#include "tao/VarOut_T.h"
#include "tao/Seq_Out_T.h"
#include "tao/Seq_Var_T.h"

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
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_module/module_ch.cpp:48

TAO_NAMESPACE  IIOP
{

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_type.cpp:231

  struct ListenPoint;

  typedef
    TAO_Var_Var_T<
        ListenPoint
      >
    ListenPoint_var;

  typedef
    TAO_Out_T<
        ListenPoint,
        ListenPoint_var
      >
    ListenPoint_out;

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/structure_ch.cpp:52

  struct TAO_Export ListenPoint
  {
    typedef ListenPoint_var _var_type;

    static void _tao_any_destructor (void *);
    TAO_String_Manager host;
    CORBA::UShort port;
  };

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_typecode/typecode_decl.cpp:44

  TAO_NAMESPACE_STORAGE_CLASS ::CORBA::TypeCode_ptr _tc_ListenPoint;

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_sequence/sequence_ch.cpp:75

  class ListenPointList;

  typedef
    TAO_VarSeq_Var_T<
        ListenPointList,
        IIOP::ListenPoint
      >
    ListenPointList_var;

  typedef
    TAO_Seq_Out_T<
        ListenPointList,
        ListenPointList_var,
        IIOP::ListenPoint
      >
    ListenPointList_out;

  class TAO_Export ListenPointList
    : public
        TAO_Unbounded_Sequence<
            IIOP::ListenPoint
          >
  {
  public:
    ListenPointList (void);
    ListenPointList (CORBA::ULong max);
    ListenPointList (
        CORBA::ULong max,
        CORBA::ULong length,
        ListenPoint *buffer,
        CORBA::Boolean release = 0
      );
    ListenPointList (const ListenPointList &);
    ~ListenPointList (void);

    static void _tao_any_destructor (void *);

    typedef ListenPointList_var _var_type;
  };

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_typecode/typecode_decl.cpp:44

  TAO_NAMESPACE_STORAGE_CLASS ::CORBA::TypeCode_ptr _tc_ListenPointList;

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_type.cpp:231

  struct BiDirIIOPServiceContext;

  typedef
    TAO_Var_Var_T<
        BiDirIIOPServiceContext
      >
    BiDirIIOPServiceContext_var;

  typedef
    TAO_Out_T<
        BiDirIIOPServiceContext,
        BiDirIIOPServiceContext_var
      >
    BiDirIIOPServiceContext_out;

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/structure_ch.cpp:52

  struct TAO_Export BiDirIIOPServiceContext
  {
    typedef BiDirIIOPServiceContext_var _var_type;

    static void _tao_any_destructor (void *);
    IIOP::ListenPointList listen_points;
  };

  // TAO_IDL - Generated from
  // W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_typecode/typecode_decl.cpp:44

  TAO_NAMESPACE_STORAGE_CLASS ::CORBA::TypeCode_ptr _tc_BiDirIIOPServiceContext;

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_module/module_ch.cpp:67

}
TAO_NAMESPACE_CLOSE // module IIOP

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/any_op_ch.cpp:52

TAO_Export void operator<<= (CORBA::Any &, const IIOP::ListenPoint &); // copying version
TAO_Export void operator<<= (CORBA::Any &, IIOP::ListenPoint*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, IIOP::ListenPoint *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const IIOP::ListenPoint *&);

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_sequence/any_op_ch.cpp:52

TAO_Export void operator<<= (CORBA::Any &, const IIOP::ListenPointList &); // copying version
TAO_Export void operator<<= (CORBA::Any &, IIOP::ListenPointList*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, IIOP::ListenPointList *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const IIOP::ListenPointList *&);

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/any_op_ch.cpp:52

TAO_Export void operator<<= (CORBA::Any &, const IIOP::BiDirIIOPServiceContext &); // copying version
TAO_Export void operator<<= (CORBA::Any &, IIOP::BiDirIIOPServiceContext*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, IIOP::BiDirIIOPServiceContext *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const IIOP::BiDirIIOPServiceContext *&);

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_root/cdr_op.cpp:48

#ifndef __ACE_INLINE__

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/cdr_op_ch.cpp:54

TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const IIOP::ListenPoint &);
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, IIOP::ListenPoint &);

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_sequence/cdr_op_ch.cpp:57

#if !defined _TAO_CDR_OP_IIOP_ListenPointList_H_
#define _TAO_CDR_OP_IIOP_ListenPointList_H_

TAO_Export CORBA::Boolean operator<< (
    TAO_OutputCDR &,
    const IIOP::ListenPointList &
  );
TAO_Export CORBA::Boolean operator>> (
    TAO_InputCDR &,
    IIOP::ListenPointList &
  );

#endif /* _TAO_CDR_OP_IIOP_ListenPointList_H_ */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/cdr_op_ch.cpp:54

TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const IIOP::BiDirIIOPServiceContext &);
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, IIOP::BiDirIIOPServiceContext &);

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_root/cdr_op.cpp:64

#endif /* __ACE_INLINE__ */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_codegen.cpp:1018

#if defined (__ACE_INLINE__)
#include "IIOPC.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#include "ace/post.h"
#endif /* ifndef */
