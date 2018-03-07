#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){


    ofBackground(0);
    ofSetFrameRate(60);



    ofEnableAlphaBlending();
    ofEnableDepthTest();
    glPointSize(2.0);

    genome_viewers.push_back( new GenomeViewer("ALL_GTEX_2.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_GTEX_3.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_GTEX_4.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_TCGA_10000.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_TCGA_10001.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_TCGA_10002.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_TARGET_8000.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_TARGET_8001.txt"));
    genome_viewers.push_back( new GenomeViewer("ALL_TARGET_8003.txt"));

    windowResized(ofGetWidth(),ofGetHeight());

}




//void ofApp::createCirclePointCloud(){
//    float angle_fraction = TWO_PI/num_genes;
//    mesh.clear();
//    for (size_t index =0; index < gene_fpkm.size(); index++){
//        //float value = pow(2,gene_fpkm[index] );

//        float value = gene_fpkm[index];
//        float x_coord = cos(angle_fraction * index)* abs(value);
//        float y_coord = sin(angle_fraction * index)*abs(value);
//        if (value >0){
//            mesh.addColor(ofColor(0,255,0));
//        }
//        else mesh.addColor(ofColor(255,0,0));


//        points.push_back(ofVec3f(x_coord, y_coord, 0));
//        mesh.addVertex(points[index]);
//    }
//}






//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < genome_viewers.size(); i++){
        genome_viewers[i]->update();

    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (fullScreenIndex != -1){
        genome_viewers[fullScreenIndex]->draw();
        return;
    }
    for (int i = 0; i < genome_viewers.size(); i++){
        genome_viewers[i]->draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'w') {
        for (int i = 0; i < genome_viewers.size(); i++){
            genome_viewers[i]->forward();
        }
    }

    if (key == 's') {
        for (int i = 0; i < genome_viewers.size(); i++){
            genome_viewers[i]->backward();
        }
    }

    if (key == 'a') {
        for (int i = 0; i < genome_viewers.size(); i++){
            genome_viewers[i]->setRotation(.2);
        }
    }

    if (key == 'd') {
        for (int i = 0; i < genome_viewers.size(); i++){

            genome_viewers[i]->setRotation(-.2);
        }

    }

    if (key == 'c') {
        for (int i = 0; i < genome_viewers.size(); i++){

        genome_viewers[i]->resetRotation();
        }

    }

    if (key == ' ') {
        for (int i = 0; i < genome_viewers.size(); i++){
            genome_viewers[i]->toggleDrawPoints();
        }
    }

    if (key == '0') {
        fullScreenIndex = -1;
        windowResized(ofGetWidth(), ofGetHeight());
    }

    if (key == '1') {
        setFullscreen(0);
    }
    if (key == '2') {
        setFullscreen(1);
    }
    if (key == '3') {
        setFullscreen(2);
    }
    if (key == '4') {
        setFullscreen(3);
    }
    if (key == '5') {
        setFullscreen(4);
    }
    if (key == '6') {
        setFullscreen(5);
    }
    if (key == '7') {
        setFullscreen(6);
    }
    if (key == '8') {
        setFullscreen(7);
    }
    if (key == '9') {
        setFullscreen(8);
    }
    if (key == '-') {
        int row = 0;
        SPECTRUM = !SPECTRUM;
        for (int i = 0; i < genome_viewers.size(); i++){
            if (i >0 && i%3 ==0){
                row++;
            }
            if (SPECTRUM) genome_viewers[i]->setSpectrumColor();
            else genome_viewers[i]->setColor(row);
        }
    }

    if (key == '=') {
        int row = 0;
        for (int i = 0; i < genome_viewers.size(); i++){
            if (i >0 && i%3 ==0){
                row++;
            }
            genome_viewers[i]->resize(0,0, ofGetWidth(), ofGetHeight());
            //genome_viewers[i]->setColor(row);

        }
    }

    if(key == 'x'){
        shotCounter +=1;
            img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
            img.save("screenshot" + std::to_string(shotCounter)+".png");
        }

    if(key == 'm'){
        MODE++;
        MODE = MODE%3;
        for (int i = 0; i < genome_viewers.size(); i++){
            genome_viewers[i]->setMode(MODE);
        }
    }

}


void ofApp::setFullscreen(int index){
    fullScreenIndex = index;
    genome_viewers[index]->resize(0,0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    int row=0;
    int col=0;

    int width  =ofGetWidth()/3;
    int height  =ofGetHeight()/3;


    for (int i = 0; i < genome_viewers.size(); i++){
        col = i%3;
        if (i>0 &&i%3==0){
            row +=1;
        }
        genome_viewers[i]->resize(width*col,height*row, ofGetWidth()/3, ofGetHeight()/3);
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
