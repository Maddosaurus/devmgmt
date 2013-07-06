#include "udpsender.h"



//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//



UdpSender::UdpSender(boost::asio::io_service& io_service, const boost::asio::ip::address& multicast_address, const std::string &message) : endpoint_(multicast_address, multicast_port), socket_(io_service, endpoint_.protocol()), timer_(io_service), message_count_(0)
{
    //std::ostringstream os;
    //os << "Message " << message_count_++;
    //os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><e:Envelope xmlns:e=\"http://www.w3.org/2003/05/soap-envelope\"xmlns:w=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\"xmlns:dn=\"http://www.onvif.org/ver10/network/wsdl\"><e:Header><w:MessageID>uuid:84ede3de-7dec-11d0-c360-f01234567890</w:MessageID><w:To e:mustUnderstand=\"true\">urn:schemas-xmlsoap-org:ws:2005:04:discovery</w:To><w:Actiona:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</w:Action></e:Header><e:Body><d:Probe><d:Types>dn:NetworkVideoTransmitter</d:Types></d:Probe></e:Body></e:Envelope>";

    //os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\"><SOAP-ENV:Body><tds:GetSystemDateAndTime/></SOAP-ENV:Body></SOAP-ENV:Envelope>";
    /*
<?xml version="1.0" encoding="UTF-8"?><e:Envelope xmlns:e="http://www.w3.org/2003/05/soap-envelope"xmlns:w="http://schemas.xmlsoap.org/ws/2004/08/addressing"xmlns:d="http://schemas.xmlsoap.org/ws/2005/04/discovery"xmlns:dn="http://www.onvif.org/ver10/network/wsdl"><e:Header><w:MessageID>uuid:84ede3de-7dec-11d0-c360-f01234567890</w:MessageID><w:To e:mustUnderstand="true">urn:schemas-xmlsoap-org:ws:2005:04:discovery</w:To><w:Actiona:mustUnderstand="true">http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</w:Action></e:Header><e:Body><d:Probe><d:Types>dn:NetworkVideoTransmitter</d:Types></d:Probe></e:Body></e:Envelope>
      */

    message_ = message;

    socket_.async_send_to(
        boost::asio::buffer(message_), endpoint_,
        boost::bind(&UdpSender::handle_send_to, this,
          boost::asio::placeholders::error));
}

void UdpSender::handle_send_to(const boost::system::error_code& error)
{
    if (!error && message_count_ < max_message_count)
    {
      timer_.expires_from_now(boost::posix_time::seconds(1));
      timer_.async_wait(
          boost::bind(&UdpSender::handle_timeout, this,
            boost::asio::placeholders::error));
    }
}

void UdpSender::handle_timeout(const boost::system::error_code& error)
{
    if (!error)
    {
      std::ostringstream os;
      os << "Message " << message_count_++;
      message_ = os.str();

      socket_.async_send_to(
          boost::asio::buffer(message_), endpoint_,
          boost::bind(&UdpSender::handle_send_to, this,
            boost::asio::placeholders::error));
    }
}


/*
int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: sender <multicast_address>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    sender 239.255.0.1\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    sender ff31::8000:1234\n";
      return 1;
    }

    boost::asio::io_service io_service;
    sender s(io_service, boost::asio::ip::address::from_string(argv[1]));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
} */
