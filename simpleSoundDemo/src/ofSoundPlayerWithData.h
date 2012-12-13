//
//  ofSoundPlayerWithData.h
//  demo1
//
//  Created by Theo Ephraim on 12/10/12.
//
//

#ifndef __demo1__ofSoundPlayerWithData__
#define __demo1__ofSoundPlayerWithData__

#include <iostream>
#include "ofMain.h"
#include <sndfile.hh>
#include <stdio.h>
#include <algorithm>
#include <vector>


class ofSoundPlayerWithData {

    public:
        ofSoundPlayerWithData();
        ofSoundPlayerWithData( string fileName );
    
        // wrappers for the ofSoundPlayer functions
        void play();
        void setPositionMS( int seek );
        void setVolume( float newVolume );
        bool getIsPlaying();
        float getVolume();
    
        // functions to get the data
        float getCurrentLevel();
        void getCurrentSample( short *sampleBuffer, int sampleSize );
    
        // info about sound file
        short **audioData;
        short *levelSample;
        int numFrames;
        int numChannels;
        int sampleRate;
    
        ofSoundPlayer player;
    private:
        SndfileHandle fileHandle;
        
};

#endif /* defined(__demo1__ofSoundPlayerWithData__) */
