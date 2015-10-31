#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

class scene
{
public:
	char name[50];
	float s[3];
	float r[4];
	float t[3];
	
	scene(char* scene_str);
	~scene();
};

class scenes
{
public:
	vector<scene> scene_list;
	int selected, x, y;

	scenes(const char* file_name);
	~scenes();

	void select(unsigned int i);
	void set_x_y(int a, int b);
	void move(int a, int b, int w, int h);
};