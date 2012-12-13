#pragma once

#include "ofMain.h"
#include "sndfile.h"
#include "ofSoundPlayerWithData.h"
#include "ofxTweenzor.h"
#include "ofxMSAInteractiveObject.h"
#include "ofxDraggable.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void tweenComplete(float* arg);

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        void triggerKangarooHop();
        void triggerWombatColorChange();

    
    ofSoundPlayerWithData 		voice_sound;
    ofSoundPlayerWithData		drums_sound;
    ofSoundPlayerWithData		piano_sound;
    ofSoundPlayerWithData		rest_sound;
    
    float voice_vol, drums_vol, piano_vol, rest_vol;

    short *sample;
    
    ofImage             image_bg;
    ofImage             image_1, image_3, image_4;

    ofPoint     im1_loc, im2_loc, im3_loc, im4_loc;
    
    ofImage image_kanga;
    float   kanga_x, kanga_y;
    bool    kanga_is_hopping;
    
    ofImage image_hedge;
    float hedge_x, hedge_y, hedge_vx, hedge_vy, hedge_rot;
    
    ofImage image_wombat;
    float wombat_scale, wombat_x, wombat_y;
    float wombat_r, wombat_g, wombat_b;
    ofxDraggable msa_wombat;
    
    
    int drawCounter, bufferCounter;
    
    
    
};
