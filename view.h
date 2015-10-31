#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

class view
{
public:
	float eye[3];
	float at[3];
	float up[3];
	double fovy, near, far;
	int viewport[4];

	view(const char* file_name);
	~view();

	void zoom(bool flag);
	void rotate(bool flag);
};