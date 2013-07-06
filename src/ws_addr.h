// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/

#ifndef _ws_addr_h_
#define _ws_addr_h_

#include <list>
#include <string>
#include <staff/common/Optional.h>
#include <staff/common/WsdlTypes.h>
#include <staff/common/DataObject.h>
#include <staff/common/Attribute.h>
#include <staff/common/QName.h>

// *interface.attributeFormDefault: unqualified
// *interface.blockDefault: #all
// *interface.elementFormDefault: qualified
// *interface.finalDefault: 
// *interface.targetNamespace: http://www.w3.org/2005/08/addressing

  struct EndpointReferenceType;
  struct ReferenceParametersType;
  struct MetadataType;
  struct RelatesToType;
  struct AttributedAnyType;
  struct ProblemActionType;


  // *restriction-union: tns:RelationshipType xs:anyURI
  typedef std::string RelationshipTypeOpenEnum;

  // *restriction-union: tns:FaultCodesType xs:QName
  typedef std::string FaultCodesOpenEnumType;
  typedef staff::anyURI AttributedURIType;
  typedef unsigned long AttributedUnsignedLongType;
  typedef staff::QName AttributedQNameType;

  // *baseType: anyURI
  enum RelationshipType
  {
    // *value: http://www.w3.org/2005/08/addressing/reply
    http___www_w3_org_2005_08_addressing_reply
  };

  // *baseType: QName
  enum FaultCodesType
  {
    // *value: tns:InvalidAddressingHeader
    tns_InvalidAddressingHeader,
    // *value: tns:InvalidAddress
    tns_InvalidAddress,
    // *value: tns:InvalidEPR
    tns_InvalidEPR,
    // *value: tns:InvalidCardinality
    tns_InvalidCardinality,
    // *value: tns:MissingAddressInEPR
    tns_MissingAddressInEPR,
    // *value: tns:DuplicateMessageID
    tns_DuplicateMessageID,
    // *value: tns:ActionMismatch
    tns_ActionMismatch,
    // *value: tns:MessageAddressingHeaderRequired
    tns_MessageAddressingHeaderRequired,
    // *value: tns:DestinationUnreachable
    tns_DestinationUnreachable,
    // *value: tns:ActionNotSupported
    tns_ActionNotSupported,
    // *value: tns:EndpointUnavailable
    tns_EndpointUnavailable
  };

  struct EndpointReferenceType
  {
    ::AttributedURIType Address;
    staff::Optional< ::ReferenceParametersType > ReferenceParameters;
    staff::Optional< ::MetadataType > Metadata;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct ReferenceParametersType
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct MetadataType
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct RelatesToType
  {
    // *useParentElement: true
    staff::anyURI tParent;
    // *defaultValue: http://www.w3.org/2005/08/addressing/reply
    // *isAttribute: true
    staff::Optional< ::RelationshipTypeOpenEnum > RelationshipType;

    RelatesToType():
      RelationshipType("http://www.w3.org/2005/08/addressing/reply")
    {
    }
  };

  struct AttributedAnyType
  {
    // *useParentElement: true
    staff::DataObject tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct ProblemActionType
  {
    staff::Optional< ::AttributedURIType > Action;
    staff::Optional<staff::anyURI> SoapAction;
    staff::anyAttribute lsAnyAttributes;
  };


#endif // _ws_addr_h_

