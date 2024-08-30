#include "user_if.h"
#include <boost/thread.hpp>

User_IF::User_IF()
{
    this->argc = 2;
    // Initialize DomainParticipantFactory
    std::vector<std::string> arguments;
    arguments.push_back("-DCPSConfigFile");
    arguments.push_back(RTPS_INIT_LOCATION);

    std::vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);

    this->dpf = TheParticipantFactoryWithArgs(this->argc, (ACE_TCHAR**)argv.data());

    // Create DomainParticipant
    this->participant = this->dpf->create_participant( 42
                                        , PARTICIPANT_QOS_DEFAULT
                                        , 0
                                        , OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!this->participant) {
      std::cout << "Cannot create participant" << std::endl;
    }

    // Create Publisher
    this->publisher = this->participant->create_publisher(PUBLISHER_QOS_DEFAULT
                                        , 0
                                        , OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    
    if (!this->publisher) {
        std::cout << "Cannot create publisher" << std::endl;
    }

    // Create Subscriber
    this->subscriber = this->participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT
                                        , 0
                                        , OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!this->subscriber) {
        std::cout << "Cannot create subscriber" << std::endl;
    }

    this->registerTopic();
    this->initMsg();                                        
}

User_IF::~User_IF()
{
    this->participant->delete_contained_entities();
    this->dpf->delete_participant(this->participant);
    TheServiceParticipant->shutdown();
}

void User_IF::registerTopic()
{
    // Register TypeSupport (MessengerTopic::Message)
    this->msg_ts = new MessengerTopic::MessageTypeSupportImpl();

    if (this->msg_ts->register_type(this->participant, "") != DDS::RETCODE_OK) {
        std::cout << "register_type failed!" << std::endl;
    }

    this->msg_topic = this->participant->create_topic("Message"
                                                        , this->msg_ts->get_type_name()
                                                        , TOPIC_QOS_DEFAULT
                                                        , 0
                                                        , OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!this->msg_topic) {
        std::cout << "Cannot create topic" << std::endl;
    }          
    /*------------------------------------------------------------------------------------------*/                                              
    // Can add other topics here
    // ...
    /*------------------------------------------------------------------------------------------*/
}

void User_IF::initMsg()
{
    this->msg.from = "OpenDDS";
    this->msg.subject = "Hello, World!";
    this->msg.subject_id = 5;
    this->msg.text = "Welcome baby";

}

// void User_IF::createMessengerWriter(bool is_block)
// {
//     this->publisher->get_default_datawriter_qos(this->msg_writer_qos);
//     this->msg_writer_qos.reliability.kind = DDS::RELIABLE_RELIABILITY_QOS;
    
//     //Match QoS with createCarlaControlReader for compatible, read more in OPENDDS docs
//     this->msg_writer_qos.liveliness.kind = DDS::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
//     this->msg_writer_qos.liveliness.lease_duration.sec = 1;
//     this->msg_writer_qos.liveliness.lease_duration.nanosec = 0;
    
//     this->msg_writer = this->publisher->create_datawriter(this->msg_topic
//                                     , msg_writer_qos
//                                     , 0
//                                     , OpenDDS::DCPS::DEFAULT_STATUS_MASK);
//     if (!this->msg_writer) {
//         // ERROR("Fail create carla status writer");
//         return;
//     }

//     this->msg_writer = MessengerTopic::MessageDataWriter::_narrow(this->msg_writer);
//     if (!this->msg_writer) {
//         // ERROR("Fail create carla control data writer");
//     }
//     waitForSub(is_block
//                 , this->msg_writer);
// }

// void User_IF::waitForSub(bool is_block
//                             , DDS::DataWriter_var writer)
// {
//     if (true == is_block) {
//         User_IF::waitForSubThread(writer);
//     }
//     else {
//         boost::thread sub_wait = boost::thread(&User_IF::waitForSubThread
//                                         , this
//                                         , writer);
//         sub_wait.detach();
//     }
// }

// void User_IF::waitForSubThread(DDS::DataWriter_var writer)
// {
//     // Block until Subscriber is available
//     DDS::StatusCondition_var condition = writer->get_statuscondition();
//     condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

//     DDS::WaitSet_var ws = new DDS::WaitSet;
//     ws->attach_condition(condition);

//     while (true) {
//         int matches = getPublicationMatchedCount(writer);
//         if (matches < 0) {
//             break;
//         }

//         if (matches >= 1) {
//             break;
//         }
        

//         DDS::ConditionSeq conditions;
//         DDS::Duration_t timeout = {60, 0};
//         if (ws->wait(conditions, timeout) != DDS::RETCODE_OK) {
//             std::cout << "wait failed" << std::endl;
//         }
//     }
//     std::cout << "wait finished" << std::endl;
//     ws->detach_condition(condition);
// }

// int User_IF::getPublicationMatchedCount(DDS::DataWriter_var writer)
// {
//     DDS::PublicationMatchedStatus matches;
//     if (writer->get_publication_matched_status(matches) != DDS::RETCODE_OK) {
//         // ERROR("get_publication_matched_status failed");
//         return -1;
//     }

//     return matches.current_count;
// }
int main()
{
    return 0;
}