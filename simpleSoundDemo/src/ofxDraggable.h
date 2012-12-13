class ofxDraggable : public ofxMSAInteractiveObject {  
public:  
    ofBaseDraws *content; // this will point to your image, video, grabber etc.  
      
    ofxDraggable() {
        content = NULL;
    }
    
    void setup(){
         enableMouseEvents();
    }
      
    void onPress(int mx, int my, int button) {  
        // save the offset of where the mouse was clicked...  
        // ...relative to the position of the object
        saveX = mx - this->x;  
        saveY = my - this->y;  
    }  
      
    void onDragOver(int mx, int my, int button) {  
        this->x = mx - saveX;    // update x position  
        this->y = my - saveY;    // update mouse y position  
    }  
      
    void draw() {  
        if(content) {
            ofEnableAlphaBlending();
            width = content->getWidth();  
            height = content->getHeight();  
            content->draw(x, y, width, height);
            ofDisableAlphaBlending();

        }
    }  
      
protected:  
    int saveX, saveY;  
};  