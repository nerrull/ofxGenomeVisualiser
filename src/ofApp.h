#pragma once

#include "ofMain.h"
#include "genomeviewer.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void setFullscreen(int index);



    vector<GenomeViewer*> genome_viewers;

    bool FORWARD = false;
    bool BACKWARD = false;
    int fullScreenIndex =-1;

    ofImage img;
    int shotCounter = 0;
    int MODE =0;

    bool SPECTRUM= false;

};
