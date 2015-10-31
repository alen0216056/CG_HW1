#include "light.h"

lights::lights()
{
	light_total = 0;
}

lights::lights(const char* light_file)
{
	char buffer[100];
	light_total = 0;
	FILE* f_light;

	f_light = fopen(light_file, "r");
	if (!f_light)
	{
		cout << "error" << light_file << endl;
		return;
	}

	while ( fgets(buffer, 100, f_light)!=NULL )
	{
		if ( strstr(buffer, "light") != NULL )
		{
			light* new_light = new light(buffer);
			light_list.push_back(*new_light);
			light_total++;
		}
		else if ( strstr(buffer, "ambient") != NULL )
		{
			environment_light* new_env = new environment_light(buffer);
			env_light.push_back(*new_env);
		}
		else
			break;
	}
	fclose(f_light);
}

lights::~lights()
{
}