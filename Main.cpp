#include<dos.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<process.h>
using namespace std;

//Class for handling data of each entry. 
class car_resale
{
    private:
        char model[50]; //Model Name
        float price; //Car Price
        int use; //Years in use
        float dist; //Distance used for
        long idno; //VIN number for tracking
    public:
        void get(); 
        void show();
        long retno();
};

//Function to get data from the user.
void car_resale::get()
{
    cout<<"Enter car model: "; gets(model);
    cout<<"Enter VIN number: "; cin>>idno;
    cout<<"How much do you want to sell your vehicle for?"; cin>>price;
    cout<<"How many years has the vehicle been in use?"; cin>>use;
    cout<<"Approximate usage of vehicle? (in kilometers)"; cin>>dist;
}

//Function to show the data of a specific entry or all entries.
void car_resale::show()
{
    cout<<"\n\nCar model: "; puts(model);
    cout<<"VIN number: "<<idno;
    cout<<"\nPrice: "<<price;
    cout<<"\nUsage: "<<use;
    cout<<"\nDriven for(in kilometers): "<<dist;
}

//Function to return the VIN number for tracking.
long car_resale::retno()
{
    return idno;
}

//Driver Program
int main()
{
    system("clear"); 
    //Welcome screen
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"*******************************************************************************";
    cout<<endl;
    cout<<" WELCOME TO FPCS CAR SALES ";
    cout<<endl<<"*******************************************************************************";
    _sleep(3000);
    system("clear");
    //Data entry
    ofstream f1; car_resale a; int n, ch; char ch1;
    f1.open("car.dat", ios::out|ios::binary);
    cout<<"\nHow many records do you wish to store? "; cin>>n;
    for(int i=0; i<n; i++)
    {
        a.get();
        f1.write((char*)&a,sizeof(a));
    }
    f1.close();
    //Menu-driven program
    do
    {
        system("clear");
        cout<<"\nOption 1: Append";
        cout<<"\nOption 2: Modify";
        cout<<"\nOption 3: Search";
        cout<<"\nOption 4: Delete";
        cout<<"\nOption 5: Display";
        cout<<"\nOption 6: Exit";
        cout<<"\nEnter your choice: "; cin>>ch;
        switch(ch)
        {
            case 1: //Takes a single entry from the user and appends into the file.
            {
                f1.open("car.dat",ios::app|ios::binary);
                a.get();
                f1.write((char*)&a,sizeof(a));
                f1.close();
                break;
            }
            case 2: //Searches for a specific entry and rewrites it. 
            {
                ofstream f2;
                f2.open("car.dat", ios::out|ios::ate|ios::binary);
                int n1;
                cout<<"\nEnter the record which has to be modified: "; cin>>n1;
                int x=(n1-1)*sizeof(a);
                f2.seekp(x,ios::beg);
                a.get();
                f2.write((char*)&a,sizeof(a));
                f2.close();
                break;
            }
            case 3: //Searches for a specific entry and shows its details.
            {
                ifstream f3; int flag=0;
                f3.open("car.dat",ios::in|ios::binary);
                f3.seekg(0,ios::beg);
                long id;
                cout<<"\nEnter VIN number: "; cin>>id;
                while(f3.read((char*)&a,sizeof(a)))
                {
                    if(a.retno()==id)
                    {
                        a.show();
                        flag=1;
                    }
                }
                if(flag==0)
                    cout<<"\nID number not found. SORRY!";
                f3.close();
                break;
            }
            case 4: //Copies all data to a new file except the selected record. Deletes the old file.
            {
                ofstream f41; ifstream f42; long c;
                f42.open("car.dat",ios::in|ios::binary);
                f41.open("newcar.dat",ios::out|ios::app|ios::binary);
                f42.seekg(0,ios::beg);
                cout<<"\nEnter vin number: "; cin>>c;
                while(f42.read((char*)&a,sizeof(a)))
                {
                    if(c!=a.retno())
                    f41.write((char*)&a,sizeof(a));
                }
                remove("car.dat"); rename("newcar.dat","car.dat");
                f41.close(); f42.close();
                break;
            }
            case 5: //displays all data in the file. 
            {
                ifstream f5;
                f5.open("car.dat",ios::in|ios::binary);
                f5.seekg(0,ios::beg);
                while(f5.read((char*)&a,sizeof(a)))
                    a.show();
                f5.close();
                break;
            }
            case 6: //Exits the program. Shows a Thank You slide. 
            {
                system("clear");
                cout<<"_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*";
                cout<<" ************************************";
                cout<<"\n * Thank you for using FPCS!! * ";
                cout<<" ************************************";
                cout<<"_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_**_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*";
                _sleep(3000);
                exit(0);
            }
        }
        cout<<"\nDo you wish to continue? "; cin>>ch1; 
    }
    while(ch1=='Y'||ch1=='y');
    return 0;
}

On Sat, Oct 29, 2022, 5:51 PM Ashwani Kaushik <sb191097@gmail.com> wrote:
This program uses the OpenCV library to detect faces in a live stream from webcam or in a video file stored in the local machine. This program detects faces in real time and tracks it. It uses pre-trained XML classifiers for the same. The classifiers used in this program have facial features trained in them. Different classifiers can be used to detect different objects.
Requirements for running the program:
1) OpenCV must be installed on the local machine.
2) Paths to the classifier XML files must be given before the execution of the program. These XML files can be found in the OpenCV directory “opencv/data/haarcascades”.
3) Use 0 in capture.open(0) to play webcam feed.
4) For detection in a local video provide the path to the video.(capture.open(“path_to_video”)).

// CPP program to detects face in a video

// Include required header files from OpenCV directory
#include "/usr/local/include/opencv2/objdetect.hpp"
#include "/usr/local/include/opencv2/highgui.hpp"
#include "/usr/local/include/opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Function for Face Detection
void detectAndDraw( Mat& img, CascadeClassifier& cascade,
    CascadeClassifier& nestedCascade, double scale );
string cascadeName, nestedCascadeName;

int main( int argc, const char** argv )
{
 // VideoCapture class for playing video for which faces to be detected
 VideoCapture capture;
 Mat frame, image;

 // PreDefined trained XML classifiers with facial features
 CascadeClassifier cascade, nestedCascade;
 double scale=1;

 // Load classifiers from "opencv/data/haarcascades" directory
 nestedCascade.load( "../../haarcascade_eye_tree_eyeglasses.xml" ) ;

 // Change path before execution
 cascade.load( "../../haarcascade_frontalcatface.xml" ) ;

 // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
 capture.open(0);
 if( capture.isOpened() )
 {
  // Capture frames from video and detect faces
  cout << "Face Detection Started...." << endl;
  while(1)
  {
   capture >> frame;
   if( frame.empty() )
    break;
   Mat frame1 = frame.clone();
   detectAndDraw( frame1, cascade, nestedCascade, scale );
   char c = (char)waitKey(10);
  
   // Press q to exit from window
   if( c == 27 || c == 'q' || c == 'Q' )
    break;
  }
 }
 else
  cout<<"Could not Open Camera";
 return 0;
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
     CascadeClassifier& nestedCascade,
     double scale)
{
 vector<Rect> faces, faces2;
 Mat gray, smallImg;

 cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
 double fx = 1 / scale;

 // Resize the Grayscale Image
 resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
 equalizeHist( smallImg, smallImg );

 // Detect faces of different sizes using cascade classifier
 cascade.detectMultiScale( smallImg, faces, 1.1,
       2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

 // Draw circles around the faces
 for ( size_t i = 0; i < faces.size(); i++ )
 {
  Rect r = faces[i];
  Mat smallImgROI;
  vector<Rect> nestedObjects;
  Point center;
  Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
  int radius;

  double aspect_ratio = (double)r.width/r.height;
  if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
  {
   center.x = cvRound((r.x + r.width*0.5)*scale);
   center.y = cvRound((r.y + r.height*0.5)*scale);
   radius = cvRound((r.width + r.height)*0.25*scale);
   circle( img, center, radius, color, 3, 8, 0 );
  }
  else
   rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
     cvPoint(cvRound((r.x + r.width-1)*scale),
     cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
  if( nestedCascade.empty() )
   continue;
  smallImgROI = smallImg( r );
  
  // Detection of eyes int the input image
  nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2,
          0|CASCADE_SCALE_IMAGE, Size(30, 30) );
  
  // Draw circles around eyes
  for ( size_t j = 0; j < nestedObjects.size(); j++ )
  {
   Rect nr = nestedObjects[j];
   center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
   center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
   radius = cvRound((nr.width + nr.height)*0.25*scale);
   circle( img, center, radius, color, 3, 8, 0 );
  }
 }

 // Show Processed Image with detected faces
 imshow( "Face Detection", img );
}
