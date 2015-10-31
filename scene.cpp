#include "scene.h"

scene::scene(char* scene_str)
{
	char* ptr = strtok(scene_str, " ");
	if (strcmp(ptr, "model") == 0)
	{
		ptr = strtok(NULL, " ");
		strcpy(name, ptr);
		ptr = strtok(NULL, " ");
		for (int i = 0; i < 3; i++)
		{
			s[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
		for (int i = 0; i < 4; i++)
		{
			r[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
		for (int i = 0; i < 3; i++)
		{
			t[i] = atof(ptr);
			ptr = strtok(NULL, " ");
		}
	}
}

scene::~scene()
{
}

scenes::scenes(const char* file_name)
{
	selected = -1;
	x = 0.0;
	y = 0.0;
	char buffer[100];
	FILE* f_scene;

	f_scene = fopen(file_name, "r");
	if (!f_scene)
	{
		cout << "can not open the file\n";
		return;
	}

	while (fgets(buffer, 100, f_scene) != NULL)
	{
		scene* tmp = new scene(buffer);
		scene_list.push_back(*tmp);
	}
}

scenes::~scenes()
{
}

void scenes::select(unsigned int i)
{
	if (i<scene_list.size())
		selected = i;
}

void scenes::set_x_y(int a, int b)
{
	x = a;
	y = b;
}

void scenes::move(int a, int b, int w, int h)
{
	if (selected >= 0)
	{
		scene_list[selected].t[0] += (a - x) / double(w);
		scene_list[selected].t[1] -= (b - y) / double(y);
	}
}
