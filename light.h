#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

class light
{
public:
	float position[4];
	float specular[4];
	float diffuse[4];
	float ambient[4];
	
	light()
	{
		for (int i = 0; i < 4; i++)
		{
			position[i] = 0.0;
			specular[i] = 0.0;
			diffuse[i] = 0.0;
			ambient[i] = 0.0;
		}
	}

	light(char* light_str)
	{
		char* ptr = strtok(light_str, " ");

		ptr = strtok(NULL, " ");
		for (int i = 0; i < 3; i++)
		{
			position[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
		position[3] = 1.0;

		for (int i = 0; i < 3; i++)
		{
			ambient[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
		ambient[3] = 1.0;

		for (int i = 0; i < 3; i++)
		{
			diffuse[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
		diffuse[3] = 1.0;

		for (int i = 0; i < 3; i++)
		{
			specular[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
		specular[3] = 1.0;
	}
};

class environment_light
{
public:
	float environment_ambient[3];

	environment_light(char* light_str)
	{
		char* ptr = strtok(light_str, " ");
		
		ptr = strtok(NULL, " ");
		for (int i = 0; i < 3; i++)
		{
			environment_ambient[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}		
	}

};

class lights
{
public:
	vector<light> light_list;
	vector<environment_light> env_light;

	lights();
	lights(const char* light_file);
	~lights();

private:
	size_t light_total;
};