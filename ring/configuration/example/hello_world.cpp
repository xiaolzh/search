// Example of simplest usage of Configurator library.
//
// Copyright (C) Denis Shevchenko, 2010.
// for @ dshevchenko.biz

#include <configurator/configurator.hpp>

#include <iostream>

int main( int argc, char* argv[] ) {	
    try {
        cf::configurator configurator; 
        configurator.add_option( "Host" );

        configurator.parse( "/some/path/to/hello_world.conf" ); // See hello_world.conf in 'example'.

        std::string value_of_host = configurator.get_value( "Host" );
        std::cout << "Value of host: " << value_of_host << std::endl;
    } catch ( const std::exception& exc ) {
		std::cerr << exc.what() << std::endl;
	} 
	
	return 0;
}
