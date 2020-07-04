#pragma once

#include "Enigma_Base.h"


class Rotor : public Enigma_Component
{
	public:
		Rotor ( std::string encode_table, char const& start_, char const& arrows_ ) ;
		char Input_signal(char c); //Input a character and start to encode it.
		
		char PstToWord(const size_t &pst){
			char w = now_Start - 'Z' - 1 + pst;						//算出輸入pst位置的字母是甚麼    (正上方的位置為A 順時針依序為B.C...)
			if (w < 'A')											
				w += 26;
			return w;
		}

		size_t WordToPst(const char &word) {
			size_t pst = word + 'Z' + 1 - now_Start;			//算出加密過後的字母在哪一個位置
			if (pst > 'Z')										
				pst -= 26;
			return pst;
		}
		void Reset();
		
	protected:
		size_t origin_Start;
		size_t origin_Arrows;
		size_t now_Start;
		size_t now_Arrows;
		size_t Forward(size_t const& i);
		bool isSpin;
		void Spin();
} ;

class Special_Rotor : public Rotor
{
	public:
		Special_Rotor(std::string encode_table, char const& start_, char const& arrows_);
		char Input_signal(char c);
	protected:
		size_t Forward(size_t const& i);
};

class Reflector : public Enigma_Component
{
	public: 
		Reflector ( std::string encode_table );
		char Input_signal(char c); //Input a character and start to encode it.
		void Reset() {};
		

	protected:
		size_t Forward(size_t const& i);
		void Spin() {};
} ;

class Plugboard : public Enigma_Component
{
	public:
		Plugboard(std::string);
		char Input_signal(char c); //Input a character and start to encode it.
		void Reset();
		//void Spin();
	protected:
		size_t Forward(size_t const& i);
};