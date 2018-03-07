#ifndef GENOMEVIEWER_H
#define GENOMEVIEWER_H
#include "ofMain.h"

class GenomeViewer
{
public:
    GenomeViewer(string path);

    void loadChromosome(string);
    void createWalkVectors();
    void generateTrajectory();
    void generateWalkIndexes();
    ofVec3f getAvgVector();
    ofVec3f getDirection(float value);
    ofVec3f projectToPlane();
    void draw();
    void resize(int x,int y,int w,int h);
    void forward();
    void backward();
    void toggleDrawPoints();
    void update();
    void setRotation(float r);
    void resetRotation();

    void setMode(int);
    void setColor(int i);
    void initCam();
    void setSpectrumColor();





    int cam_distance =0;
    int cam_movement=0;

    ofEasyCam cam;
    ofRectangle viewMain;

    vector<string> gene_list;
    vector<float> gene_fpkm;
    vector<float> sorted_gene_fpkm;
    vector<ofVec3f> points;
    vector<ofVec3f> projected_points;
    vector<ofVec3f> walk_vectors;
    vector<float> valueWalkIndexes;
    ofVboMesh mesh;
    ofVboMesh projected_mesh;
    ofVec3f plane_normal_vector;
    ofQuaternion planeRot;
    ofPolyline line;
    ofPlanePrimitive plane;

    float rotation =0;
    float rotation_value=0;
    float max_value;
    float min_value;
    size_t num_genes;
    int DRAW_POINTS = 0;





};

#endif // GENOMEVIEWER_H
