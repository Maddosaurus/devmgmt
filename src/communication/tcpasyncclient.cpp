//
// TcpAsyncClient.cpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "tcpasyncclient.h"

void TcpAsyncClient::handle_resolve(const boost::system::error_code& err,
    tcp::resolver::iterator endpoint_iterator)
{
  if (!err)
  {
    // Attempt a connection to each endpoint in the list until we
    // successfully establish a connection.
    //boost::asio::async_connect(socket_, endpoint_iterator,
    boost::asio::async_connect(socket_, endpoint_iterator,
        boost::bind(&TcpAsyncClient::handle_connect, this,
          boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err.message() << "\n";
  }
}

void TcpAsyncClient::handle_connect(const boost::system::error_code& err)
{
  if (!err)
  {
    // The connection was successful. Send the request.
    boost::asio::async_write(socket_, request_,
        boost::bind(&TcpAsyncClient::handle_write_request, this,
          boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err.message() << "\n";
  }
}

void TcpAsyncClient::handle_write_request(const boost::system::error_code& err)
{
  if (!err)
  {
    // Read the response status line. The response_ streambuf will
    // automatically grow to accommodate the entire line. The growth may be
    // limited by passing a maximum size to the streambuf constructor.
    boost::asio::async_read_until(socket_, response_, "\r\n",
        boost::bind(&TcpAsyncClient::handle_read_status_line, this,
          boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err.message() << "\n";
  }
}

void TcpAsyncClient::handle_read_status_line(const boost::system::error_code& err)
{
  if (!err)
  {
    // Check that response is OK.
    std::istream response_stream(&response_);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      return;
    }
    if (status_code != 200)
    {
      std::cout << "Response returned with status code ";
      std::cout << status_code << "\n";
      return;
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
        boost::bind(&TcpAsyncClient::handle_read_headers, this,
          boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err << "\n";
  }
}

void TcpAsyncClient::handle_read_headers(const boost::system::error_code& err)
{
  if (!err)
  {
    // Process the response headers.
    std::istream response_stream(&response_);
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
      //std::cout << header << "\n";
    //std::cout << "\n";

    // Write whatever content we already have to output.
    if (response_.size() > 0)
      //std::cout << &response_;

    //clear the stringstream before using it to search for the URI
    os.str("");

    // Start reading remaining data until EOF.
    boost::asio::async_read(socket_, response_,
        boost::asio::transfer_at_least(1),
        boost::bind(&TcpAsyncClient::handle_read_content, this,
          boost::asio::placeholders::error));
  }
  else
  {
    std::cout << "Error: " << err << "\n";
  }
}

//!
//! \brief TcpAsyncClient::handle_read_content Änderungen: Nur noch IP-Adresse ausgeben.
//! \param err
//!
void TcpAsyncClient::handle_read_content(const boost::system::error_code& err)
{
  if (!err)
  {
    os<<&response_;
    std::string ergebnis="";

    // Continue reading remaining data until EOF.
    boost::asio::async_read(socket_, response_,
        boost::asio::transfer_at_least(1),
        boost::bind(&TcpAsyncClient::handle_read_content, this,
          boost::asio::placeholders::error));

    //Gesucht ist der Bereich zwischen <tt:Uri> und </tt:Uri>.
    //Das Ganze nun um 8 nach rechts verschoben, um den XML-Tag nicht mit in der Ausgabe zu haben
    std::size_t found = os.str().find("<tt:Uri>");
      if (found!=std::string::npos){
          std::size_t foundEnd = os.str().find("</tt:Uri>");
            if (found!=std::string::npos){
                ergebnis = os.str().substr(found+8, foundEnd-found-8);
                //std::cout << ergebnis << std::endl;
                this->foundURI = ergebnis;
                return;
            }
            else{
                std::cout << "No end found!!\n";
            }
      }
  }
  else if (err != boost::asio::error::eof)
  {
    std::cout << "Error: " << err << "\n";
  }
}


TcpAsyncClient::TcpAsyncClient(boost::asio::io_service& io_service,
    const std::string& server, const std::string& path, const std::string &message)
  : resolver_(io_service),
    socket_(io_service)
{
  // Form the request. We specify the "Connection: close" header so that the
  // server will close the socket after transmitting the response. This will
  // allow us to treat all data up until the EOF as the content.
  std::ostream request_stream(&request_);
  request_stream << "POST " << path << " HTTP/1.0\r\n";
  request_stream << "Host: " << server << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Connection: close\r\n\r\n";

  request_stream << message;

  // Start an asynchronous resolve to translate the server and service names
  // into a list of endpoints.
  tcp::resolver::query query(server, "http");
  resolver_.async_resolve(query,
      boost::bind(&TcpAsyncClient::handle_resolve, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::iterator));
}

std::string TcpAsyncClient::getURI(){
    return this->foundURI;
}
