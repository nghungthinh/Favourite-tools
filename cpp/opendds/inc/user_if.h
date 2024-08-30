#include <ace/Log_Msg.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DdsDcpsSubscriptionC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include <dds/DCPS/StaticIncludes.h>
#ifdef ACE_AS_STATIC_LIBS
#  include <dds/DCPS/RTPS/RtpsDiscovery.h>
#  include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif

#include "DataReaderListenerImpl.h"
#include "MessengerTopicTypeSupportImpl.h"

#include <iostream>
#include <vector>
#include <pthread.h>

#define RTPS_INIT_LOCATION "../opendds_configs/rtps.ini"

class MessengerListenerImpl;

class User_IF {
private:
    int argc;
    std::vector<char *> argv;

    DDS::DomainParticipantFactory_var dpf;
    DDS::DomainParticipant_var participant;

    DDS::Publisher_var publisher;
    DDS::Subscriber_var subscriber;

    /* Messenger Topic*/
    MessengerTopic::MessageTypeSupport_var msg_ts;
    MessengerTopic::MessageDataWriter_var msg_msg_writer;
    MessengerTopic::Message msg;
    DDS::Topic_var msg_topic;
    DDS::DataReaderListener_var msg_listener;
    DDS::DataReader_var msg_reader;
    DDS::DataWriter_var msg_writer;
    DDS::DataReaderQos msg_reader_qos;
    DDS::DataWriterQos msg_writer_qos;
    
    void registerTopic();
    // void createPublisher();
    // void createSubscriber();
    void waitForSub(bool is_block, DDS::DataWriter_var writer);
    void waitForSubThread(DDS::DataWriter_var writer);
    int getPublicationMatchedCount(DDS::DataWriter_var writer);
    void initMsg();

    void *context;
public:
    User_IF();
    virtual ~User_IF();
    MessengerListenerImpl *listener_servant_msg;

    void createMessengerWriter(bool is_block);
    // void createMessengerReader(void (*message_arrived_cb)(void *, MessengerTopic::Messenger *));

    // // Messenger
    // bv_err_return_t setMessengerMsg(Messenger::Messenger &msg);
};