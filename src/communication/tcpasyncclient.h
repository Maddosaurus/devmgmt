//
// TcpAsyncClient.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TCPASYNCCLIENT_H
#define TCPASYNCCLIENT_H

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class TcpAsyncClient
{
private:
    std::ostringstream os;
    std::string foundURI;

    tcp::resolver resolver_;
    tcp::socket socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;

    void handle_resolve(const boost::system::error_code& err, tcp::resolver::iterator endpoint_iterator);
    void handle_connect(const boost::system::error_code& err);
    void handle_write_request(const boost::system::error_code& err);
    void handle_read_status_line(const boost::system::error_code& err);
    void handle_read_headers(const boost::system::error_code& err);
    void handle_read_content(const boost::system::error_code& err);

public:
    TcpAsyncClient(boost::asio::io_service& io_service, const std::string& server, const std::string& path, const std::string &message);
    std::string getURI();
};

#endif // TCPASYNCCLIENT_H
