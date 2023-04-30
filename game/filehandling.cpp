#include "filehandling.h"
#include "arvenhold.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void FileHandler::save(int gameHeight, int gameWidth) {
	/*
	fullscreen: 0/1
resolution: 1080
controller: 0/1
up: w
left: a
down: s
right: d
spell: left-click
potion: right-click


create controller list from practical 2

store full screen, resolution
*/


	//open file, get all the stuff into externs and get them here, write them to the file with commas between, close file

	fstream ifs("res/saves/save_1.txt");       // note no mode needed
	if (!ifs.is_open()) {
		cout << " Failed to open" << endl;
	}
	else {
		cout << "Opened OK" << endl;
		ifs << gameWidth << "," << gameHeight << endl;
	}
	ifs.close();

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

		stringstream ss;
		ss << file.rdbuf();

		string data = ss.str();

		cout << data << endl;
			

		file.close();
	}

	//take in the file from save, read its contents, the first 2 will be game width and height
}