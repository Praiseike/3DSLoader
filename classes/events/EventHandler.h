#include <iostream>

#ifndef EVENTS_H
#define EVENTS_H
using namespace std;

class EventHandler
{
	public:

        EventHandler()
        {
            g_ViewMode = GL_TRIANGLES;
        }

        // Please help...
		void toggleLight(GLenum light)
		{
		    if(light == GL_LIGHT0)
		    {
		        if(rightLightOn == true)
		        {
		            glDisable(light);
		            rightLightOn = !rightLightOn;

		        }
		        else if(rightLightOn == false)
		        {
		            glEnable(light);
		            rightLightOn = !rightLightOn;
		        }
		    }

		    if(light == GL_LIGHT1)
		    {
		        if(leftLightOn == true)
		        {
		            glDisable(light);
		            leftLightOn = !leftLightOn;

		        }
		        else if(leftLightOn == false)
		        {
		            glEnable(light);
		            leftLightOn = !leftLightOn;
		        }
		    }

		}

        static float rotateMod()
        {
            static float angle = 0;
            angle = (angle >= 360)?0:angle+=0.5;
            return angle;
        }

        inline int getAngle()
        {
            return this->rotAngle;
        }

		void keyboard(int key,int x,int y)
		{
			switch(key)
			{
				case GLUT_KEY_LEFT:
					xtrans += speed;
					break;

				case GLUT_KEY_RIGHT:
					xtrans -= speed;
					break;

				case GLUT_KEY_UP:
					ztrans += speed;
					break;

				case GLUT_KEY_DOWN:
					ztrans -= speed;
					break;

		        case GLUT_KEY_F1:
		            cout << "[+] GL_LIGHT1 is "<<leftLightOn<<endl;
		            toggleLight(GL_LIGHT1);
		            break;

		        case GLUT_KEY_F2:
		            cout << "[+] GL_LIGHT0 is "<<rightLightOn<<endl;
		            toggleLight(GL_LIGHT0);
		            break;
                case GLUT_KEY_SHIFT_L:
                    cout << "[+] Turning right"<<endl;
                    rotAngle -= 1;
                    break;
                case GLUT_KEY_SHIFT_R:
                    cout << "[+] Turning left"<<endl;
                    rotAngle += 1;
                    break;
                case GLUT_KEY_F11:
                    if(fullscreen)
                    {
                        cout << "[+] Leaving fullscreen mode"<<endl;
                        glutFullScreenToggle();
                        fullscreen = false;
                    }
                    else
                    {
                    cout << "[+] Switching to fullScreen"<<endl;
                        glutFullScreenToggle();
                        fullscreen = true;
                    }
                    break;

                case GLUT_KEY_F3:
                    m_ToggleMode();
                    break;

				default:
					break;
			}
		}

        int getTranslateSpeed()
		{
			return this->speed;
		}

        inline int getXtrans()
		{
			return this->xtrans;
		}

		inline int getZtrans()
		{
			return this->ztrans;
		}

        inline int getRotAngle()
        {
            return rotAngle;
        }

        void setSpeed(int s)
        {
            speed = s;
        }

        void m_ToggleMode()
        {
            if(g_ViewMode == GL_TRIANGLES)
            {
                g_ViewMode = GL_LINES;
                cout << "GL_LINES: "<<g_ViewMode<<endl;
            }
            else
            {
                g_ViewMode = GL_TRIANGLES;
                cout << "GL_TRIANGLES: "<<g_ViewMode<<endl;
            }
        }

        int getViewMode() {return g_ViewMode;}
	private:

        bool leftLightOn = true;
        bool rightLightOn = true;
        bool fullscreen = false;

        short rotAngle = 0;
		int ztrans = -3;
		int xtrans = 0;
		float speed = 3;
        int g_ViewMode;

};

#endif // EVENTS_H
