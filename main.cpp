#include "scene.h"
#include "light.h"
#include "mesh.h"
#include "view.h"
#include "glut.h"

void display();
void reshape(int w, int h);
void scene_setting();
void object(const char* file_name);
void lighting();
void viewing();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouse_motion(int x, int y);

int width = 800, height = 600;
scenes* s = new scenes("scene2.scene");
lights* l = new lights("scene2.light");
view* v = new view("scene2.view");

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW_1");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_motion);
	glutMainLoop();
	return 0;
}

void scene_setting()
{
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < s->scene_list.size(); i++)
	{
		glPushMatrix();
		glTranslatef(s->scene_list[i].t[0], s->scene_list[i].t[1], s->scene_list[i].t[2]);
		glRotatef(s->scene_list[i].r[0], s->scene_list[i].r[1], s->scene_list[i].r[2], s->scene_list[i].r[3]);
		glScalef(s->scene_list[i].s[0], s->scene_list[i].s[1], s->scene_list[i].s[2]);
		object(s->scene_list[i].name);
		glPopMatrix();
	}
}

void object(const char* file_name)
{
	mesh* obj = new mesh(file_name);

	int lastMaterial = -1;
	for (size_t i = 0; i < obj->fTotal; ++i)
	{
		// set material property if this face used different material
		if (lastMaterial != obj->faceList[i].m)
		{
			lastMaterial = (int)obj->faceList[i].m;
			glMaterialfv(GL_FRONT, GL_AMBIENT, obj->mList[lastMaterial].Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, obj->mList[lastMaterial].Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, obj->mList[lastMaterial].Ks);
			glMaterialfv(GL_FRONT, GL_SHININESS, &obj->mList[lastMaterial].Ns);

			//you can obtain the texture name by object->mList[lastMaterial].map_Kd
			//load them once in the main function before mainloop
			//bind them in display function here
		}

		glBegin(GL_TRIANGLES);
		for (size_t j = 0; j<3; ++j)
		{
			//textex corrd. object->tList[object->faceList[i][j].t].ptr
			glNormal3fv(obj->nList[obj->faceList[i][j].n].ptr);
			glVertex3fv(obj->vList[obj->faceList[i][j].v].ptr);
		}
		glEnd();
	}
}

void lighting()
{
	int gl_light[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	for (int i = 0; i < l->light_list.size(); i++ )
	{
		glEnable(gl_light[i]);
		glLightfv(gl_light[i], GL_POSITION, l->light_list[i].position);
		glLightfv(gl_light[i], GL_DIFFUSE, l->light_list[i].diffuse);
		glLightfv(gl_light[i], GL_SPECULAR, l->light_list[i].specular);
		glLightfv(gl_light[i], GL_AMBIENT, l->light_list[i].ambient);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, l->env_light[0].environment_ambient);
}

void viewing()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(v->eye[0], v->eye[1], v->eye[2], v->at[0], v->at[1], v->at[2], v->up[0], v->up[1], v->up[2]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(v->fovy, (float)v->viewport[2] / v->viewport[3], v->near, v->far);

	glViewport(v->viewport[0], v->viewport[1], v->viewport[2], v->viewport[3]);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      
	glClearDepth(1.0f);                        
	glEnable(GL_DEPTH_TEST);                  
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewing();
	lighting();
	scene_setting();
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			v->zoom(1);
		break;
		case 'a':
			v->rotate(1);
		break;
		case 's':
			v->zoom(0);
		break;
		case 'd':
			v->rotate(0);
		break;
		default:
			if (key >= '0' && key <= '9')
				s->select(key - '0');
		break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state)
				s->set_x_y(-1, -1);
			else
				s->set_x_y(x, y);
		break;
		case GLUT_RIGHT_BUTTON :
			if (state)
				s->set_x_y(-1, -1);
			else
				s->set_x_y(x, y);
		break;
	}
}

void mouse_motion(int x, int y)
{
	s->move(x, y, v->viewport[2], v->viewport[3]);
	s->set_x_y(x, y);
	glutPostRedisplay();
}
