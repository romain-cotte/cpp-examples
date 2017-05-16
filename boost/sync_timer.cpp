/**
 * Please visit http://www.bogotobogo.com/cplusplus/Boost/boost_AsynchIO_asio_tcpip_socket_server_client_timer_A.php
 */
#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main() {
  boost::asio::io_service io;

  for (int i = 0; i < 5; i++) {
    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(i));
    timer.wait();
    std::cout << "Blocking wait(): " << i << " second-wait\n";
  }

  return 0;
}
