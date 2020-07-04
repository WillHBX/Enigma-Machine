#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

class Enigma_Files
{
	public:
		void Read_file ( std::string file ) ; //Read text from file into string
		void Write_file ( std::string file ) ; //Write string from file into string

		void Push ( char const& c ) ; //Push a character on the end of data string
		char const& operator [] ( size_t const& i  ) ; // (const) subscript operator

		std::string Data () ; //get the data string
		size_t Length(); //report # of character

	protected:
		std::string data ; //the data string
} ;

class Enigma_Component
{
	public:
		Enigma_Component ();
		Enigma_Component ( std::string file );

		virtual char Input_signal ( char c ) ; //Input a character and start to encode it.
		void Link ( Enigma_Component & next ) ; //Link the NEXT ENCODER
		virtual void Reset () ; //(hw8 only) Reset wheel's postion

	protected:
		Enigma_Component* link_next ; // Link to the NEXT encoder
		Enigma_Component* link_previous ; // Link to the PREVIOUS encoder

		std::vector<size_t> encode_table; //Mapping of forward Encoding
		std::vector<size_t> reverse_table; //(optional) Mapping of backward Encoding (Decoding)

		virtual size_t Forward( size_t const& i ) = 0 ; //Forward Encoding
		//virtual size_t Backward( size_t const& i ) = 0 ; //(optional) Backward Encoding 

		void Read_table ( std::string file ) ; //Read the Ringstellung and generate encode_table & reverse_table
		virtual void Spin () {} 
		//(hw8 only) Spin the wheel
} ;
