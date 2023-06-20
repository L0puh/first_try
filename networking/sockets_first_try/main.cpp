#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif 
#define ASIO_STANDALONE

#include <iostream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <chrono>
std::vector<char> vBuffer(20 * 1024);

int error_handler(asio::error_code er);

std::vector<char> vbuffer(20 * 1024); // make a frame of size of data 
void get_some_data(asio::ip::tcp::socket& socket);
void print_content(std::error_code error, std::size_t length, asio::ip::tcp::socket& socket);

int main() {
	asio::error_code er;
	asio::io_context context; //create the interface 
	asio::io_context::work idleWork(context); // fake work until aysnc func gives data
	std::thread thrContext = std::thread([&]() { context.run(); }); // start the context in own thread
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", er), 80); //get an address
	asio::ip::tcp::socket socket(context); // create a socket
	socket.connect(endpoint, er); // try to connect 
	error_handler(er);
	
	if (socket.is_open()) {
		get_some_data(socket);
		
		std::string req = // make a request 
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";
		socket.write_some(asio::buffer(req.data(), req.size()), er);
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(20000ms);
		
	}
	return 0;
}

int error_handler(asio::error_code er) {
	
	if (er) {
		std::cout << er.message() << '\n';
	}
	return 0;
}

void print_content(std::error_code error, std::size_t length, asio::ip::tcp::socket& socket) {

	if (!error) {
		std::cout << "\n\n READ: " << length << "bytes\n\n";
		for (int i = 0; i < length; i++)
			std::cout << vbuffer[i];
		get_some_data(socket);
	}
	else {
		error_handler(error);
		
	}
	
}

void get_some_data(asio::ip::tcp::socket& socket) {
	std::error_code error;
	std::size_t length;
	// async reading data and printing it 
	socket.async_read_some(asio::buffer(vbuffer.data(), vBuffer.size()),
		[&](std::error_code error, std::size_t len)
		{
			if (!error) {
				for (int i = 0; i < len; i++)
					std::cout << vbuffer[i];
			}
		}
	);

}

