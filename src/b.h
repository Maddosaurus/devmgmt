// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/

#ifndef _b_h_
#define _b_h_

#include <list>
#include <string>
#include <staff/common/Optional.h>
#include <staff/common/WsdlTypes.h>
#include <staff/common/DataObject.h>
#include <staff/common/Attribute.h>
#include <staff/common/QName.h>
#include <staff/common/Nillable.h>
#include "ws_addr.h"
#include "bf.h"
#include "t.h"

// *interface.attributeFormDefault: unqualified
// *interface.elementFormDefault: qualified
// *interface.targetNamespace: http://docs.oasis-open.org/wsn/b-2

  struct TopicExpressionType;
  struct FilterType;
  struct SubscriptionPolicyType;
  struct NotificationMessageHolderType;
  struct SubscribeCreationFailedFaultType;
  struct InvalidFilterFaultType;
  struct TopicExpressionDialectUnknownFaultType;
  struct InvalidTopicExpressionFaultType;
  struct TopicNotSupportedFaultType;
  struct MultipleTopicsSpecifiedFaultType;
  struct InvalidProducerPropertiesExpressionFaultType;
  struct InvalidMessageContentExpressionFaultType;
  struct UnrecognizedPolicyRequestFaultType;
  struct UnsupportedPolicyRequestFaultType;
  struct NotifyMessageNotSupportedFaultType;
  struct UnacceptableInitialTerminationTimeFaultType;
  struct NoCurrentMessageOnTopicFaultType;
  struct UnableToGetMessagesFaultType;
  struct UnableToDestroyPullPointFaultType;
  struct UnableToCreatePullPointFaultType;
  struct UnacceptableTerminationTimeFaultType;
  struct UnableToDestroySubscriptionFaultType;
  struct PauseFailedFaultType;
  struct ResumeFailedFaultType;
  struct NotificationProducerRP;
  struct SubscriptionManagerRP;
  struct Notify;
  struct UseRaw;
  struct Subscribe;
  struct SubscribeResponse;
  struct GetCurrentMessage;
  struct GetCurrentMessageResponse;
  struct GetMessages;
  struct GetMessagesResponse;
  struct DestroyPullPoint;
  struct DestroyPullPointResponse;
  struct CreatePullPoint;
  struct CreatePullPointResponse;
  struct Renew;
  struct RenewResponse;
  struct Unsubscribe;
  struct UnsubscribeResponse;
  struct PauseSubscription;
  struct PauseSubscriptionResponse;
  struct ResumeSubscription;
  struct ResumeSubscriptionResponse;


  // *restriction-union: xsd:dateTime xsd:duration
  typedef std::string AbsoluteOrRelativeTimeType;

  struct TopicExpressionType
  {
    // *useParentElement: true
    staff::Optional<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
    // *isAttribute: true
    staff::anyURI Dialect;
  };

  struct FilterType
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct SubscriptionPolicyType
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct NotificationMessageHolderType
  {
    struct Message
    {
      // *useParentElement: true
      staff::DataObject tUnnamed0;
    };

    staff::Optional< ::EndpointReferenceType > SubscriptionReference;
    staff::Optional< ::TopicExpressionType > Topic;
    staff::Optional< ::EndpointReferenceType > ProducerReference;
    struct ::NotificationMessageHolderType::Message Message;
  };

  struct SubscribeCreationFailedFaultType: public ::BaseFaultType
  {
  };

  struct InvalidFilterFaultType: public ::BaseFaultType
  {
    // *useParentElement: true
    std::list<staff::QName> UnknownFilter;
  };

  struct TopicExpressionDialectUnknownFaultType: public ::BaseFaultType
  {
  };

  struct InvalidTopicExpressionFaultType: public ::BaseFaultType
  {
  };

  struct TopicNotSupportedFaultType: public ::BaseFaultType
  {
  };

  struct MultipleTopicsSpecifiedFaultType: public ::BaseFaultType
  {
  };

  struct InvalidProducerPropertiesExpressionFaultType: public ::BaseFaultType
  {
  };

  struct InvalidMessageContentExpressionFaultType: public ::BaseFaultType
  {
  };

  struct UnrecognizedPolicyRequestFaultType: public ::BaseFaultType
  {
    // *useParentElement: true
    std::list<staff::QName> UnrecognizedPolicy;
  };

  struct UnsupportedPolicyRequestFaultType: public ::BaseFaultType
  {
    // *useParentElement: true
    std::list<staff::QName> UnsupportedPolicy;
  };

  struct NotifyMessageNotSupportedFaultType: public ::BaseFaultType
  {
  };

  struct UnacceptableInitialTerminationTimeFaultType: public ::BaseFaultType
  {
    staff::dateTime MinimumTime;
    staff::Optional<staff::dateTime> MaximumTime;
  };

  struct NoCurrentMessageOnTopicFaultType: public ::BaseFaultType
  {
  };

  struct UnableToGetMessagesFaultType: public ::BaseFaultType
  {
  };

  struct UnableToDestroyPullPointFaultType: public ::BaseFaultType
  {
  };

  struct UnableToCreatePullPointFaultType: public ::BaseFaultType
  {
  };

  struct UnacceptableTerminationTimeFaultType: public ::BaseFaultType
  {
    staff::dateTime MinimumTime;
    staff::Optional<staff::dateTime> MaximumTime;
  };

  struct UnableToDestroySubscriptionFaultType: public ::BaseFaultType
  {
  };

  struct PauseFailedFaultType: public ::BaseFaultType
  {
  };

  struct ResumeFailedFaultType: public ::BaseFaultType
  {
  };

  struct NotificationProducerRP
  {
    // *useParentElement: true
    std::list< ::TopicExpressionType > TopicExpression;
    // *defaultValue: true
    staff::Optional<bool> FixedTopicSet;
    // *useParentElement: true
    std::list<staff::anyURI> TopicExpressionDialect;
    staff::Optional< ::TopicSetType > TopicSet;

    NotificationProducerRP():
      FixedTopicSet(true)
    {
    }
  };

  struct SubscriptionManagerRP
  {
    ::EndpointReferenceType ConsumerReference;
    staff::Optional< ::FilterType > Filter;
    staff::Optional< ::SubscriptionPolicyType > SubscriptionPolicy;
    staff::Optional<staff::dateTime> CreationTime;
  };

  struct Notify
  {
    // *useParentElement: true
    std::list< ::NotificationMessageHolderType > NotificationMessage;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct UseRaw
  {
  };

  struct Subscribe
  {
    struct SubscriptionPolicy
    {
      // *useParentElement: true
      std::list<staff::DataObject> tUnnamed0;
    };

    ::EndpointReferenceType ConsumerReference;
    staff::Optional< ::FilterType > Filter;
    staff::Optional< staff::Nillable< ::AbsoluteOrRelativeTimeType > > InitialTerminationTime;
    staff::Optional<struct ::Subscribe::SubscriptionPolicy> SubscriptionPolicy;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct SubscribeResponse
  {
    ::EndpointReferenceType SubscriptionReference;
    staff::Optional<staff::dateTime> CurrentTime;
    staff::Optional< staff::Nillable<staff::dateTime> > TerminationTime;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct GetCurrentMessage
  {
    ::TopicExpressionType Topic;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct GetCurrentMessageResponse
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct GetMessages
  {
    staff::Optional<staff::nonNegativeInteger> MaximumNumber;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct GetMessagesResponse
  {
    // *useParentElement: true
    std::list< ::NotificationMessageHolderType > NotificationMessage;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct DestroyPullPoint
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct DestroyPullPointResponse
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct CreatePullPoint
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct CreatePullPointResponse
  {
    ::EndpointReferenceType PullPoint;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
    staff::anyAttribute lsAnyAttributes;
  };

  struct Renew
  {
    staff::Nillable< ::AbsoluteOrRelativeTimeType > TerminationTime;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct RenewResponse
  {
    staff::Nillable<staff::dateTime> TerminationTime;
    staff::Optional<staff::dateTime> CurrentTime;
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct Unsubscribe
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct UnsubscribeResponse
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct PauseSubscription
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct PauseSubscriptionResponse
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct ResumeSubscription
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };

  struct ResumeSubscriptionResponse
  {
    // *useParentElement: true
    std::list<staff::DataObject> tUnnamed0;
  };


#endif // _b_h_

