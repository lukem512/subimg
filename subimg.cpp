#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
    Mat img, img_gray, subimg;
    int ii, jj;
    int x1, y1;
    int x2, y2;

    if (argc != 6)
    {
        cout << "Usage: " << argv[0] << " imagename.jpg x1 y1 x2 y2" << endl;
        return EXIT_FAILURE;
    }

    // load the image
    img = imread(argv[1]);

    // convert to grayscale
    cvtColor(img, img_gray, CV_BGR2GRAY);

    if (!img.data)
    {
        cout << "Could not find or open image " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    // get the sub image coordinates
    x1 = atoi(argv[2]);
    y1 = atoi(argv[3]);
    x2 = atoi(argv[4]);
    y2 = atoi(argv[5]);

    cout << "Creating sub image from (" << x1 << "," << y1 << ")";
    cout << " to (" << x2 << "," << y2 << ")" << endl; 

    // check order of points
    if (x1 > x2 || y1 > y2)
    {
        cout << "Please specify coordinates in-order" << endl;
        return EXIT_FAILURE;
    }
    
    // create the sub image
    subimg.create(x2-x1, y2-y1, CV_8U);
    subimg.setTo(Scalar(0));

    // get the sub image
    for (ii=0;ii<subimg.rows;ii++)
        for (jj=0;jj<subimg.cols;jj++)
            subimg.at<uchar>(jj,ii) = img_gray.at<uchar>(jj+x1,ii+y1);

    // display the sub image
    namedWindow("subimg", CV_WINDOW_AUTOSIZE);
    imshow("subimg", subimg);

    // wait for keypress
    waitKey(0);
    return EXIT_SUCCESS;
}
