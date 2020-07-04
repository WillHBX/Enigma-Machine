#include <iostream>
#include "Enigma.h"

using namespace std;

Rotor::Rotor(std::string encode_table, char const& start_, char const& arrows_)
	:Enigma_Component(encode_table),isSpin(false)
{
	origin_Start = start_;
	now_Start = origin_Start;
	origin_Arrows = WordToPst(arrows_);
	now_Arrows = origin_Arrows;
}

char Rotor::Input_signal(char c)
{			
	if (c > 'Z') {
		Spin();
		c -= 26;
	}
	char word = PstToWord(c);		//求出輸入的那個位置的字母
	size_t after = WordToPst(encode_table[word - 'A']);	//算出加密過後的字母在哪一個位置
	
	char outWord = PstToWord(Forward(after));

	if (outWord < 'A')
		outWord += 26;
	
	return WordToPst(reverse_table[outWord - 'A']);
}

void Rotor::Reset()
{
	now_Arrows = origin_Arrows;
	now_Start = origin_Start;
	if (link_next)
		link_next->Reset();
}

size_t Rotor::Forward(size_t const& i)
{
	if (now_Arrows == 'A' && !isSpin) {			
		isSpin = true;
		return link_next->Input_signal(i + 26);
	}

	if (now_Arrows == 'B')
		isSpin = false;

	return link_next->Input_signal(i);
}

void Rotor::Spin()
{
	now_Start++;
	if (now_Start > 'Z')
		now_Start -= 26;

	now_Arrows--;
	if (now_Arrows < 'A')
		now_Arrows += 26;
}

Special_Rotor::Special_Rotor(std::string encode_table, char const& start_, char const& arrows_)
	:Rotor(encode_table,start_,arrows_){}


char Special_Rotor::Input_signal(char c)
{
	if (c > 'Z') {
		Spin();
		c -= 26;
	}
	char word = PstToWord(c);								//求出輸入的那個位置的字母
	size_t after = WordToPst(encode_table[word - 'A']);	//算出加密過後的字母在哪一個位置

	char outPst = PstToWord(Forward(after));
	if (outPst < 'A')
		outPst += 26;
	
	size_t ans = WordToPst(reverse_table[outPst - 'A']);
	if (now_Arrows == 'B')
		Spin();
	return ans;
}

size_t Special_Rotor::Forward(size_t const& i)
{
	size_t tmp = i;

	if (now_Arrows == 'A' && !isSpin) {	
		isSpin = true;
		return link_next->Input_signal(tmp + 26);
	}
	if (now_Arrows == 'B')
		isSpin = false;
	return link_next->Input_signal(tmp);
}

Reflector::Reflector(std::string encode_table)
	:Enigma_Component(encode_table) {}

char Reflector::Input_signal(char c)
{
	return encode_table[c - 'A'];
}

size_t Reflector::Forward(size_t const& i)
{
	return encode_table[i - 'A'];
}

Plugboard::Plugboard(string encode_table)
	:Enigma_Component(encode_table) {}

char Plugboard:: Input_signal(char c)
{
	return encode_table[Forward(c)-'A'];
}

void Plugboard::Reset()
{
	if (link_next)
		link_next->Reset();
}



size_t Plugboard::Forward(size_t const& i)
{
	return link_next->Input_signal(encode_table[i - 'A'] + 26);
}

