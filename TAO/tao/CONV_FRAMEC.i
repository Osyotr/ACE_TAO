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
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_sequence/cdr_op_ci.cpp:84

#if !defined _TAO_CDR_OP_CONV_FRAME_CodeSetComponent__tao_seq_CodeSetId_I_
#define _TAO_CDR_OP_CONV_FRAME_CodeSetComponent__tao_seq_CodeSetId_I_

CORBA::Boolean TAO_Export operator<< (
    TAO_OutputCDR &,
    const CONV_FRAME::CodeSetComponent::_tao_seq_CodeSetId &
  );

CORBA::Boolean TAO_Export operator>> (
    TAO_InputCDR &,
    CONV_FRAME::CodeSetComponent::_tao_seq_CodeSetId &
  );

#endif /* _TAO_CDR_OP_CONV_FRAME_CodeSetComponent__tao_seq_CodeSetId_I_ */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/cdr_op_ci.cpp:71

ACE_INLINE
CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const CONV_FRAME::CodeSetComponent &_tao_aggregate
  )
{
  if (
    (strm << _tao_aggregate.native_code_set) &&
    (strm << _tao_aggregate.conversion_code_sets)
   )
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

ACE_INLINE
CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    CONV_FRAME::CodeSetComponent &_tao_aggregate
  )
{
  if (
    (strm >> _tao_aggregate.native_code_set) &&
    (strm >> _tao_aggregate.conversion_code_sets)
   )
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/cdr_op_ci.cpp:71

ACE_INLINE
CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const CONV_FRAME::CodeSetComponentInfo &_tao_aggregate
  )
{
  if (
    (strm << _tao_aggregate.ForCharData) &&
    (strm << _tao_aggregate.ForWcharData)
   )
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

ACE_INLINE
CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    CONV_FRAME::CodeSetComponentInfo &_tao_aggregate
  )
{
  if (
    (strm >> _tao_aggregate.ForCharData) &&
    (strm >> _tao_aggregate.ForWcharData)
   )
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_structure/cdr_op_ci.cpp:71

ACE_INLINE
CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const CONV_FRAME::CodeSetContext &_tao_aggregate
  )
{
  if (
    (strm << _tao_aggregate.char_data) &&
    (strm << _tao_aggregate.wchar_data)
   )
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

ACE_INLINE
CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    CONV_FRAME::CodeSetContext &_tao_aggregate
  )
{
  if (
    (strm >> _tao_aggregate.char_data) &&
    (strm >> _tao_aggregate.wchar_data)
   )
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

