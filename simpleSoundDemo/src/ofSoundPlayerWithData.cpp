//
//  ofSoundPlayerWithData.cpp
//  demo1
//
//  Created by Theo Ephraim on 12/10/12.
//
//

#include "ofSoundPlayerWithData.h"
#define BUFFER_LEN 512
#define SAMPLE_LEN 256

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

ofSoundPlayerWithData::ofSoundPlayerWithData(){
    //do nothing?
}

ofSoundPlayerWithData::ofSoundPlayerWithData ( string fileName ){
    fileHandle = SndfileHandle( ofToDataPath( fileName ) );
    
    if ( fileHandle.error() ){
        cout << "ERROR READING FILE" << fileName << "\n";
        cout << fileHandle.strError();
        return;
    }
    printf("File Loaded Successfully -- %s\n", fileName.c_str() );
    
    numChannels = fileHandle.channels();
    sampleRate = fileHandle.samplerate();
    numFrames = fileHandle.frames();
    
    cout << "File Loaded -- " << fileName << "\n";
    cout << " -- Num Channels : " << numChannels << "\n";
    cout << " -- Sample Rate : " << sampleRate << "\n";
    cout << " -- Num Frames : " << numFrames << "\n";
    cout << " -- Length (min) : " << (numFrames / sampleRate / 60.0) << "\n";
    
    player.loadSound( fileName );
    
    short *audioDataTemp = new short[ numFrames * numChannels ];
    fileHandle.readf( audioDataTemp, numFrames );
    
    audioData = new short*[ numChannels ];
    for (int c=0; c<numChannels; c++){
        audioData[c] = new short[ numFrames ];
        for (int f=0; f<numFrames; f++){
            audioData[c][f] = audioDataTemp[ numChannels*f + c ];
        }
    }
    delete audioDataTemp;
    
    levelSample = new short[ SAMPLE_LEN ];
}

float ofSoundPlayerWithData::getCurrentLevel(){
    // uses root mean square to roughly calculate volume
    //  not really sure about what scale this is at
    getCurrentSample( levelSample, SAMPLE_LEN );
    double curLevel = 0;
    
    for (int i=0; i<SAMPLE_LEN; i++){
        curLevel = levelSample[i] * levelSample[i];
    }
    curLevel /= (double) SAMPLE_LEN;
    curLevel = sqrt( curLevel );
    return curLevel;
}
void ofSoundPlayerWithData::getCurrentSample( short *sampleBuffer, int sampleSize ){
    int currentFrame = player.getPositionMS() / 1000.0 * sampleRate;
    // ensure we don't read past the end of the data at the very end of the track
    if ( currentFrame + sampleSize >= numFrames ){
        currentFrame = numFrames - sampleSize - 1;
    }
    std::memcpy( sampleBuffer, &audioData[0][ currentFrame ], sizeof(short) * sampleSize);
}


// ofSoundPlayer calls
void ofSoundPlayerWithData::play(){
    player.play();
}
void ofSoundPlayerWithData::setPositionMS( int seek ){
    player.setPositionMS( seek );
}
void ofSoundPlayerWithData::setVolume( float newVolume ){
    player.setVolume( newVolume );
}
float ofSoundPlayerWithData::getVolume(){
    return player.getVolume();
}
bool ofSoundPlayerWithData::getIsPlaying(){
    return player.getIsPlaying();
}
// TODO: fill in rest of ofSoundPlayer's calls -- or better yet, make this class extend ofSoundPlayer



