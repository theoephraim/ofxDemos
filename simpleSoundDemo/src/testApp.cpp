#include "testApp.h"
#include <sndfile.hh>
#include <stdio.h>


#define FRAMERATE 60
#define SONG_START_MS 13500
#define KANGA_START_X -500
#define KANGA_START_Y 250



//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate( FRAMERATE );
	ofSetVerticalSync(true);
    
	// must call this before adding any tweens
	Tweenzor::init();
    
    
    // load in sounds
    voice_sound = ofSoundPlayerWithData( "sounds/voice.wav" );
    drums_sound = ofSoundPlayerWithData( "sounds/drums.wav" );
    piano_sound = ofSoundPlayerWithData( "sounds/piano.wav" );
    rest_sound = ofSoundPlayerWithData( "sounds/rest.wav" );
    
    image_bg.allocate( 1810, 784, OF_IMAGE_COLOR );
    image_bg.loadImage( "images/mars_surface.jpg" );
    
    
    // hopping kangaroo
    image_kanga.allocate( 527, 400, OF_IMAGE_COLOR_ALPHA );
    image_kanga.loadImage( "images/kangaroo.png" );
    kanga_x = KANGA_START_X;
    kanga_y = KANGA_START_Y;
    kanga_is_hopping = false;
    
    
    // spinning hedgehog
    image_hedge.allocate(280, 280, OF_IMAGE_COLOR_ALPHA );
    image_hedge.loadImage( "images/hedgehog.png" );
    hedge_x = ofRandom( 300, ofGetWidth()-300 );
    hedge_y = ofRandom( 300, ofGetHeight()-300 );
    hedge_vx = ofRandom( 30, 100 );
    hedge_vy = ofRandom( 30, 100 );
    hedge_rot = ofRandom( 0, 360 );
    
    // scary wombat!
    image_wombat.allocate( 470, 276, OF_IMAGE_COLOR_ALPHA );
    image_wombat.loadImage( "images/wombat.png" );
    wombat_x = 300;
    wombat_y = ofGetHeight();
    wombat_r = ofRandom( 0, 255 );
    wombat_g = ofRandom( 0, 255 );
    wombat_b = ofRandom( 0, 255 );
    msa_wombat.content = &image_wombat;
    
    sample = new short[256];
    
    drawCounter	= 0;
    bufferCounter = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
    ofBackground(255,0,0);
    
    // different smoothing needed for different movements and sounds
    voice_vol = voice_vol * .60 + voice_sound.getCurrentLevel() * .3;
    drums_vol = drums_vol * .10 + drums_sound.getCurrentLevel() * .90;
    piano_vol = piano_vol * .30 + piano_sound.getCurrentLevel() * .70;
    rest_vol = rest_vol * .97 + rest_sound.getCurrentLevel() * .03;

    // trigger kangaroo hop on bass and snare -- loud peaks
    if (drums_vol > 180 ){
        triggerKangarooHop();
    }
    
    // hedgehog bounces around the screen and spins with the voice track
    hedge_x += hedge_vx / FRAMERATE ;
    hedge_y += hedge_vy / FRAMERATE ;
    hedge_rot += voice_vol/100;
    if ( hedge_x - image_hedge.width/2 < 0 || hedge_x + image_hedge.width/2 > ofGetWidth() ){
        hedge_vx *= -1;
        hedge_vx += ofRandom( -10, 10 );
    }
    if ( hedge_y - image_hedge.height/2 < 0 || hedge_y + image_hedge.height/2 > ofGetHeight() ){
        hedge_vy *= -1;
        hedge_vy += ofRandom( -10, 10 );
    }
    
    // wombat changes color on loud piano hits -- draggable in X dimension
    if (piano_vol > 100){
        triggerWombatColorChange();
    }
    bufferCounter++;
}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255,255,255);
    image_bg.draw(0,0);

    ofEnableAlphaBlending();
    image_kanga.draw( kanga_x, kanga_y );
    
    ofPushMatrix();
        ofTranslate(hedge_x, hedge_y );
        ofRotate( hedge_rot );
        image_hedge.setAnchorPercent(.5, .5);
        image_hedge.draw(0, 0);
    ofPopMatrix();
    
    
    ofSetColor( wombat_r, wombat_g, wombat_b );
//    image_wombat.setAnchorPercent(.5, 1);
//    image_wombat.draw( wombat_x, wombat_y );
    msa_wombat.y = ofGetHeight() - msa_wombat.height;
    msa_wombat.draw();
    //switched to MSA object to make it draggable
    
    ofDisableAlphaBlending();
    
    // draws circles to show smoothed volume
//    ofSetColor(100, 0 , 0);
//    ofCircle( 100, 350, voice_vol );
//    ofCircle( 300, 350, drums_vol );
//    ofCircle( 500, 350, piano_vol );
//    ofCircle( 700, 350, rest_vol );
        
    drawCounter++;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout << "Key = " << key << "\n";
    
    // Toggle sounds on-off
    if ( key == 49 ){
        drums_sound.setVolume( drums_sound.getVolume() == 0 ? 1 : 0 );
    } else if ( key == 50 ){
        piano_sound.setVolume( piano_sound.getVolume() == 0 ? 1 : 0 );
    } else if ( key == 51 ){
        voice_sound.setVolume( voice_sound.getVolume() == 0 ? 1 : 0 );
    } else if ( key == 52 ){
        rest_sound.setVolume( rest_sound.getVolume() == 0 ? 1 : 0 );
    }
    
    // restart the tracks
    if ( key == 32 ){
        if ( !drums_sound.getIsPlaying() ){
            drums_sound.play();
            piano_sound.play();
            voice_sound.play();
            rest_sound.play();   
        }
        // there is some silence at the begninng -- skip ahead to where the music starts
        drums_sound.setPositionMS( SONG_START_MS );
        piano_sound.setPositionMS( SONG_START_MS );
        voice_sound.setPositionMS( SONG_START_MS );
        rest_sound.setPositionMS( SONG_START_MS );
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


// --------------------------------------------------------------

void testApp::triggerKangarooHop(){
    if ( kanga_is_hopping ) return;
    
    kanga_is_hopping = true;
    Tweenzor::add( &kanga_x, kanga_x, kanga_x+100, 0.f, 0.14, EASE_LINEAR );
    Tweenzor::add( &kanga_y, kanga_y, kanga_y-50, 0.0f, 0.07, EASE_LINEAR );
    Tweenzor::getTween( &kanga_y )->setRepeat( 1, true );
    
    Tweenzor::addCompleteListener( Tweenzor::getTween(&kanga_x), this, &testApp::tweenComplete);

}

void testApp::triggerWombatColorChange(){
    Tweenzor::add( &wombat_r, wombat_r, ofRandom(0,255), 0.f, 0.5, EASE_LINEAR );
    Tweenzor::add( &wombat_g, wombat_g, ofRandom(0,255), 0.f, 0.5, EASE_LINEAR );
    Tweenzor::add( &wombat_b, wombat_b, ofRandom(0,255), 0.f, 0.5, EASE_LINEAR );
}
void testApp::tweenComplete(float* arg){
    
    // kangaroo hop
    if(arg == &kanga_x) {
        kanga_is_hopping = false;
        if ( kanga_x > ofGetWidth() ){
            kanga_x = KANGA_START_X;
        }
    } else {
        
    }
}


