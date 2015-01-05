#include "composite.h"
#include "sync.h"
#include <typeinfo>

namespace sg {
	namespace noder {

		float gravity = 9.8f;

        //typedef boost::shared_ptr< actors > actorsPtr;

        Nodes herd;
		int counter;
		double second;

		const struct sync_track * Peek_C_L_X, *Peek_C_L_Y, *Peek_C_L_Z;
		const struct sync_track * From_C_P_X, *Peek_C_P_Y, *Peek_C_P_Z;


		composite::composite() : actors()
		{



		}



		void composite::AddActor(int typeID, GLfloat x, GLfloat y, GLfloat z)
		{
			switch (typeID)
			{
			case 001:
				herd.push_back(actorsPtr(new camera(x, y, z, false)));
                break;
			case 002:
				herd.push_back(actorsPtr(new cube(x, y, z, false)));
				break;
			case 003:
				herd.push_back(actorsPtr(new composite()));
			default:
				cout << "Error no such object: " << typeID << endl;
			}
		}
		void composite::AddActor(VEC3 co, string filename1, string filename2, GLfloat x, GLfloat y, GLfloat z)
		{
			herd.push_back(actorsPtr(new model(x, y, z, false, filename1, filename2, co)));


		}





		void composite::Magic(bool draw)
		{

			//found out the timer started way to early.
			if (counter == -1)
				clock.restart();


			counter++;





			for (unsigned int i = 0; i < herd.size(); i++)
			{


				//Animation handler, but how to handle transofrmation data and calls?
				//should scripting functions take place here or in another class?




				/*
				if(  typeid( * herd[i].get())==typeid( camera ))
				cout << "actor nr: " << i << " is camera" << endl;


				if(  typeid( * herd[i].get())==typeid( model ))
				cout << "actor nr: " << i << " is model" << endl;
				*/

				if (typeid(*herd[i].get()) == typeid(camera))
				{
					//herd[i]->TranslateLocal(0.05f, 0.0f, -0.05f);
					//herd[i]->f
					//herd[i]->RotateLocal(1.0f, 0.0f, 1.0f, 0.0f);
					//herd[i]->SetModel();

					//for lookat må man inverse
				}

				if (typeid(*herd[i].get()) == typeid(model))
				{ 
				//herd[i]->RotateLocal(1.0f, 0.0f, 1.0f, 0.0f);
				//herd[i]->RotateLocal(1.0f, 1.0f, 0.0f, 0.0f);
				//herd[i]->TranslateLocal(0.0f, 0.0f, -0.05f);

				}
				//herd[i]->Translate(0.0f, 0.0f, 0.05f);
				//if(draw)
				herd[i]->draw();
			}



			second = second + (clock.elapsed());



			if (second >= 1.0)
			{

				//cout << "FPS: " << counter << endl;
				counter = 0;
				second = 0;

			}


			clock.restart();
		}

		void composite::DrawAll(){
			for (unsigned int i = 0; i < herd.size(); i++)
			{
				herd[i]->draw();
			}
		}

		void composite::StartTimer()
		{
			clock = Timer();
			counter = -1;
			second = 0;

		}

		void composite::SortTracks()
		{

			//sync_device *rocket = sync_create_device("sync");

			herd[1]->RotateLocal(-25.0f, 1.0f, 0.0f, 0.0f);
			herd[1]->RotateLocal(15.0f, 0.0f, 1.0f, 0.0f);
			herd[1]->RotateLocal(-15.0f, 0.0f, 0.0f, 1.0f);
			herd[1]->TranslateLocal(0.0f, 1.0f, 0.0f);
			herd[2]->ScaleLocal(3.0f);
			herd[2]->RotateLocal(90.0f, 1.0f, 0.0f, 0.0f);
			//Peek_C_L_X = sync_get_track( rocket, "Look.X");
			//Peek_C_L_Y = sync_get_track( rocket, "Look.Y");
			//Peek_C_L_Z = sync_get_track( rocket, "Look.Z");

			//From_C_L_Z = sync_get_tracker(r


		}
	}
}
