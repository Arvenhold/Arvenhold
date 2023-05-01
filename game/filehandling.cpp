#include "filehandling.h"
#include "arvenhold.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/graphics.hpp>

using namespace std;
using namespace sf;

string settings[8]; 
int controls[6]; //w,a,s,d,shoot,potion

void FileHandler::save(int gameHeight, int gameWidth) {



	//open file, get all the stuff into externs and get them here, write them to the file with commas between, close file

	//ifstream file("res/saves/save_1.txt");       // note no mode needed
	
	std::ofstream clearfile;
	clearfile.open("res/saves/save_1.txt", std::ofstream::out | std::ofstream::trunc);
	clearfile.close();


	fstream file("res/saves/save_1.txt",ios::app);       // note no mode needed
	if (!file.is_open()) {
		cout << " Failed to open" << endl;
	}
	else {

		cout << "Opened OK" << endl;
		//convert wasd to chars

		//convert spell to left click
		//convert potion to right click
		//full screen boolean



		//if mouse, add 200



		settings[0] = to_string(gameWidth);
		settings[1] = to_string(gameHeight);
		int i = 2;
		for (int k : controls) {
			//settings[i] = "0";
			settings[i] = to_string(k);
			i++;
		}

		for (string s : settings)
		{
			file << s << ",";
		}
	}
	file.close();

}

void FileHandler::load(int &gameHeight, int &gameWidth) {

	gameHeight = 1080;
	gameWidth = 1920;

	fstream file("res/saves/save_1.txt");
	if (!file.is_open()) {
		cout << " Failed to open" << endl;
	}
	else {
		cout << "Opened OK" << endl;

		stringstream output;
		output << file.rdbuf();

		string data;

		std::vector<std::string> toks;
		
		while (getline(output, data, ',')) {

			toks.push_back(data);
		}

		int i = 0;
		for (string s : settings)
		{
			if (i == 0)
				gameWidth = stoi(toks[i]);
			else if (i == 1)
				gameHeight = stoi(toks[i]);
			else
				controls[i-2] = stoi(toks[i]);

			i++;

			
		}
	
		file.close();
	}

	//take in the file from save, read its contents, the first 2 will be game width and height
}

char FileHandler::KtoC(sf::Keyboard::Key k) {
	switch (k) {
	case Keyboard::Key::A:
		return 'a';
		break;

	case Keyboard::Key::B:
		return 'b';
		break;

	case Keyboard::Key::C:
		return 'c';
		break;

	case Keyboard::Key::D:
		return 'd';
		break;

	case Keyboard::Key::E:
		return 'e';
		break;

	case Keyboard::Key::F:
		return 'f';
		break;

	case Keyboard::Key::G:
		return 'g';
		break;

	case Keyboard::Key::H:
		return 'h';
		break;

	case Keyboard::Key::I:
		return 'i';
		break;

	case Keyboard::Key::J:
		return 'j';
		break;

	case Keyboard::Key::K:
		return 'k';
		break;

	case Keyboard::Key::L:
		return 'l';
		break;

	case Keyboard::Key::M:
		return 'm';
		break;

	case Keyboard::Key::N:
		return 'n';
		break;

	case Keyboard::Key::O:
		return 'o';
		break;

	case Keyboard::Key::P:
		return 'p';
		break;

	case Keyboard::Key::Q:
		return 'q';
		break;

	case Keyboard::Key::R:
		return 'r';
		break;

	case Keyboard::Key::S:
		return 's';
		break;

	case Keyboard::Key::T:
		return 't';
		break;

	case Keyboard::Key::U:
		return 'u';
		break;

	case Keyboard::Key::V:
		return 'v';
		break;

	case Keyboard::Key::W:
		return 'w';
		break;

	case Keyboard::Key::X:
		return 'x';
		break;

	case Keyboard::Key::Y:
		return 'y';
		break;

	case Keyboard::Key::Z:
		return 'z';
		break;
	default:
		return '0';
		break;
	}
}

sf::Keyboard::Key FileHandler::CtoK(char c) {
	switch (c) {
	case 'a':
		return Keyboard::Key::A;
		break;

	case 'b':
		return Keyboard::Key::B;
		break;

	case 'c':
		return Keyboard::Key::C;
		break;

	case 'd':
		return Keyboard::Key::D;
		break;

	case 'e':
		return Keyboard::Key::E;
		break;

	case 'f':
		return Keyboard::Key::F;
		break;

	case 'g':
		return Keyboard::Key::G;
		break;

	case 'h':
		return Keyboard::Key::H;
		break;

	case 'i':
		return Keyboard::Key::I;
		break;

	case 'j':
		return Keyboard::Key::J;
		break;

	case 'k':
		return Keyboard::Key::K;
		break;

	case 'l':
		return Keyboard::Key::L;
		break;

	case 'm':
		return Keyboard::Key::M;
		break;

	case 'n':
		return Keyboard::Key::N;
		break;

	case 'o':
		return Keyboard::Key::O;
		break;

	case 'p':
		return Keyboard::Key::P;
		break;

	case 'q':
		return Keyboard::Key::Q;
		break;

	case 'r':
		return Keyboard::Key::R;
		break;

	case 's':
		return Keyboard::Key::S;
		break;

	case 't':
		return Keyboard::Key::T;
		break;

	case 'u':
		return Keyboard::Key::U;
		break;

	case 'v':
		return Keyboard::Key::V;
		break;

	case 'w':
		return Keyboard::Key::W;
		break;

	case 'x':
		return Keyboard::Key::X;
		break;

	case 'y':
		return Keyboard::Key::Y;
		break;

	case 'z':
		return Keyboard::Key::Z;
		break;

	default:
		return Keyboard::Key::Num0;
	}

}