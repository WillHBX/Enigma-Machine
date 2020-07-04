#include <iostream>
#include <string>
#include <fstream>
#include "Enigma_Base.h"

using namespace std;

void Enigma_Files::Read_file(string file)
{
	ifstream inFile(file, ios::in);

	if (!inFile) {
		inFile.close();
		cerr << file << " could not be opened.\n";
		exit(1);
	}

	for (string s; !inFile.eof();) {
		inFile >> s;
		data += s;
	}

	inFile.close();
}

void Enigma_Files::Write_file(string file)
{
	ofstream outFile(file, ios::out);

	if (!outFile) {
		outFile.close();
		cerr << file << " could not be opened.\n";
		exit(1);
	}

	outFile << data;

	outFile.close();
}

void Enigma_Files::Push(char const& c)
{
	data.push_back(c);
}

char const& Enigma_Files::operator [] (size_t const& i)
{
	return data[i];
}

string Enigma_Files::Data()
{
	return data;
}

size_t Enigma_Files::Length()
{
	return data.length();
}

Enigma_Component::Enigma_Component()
	:link_next(NULL), link_previous(NULL), encode_table(0) {}

Enigma_Component::Enigma_Component(std::string file)
	: link_next(NULL), link_previous(NULL)
{
	Read_table(file);
}

char Enigma_Component::Input_signal(char c)
{
	return Forward(c);
}

void Enigma_Component::Link(Enigma_Component & next)
{
	link_next = &next;
	next.link_previous = this;
}

void Enigma_Component::Reset()
{
	link_next->Reset();
}

void Enigma_Component::Read_table(std::string file)
{
	ifstream inFile(file, ios::in);

	if (!inFile) {
		inFile.close();
		cerr << file << " could not be opened.\n";
		exit(1);
	}
	string s;
	inFile >> s;

	for (size_t  i = 0;i<s.size();i++) 
		encode_table.push_back(s[i]);
	
	for (char c = 'A'; c <= 'Z'; c++)
		for (size_t i = 0; i < s.size(); i++)
			if (c == s[i]) {
				reverse_table.push_back(i + 'A');
				break;
			}

	inFile.close();
}
