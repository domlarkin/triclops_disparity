#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include "cv.h"
#include "highgui.h"
#include <triclops/triclops.h>
#include <triclops/fc2triclops.h>

//#include "usma_triclops/typedefs.h"
#include "common.h"

namespace FC2 = FlyCapture2;
namespace FC2T = Fc2Triclops;

class CameraSystem
{
    public:
    CameraSystem();
    ~CameraSystem();
        int startUp();
        // configue camera to capture image
        void run();
        // convert image to BRGU
        int convertToBGRU( FC2::Image & image, FC2::Image & convertedImage );
        // convert image to BRG
        int convertToBGR( FC2::Image & image, FC2::Image & convertedImage );
        TriclopsContext triclops;
        ;
        std::string getResolution();
        int shutdown();
        int setDispMax(int disp){disp_max=disp;return 0;}
        int setDispMin(int disp){disp_min=disp;return 0;}
        int setDispMapMax(int disp){disp_map_max=disp;return 0;}
        int setDispMapMin(int disp){disp_map_min=disp;return 0;}
        int setStereoMask(int mask){stereo_mask=mask;return 0;}
        cv::Mat getDisparityImage(){return disparityImageCV;}

    private:
        // carry out stereo processing pipeline
        int doStereo( TriclopsContext const & triclops,
                      TriclopsInput  const & stereoData,
                      TriclopsImage      & depthImage );
        // generate triclops input necessary to carry out stereo processing
        int generateTriclopsInput( FC2::Image const & grabbedImage,
                                   ImageContainer   & imageContainer,
                                   TriclopsInput    & colorData,
                                   TriclopsInput    & stereoData );
        // generare triclops input
        int generateTriclopsInput( FC2::Image const & grabbedImage,
                                   ImageContainer   & imageCont,
                                   TriclopsInput    & triclopsInput );
        // generate Triclops context from connected camera
        int generateTriclopsContext( FC2::Camera     & camera,
                                     TriclopsContext & triclops );
        // capture image from connected camera
        int grabImage( FC2::Camera & camera, FC2::Image & grabbedImage );
        int configureCamera( FC2::Camera &camera );
        FC2::Camera camera;
        FC2::Image grabbedImage;
        TriclopsInput color;
        TriclopsInput mono;
        TriclopsImage disparityImageTriclops;
        cv::Mat disparityImageCV;
FC2::CameraInfo camInfo;
int disp_max;
        int disp_min;
        int disp_map_max;
        int disp_map_min;
        int disp_map_on;
        int stereo_mask;
};

#endif // CAMERA_SYSTEM_H
