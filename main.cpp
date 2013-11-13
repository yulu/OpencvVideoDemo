#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>

using namespace cv;
using namespace std;

/*
 * A seperate thread to play the sound
 */
struct thread_data
{
	int m_id;
	thread_data(int id) : m_id(id) {}
};

DWORD WINAPI thread_func(LPVOID lpParameter)
{
	thread_data *td = (thread_data*)lpParameter;
	PlaySound(TEXT("C:/test1.wav"), NULL, SND_LOOP);
	return 0;
}

/*
 * Play video in the main thread
 */
int PlayVideo(String filename){
	// open the video file for reading
    VideoCapture cap(filename); 

	// if not success, exit program
    if ( !cap.isOpened() ) 
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }

	// get the frames per seconds of the video
    double fps = cap.get(CV_CAP_PROP_FPS); 

    cout << "Frame per seconds : " << fps << endl;

	// create a window called "MyVideo"
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); 

    while(1)
    {
        Mat frame;

		// read a new frame from video
        bool bSuccess = cap.read(frame); 

		if(frame.empty())
			return 1;

         if (!bSuccess) // if not success, break loop
        {
               cout << "Cannot read the frame from video file" << endl;
               break;
        }


		//TODO: process the frame image needed
		Mat resize_frame;
		//resize(frame, resize_frame,	Size(1280, 720));

		//display the frame
        imshow("MyVideo", frame); //show the frame in "MyVideo" window

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl; 
                return -1; 
       }

    }

}

int main(int argc, char* argv[])
{
	String filename = "C:/Ngari.mov";

	// create a seperate thread to play the sound
	CreateThread(NULL, 0, thread_func, new thread_data(0) , 0, 0);
	
	
	while (PlayVideo(filename) == 1){
		continue;
	}

	return 0;
	
}
