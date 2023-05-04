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

string settings[9]; 
int controls[6]; //w,a,s,d,shoot,potion

int saved_level;

void FileHandler::save(int gameHeight, int gameWidth, int save) {



	//open file, get all the stuff into externs and get them here, write them to the file with commas between, close file

	//ifstream file("res/saves/save_1.txt");       // note no mode needed
	
	std::ofstream clearfile;
	clearfile.open("res/saves/save_1.txt", std::ofstream::out | std::ofstream::trunc);
	clearfile.close();


	fstream file("res/saves/save_1.txt",ios::app);       // note no mode needed
	if (!file.is_open()) {
		//cout << " Failed to open" << endl;
	}
	else {

		//cout << "Opened OK" << endl;
		//convert wasd to chars

		//convert spell to left click
		//convert potion to right click
		//full screen boolean



		//if mouse, add 200



		settings[0] = to_string(gameWidth);
		settings[1] = to_string(gameHeight);
		settings[2] = to_string(save);
		int i = 3;
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

void FileHandler::load(int &gameHeight, int &gameWidth, int &save) {

	gameHeight = 1080;
	gameWidth = 1920;

	fstream file("res/saves/save_1.txt");
	if (!file.is_open()) {
		file << "1920,1080,1,22,0,18,3,200,201" << endl;
		controls[0] = 22;
		controls[1] = 0;
		controls[2] = 18;
		controls[3] = 3;
		controls[4] = 200;
		controls[5] = 201;
		gameHeight = 1080;
		gameWidth = 1920;
		saved_level = 1;


		//cout << " Failed to open" << endl;
	}
	else {
		//cout << "Opened OK" << endl;

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
			else if (i == 2)
				save = stoi(toks[i]);
			else
				controls[i-3] = stoi(toks[i]);

			i++;

			
		}
	
		file.close();
	}

	//take in the file from save, read its contents, the first 2 will be game width and height
}

string FileHandler::ItoS(int k) {
	switch (k) {
	case 0:
		return "A";
		break;

	case 1:
		return "B";
		break;

	case 2:
		return "C";
		break;

	case 3:
		return "D";
		break;

	case 4:
		return "E";
		break;

	case 5:
		return "F";
		break;

	case 6:
		return "G";
		break;

	case 7:
		return "H";
		break;

	case 8:
		return "I";
		break;

	case 9:
		return "J";
		break;

	case 10:
		return "K";
		break;

	case 11:
		return "L";
		break;

	case 12:
		return "M";
		break;

	case 13:
		return "N";
		break;

	case 14:
		return "O";
		break;

	case 15:
		return "P";
		break;

	case 16:
		return "Q";
		break;

	case 17:
		return "R";
		break;

	case 18:
		return "S";
		break;

	case 19:
		return "T";
		break;

	case 20:
		return "U";
		break;

	case 21:
		return "V";
		break;

	case 22:
		return "W";
		break;

	case 23:
		return "X";
		break;

	case 24:
		return "Y";
		break;

	case 25:
		return "Z";
		break;
	case 26:
		return "Num0";
		break;
		
	case 27:
		return "Num1";
		break;

	case 28:
		return "Num2";
		break;
		
	case 29:
		return "Num3";
		break;
		
	case 30:
		return "Num4";
		break;

	case 31:
		return "Num5";
		break;
			
	case 32:
		return "Num6";
		break;
		
	case 33:
		return "Num7";
		break;
		
	case 34:
		return "Num8";
		break;

	case 35:
		return "Num9";
		break;

	case 36:
		return "Escape";
		break;

	case 37:
		return "LControl";
		break;

	case 38:
		return "LShift";
		break;

	case 200:
		return "Left click";
		break;

	case 201:
		return "Right click";
		break;

	case 202:
		return "Middle";
		break;

	case 203:
		return "Button_1";
		break;

	case 204:
		return "Button_2";
		break;

	default:
		return "no key";
		break;
	}
}