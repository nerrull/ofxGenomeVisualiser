#include "genomeviewer.h"

GenomeViewer::GenomeViewer(string path)
{

    viewMain.x=0;
    viewMain.y = 0;
    viewMain.width = ofGetWidth();
    viewMain.height =ofGetHeight();
    cam.setDistance(0);
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);

    projected_mesh.setMode(OF_PRIMITIVE_PATCHES);


    loadChromosome(path);
    createWalkVectors();

    generateTrajectory();
    plane_normal_vector = getAvgVector();

    planeRot.makeRotate(cam.getLookAtDir(), -plane_normal_vector);
    cam.setOrientation(planeRot);
    cam.setDistance(200);
    cam_distance = 200;

    cam.setNearClip(0.1);
    cam.setFarClip(200000);
    projectToPlane();
}


void GenomeViewer::initCam(){



    //    plane.setHeight(500);
    //    plane.setWidth(500);
    //    plane.setOrientation(planeRot);

}


void GenomeViewer::loadChromosome(string path){
    string filepath = path;
    ofFile chromosome (filepath);
     ofBuffer chrom = ofBufferFromFile(chromosome.getAbsolutePath());

    vector<string> temp_gene_list;
    vector<float> temp_gene_fpkm;
    for(auto& line : chrom.getLines()) {
        if(line.size()) {
            string s;
            float x;
            stringstream(line) >> s >> x;
            temp_gene_list.push_back(s);
            temp_gene_fpkm.push_back(x);
        }
    }
    auto it = max_element(std::begin(temp_gene_fpkm), std::end(temp_gene_fpkm)); // c++11
    max_value = *it;
    min_value = *min_element(std::begin(temp_gene_fpkm), std::end(temp_gene_fpkm)); // c++11

    for (size_t i =0; i<temp_gene_fpkm.size(); i++){
        if (temp_gene_fpkm[i] ==min_value) continue;
        gene_fpkm.push_back(temp_gene_fpkm[i]);
        sorted_gene_fpkm.push_back(temp_gene_fpkm[i]);
        gene_list.push_back(temp_gene_list[i]);
    }
    num_genes =gene_list.size();
    ofSort(sorted_gene_fpkm);

}



void GenomeViewer::generateWalkIndexes(){

    float step = num_genes/walk_vectors.size();
    for (size_t i =0; i<walk_vectors.size(); i++){
        valueWalkIndexes.push_back(sorted_gene_fpkm[step*i]);
    }
}


void GenomeViewer::createWalkVectors(){
//        walk_vectors.push_back(ofVec3f(0.,  1.,  1.));
//        walk_vectors.push_back(ofVec3f(1.,  1.,  1.));
//        walk_vectors.push_back(ofVec3f(-1., 1.,  1.));
//        walk_vectors.push_back(ofVec3f(-1., -1., 1.));
//        walk_vectors.push_back(ofVec3f(1.,  -1., 1.));
//        walk_vectors.push_back(ofVec3f(0.,  -1., 1.));
//        walk_vectors.push_back(ofVec3f(-1.,  0., 1.));


//        walk_vectors.push_back(ofVec3f(1.,  0.,  -1.));
//        walk_vectors.push_back(ofVec3f(0.,  1.,  -1.));
//        walk_vectors.push_back(ofVec3f(1.,  1.,  -1.));
//        walk_vectors.push_back(ofVec3f(-1., 1.,  -1.));
//        walk_vectors.push_back(ofVec3f(-1., -1., -1.));
//        walk_vectors.push_back(ofVec3f(1.,  -1., -1.));
//        walk_vectors.push_back(ofVec3f(0.,  -1., -1.));
//        walk_vectors.push_back(ofVec3f(-1.,  0., -1.));

//        walk_vectors.push_back(ofVec3f(1., 0., 0.));
//        walk_vectors.push_back(ofVec3f(0., 1., 0.));
//        walk_vectors.push_back(ofVec3f(1., 1., 0.));
//        walk_vectors.push_back(ofVec3f(-1., 1., 0.));
//        walk_vectors.push_back(ofVec3f(-1., -1., 0.));
//        walk_vectors.push_back(ofVec3f(1., -1., 0.));
//        walk_vectors.push_back(ofVec3f(0., -1., 0.));
//        walk_vectors.push_back(ofVec3f(-1., 0., 0.));

            walk_vectors.push_back(ofVec3f(0.,  1.,  1.));
            walk_vectors.push_back(ofVec3f(1.,  0.,  1.));

            walk_vectors.push_back(ofVec3f(1.,  1.,  1.));
            walk_vectors.push_back(ofVec3f(-1., 1.,  1.));
            walk_vectors.push_back(ofVec3f(-1., -1., 1.));
            walk_vectors.push_back(ofVec3f(1.,  -1., 1.));
            walk_vectors.push_back(ofVec3f(0.,  -1., 1.));
            walk_vectors.push_back(ofVec3f(-1.,  0., 1.));
            walk_vectors.push_back(ofVec3f(0.,  0., 1.));



            walk_vectors.push_back(ofVec3f( 1.,  0., -1.));
            walk_vectors.push_back(ofVec3f( 0.,  1., -1.));
            walk_vectors.push_back(ofVec3f( 1.,  1., -1.));
            walk_vectors.push_back(ofVec3f(-1.,  1., -1.));
            walk_vectors.push_back(ofVec3f(-1., -1., -1.));
            walk_vectors.push_back(ofVec3f( 1., -1., -1.));
            walk_vectors.push_back(ofVec3f( 0., -1., -1.));
            walk_vectors.push_back(ofVec3f(-1.,  0., -1.));
            walk_vectors.push_back(ofVec3f( 0.,  0., -1.));


            walk_vectors.push_back(ofVec3f(1., 0., 0.));
            walk_vectors.push_back(ofVec3f(0., 1., 0.));
            walk_vectors.push_back(ofVec3f(1., 1., 0.));
            walk_vectors.push_back(ofVec3f(-1., 1., 0.));
            walk_vectors.push_back(ofVec3f(-1., -1., 0.));
            walk_vectors.push_back(ofVec3f(1., -1., 0.));
            walk_vectors.push_back(ofVec3f(0., -1., 0.));
            walk_vectors.push_back(ofVec3f(-1., 0., 0.));

//    int num_directions = 16;
//    for (int i=0; i<num_directions; i++){
//        float angle = TWO_PI/num_directions *i;
//        walk_vectors.push_back(ofVec3f(cos(angle),sin(angle), 0.));
//    }

    generateWalkIndexes();


}



ofVec3f GenomeViewer::getDirection(float value){
    size_t i =0;
    for (; i<valueWalkIndexes.size(); i++){
        if (value <=valueWalkIndexes[i]) break;
    }
    return walk_vectors[i-1];
}

ofVec3f GenomeViewer::getAvgVector(){
    int count =0;
    ofVec3f avgVector;
    for (size_t index =0; index < points.size(); index+=10){
        avgVector += points[index];
        count++;
    }
    avgVector = avgVector/count;
    return avgVector.normalize();
}

ofVec3f GenomeViewer::projectToPlane(){
    int count =0;
    float spiral_strength = 0.0;
    ofVec3f proj_point;
    for (size_t index =0; index < points.size(); index+=1){
        float dist = points[index].dot(plane_normal_vector);
        proj_point = points[index] - dist*plane_normal_vector;
        //proj_point*=spiral_strength;
        projected_points.push_back(proj_point);
        projected_mesh.addVertex(proj_point);
        projected_mesh.addColor(mesh.getColor(index));
        //spiral_strength +=0.01;
    }
}


void GenomeViewer::generateTrajectory(){

    ofVec3f current_point(0.,0.,0.);

    float hsb_angle_fraction = 255.0/num_genes;
    ofColor c;
    c.setHsb(0., 200.,200.);

    points.push_back(current_point);
    mesh.addVertex(points[0]);
    mesh.addColor(c);    ofVec3f pos = cam.getPosition();
    float radius  = pos.length();
    pos += ofVec3f(cos(rotation_value*2*PI/1000.)*radius, sin(rotation_value*2*PI/1000.)*radius,0.);
    cam.setPosition(pos);
    cam.lookAt(ofVec3f(0.,0.,0.));

    mesh.clear();
    points.clear();
    projected_mesh.clear();
    float angle_fraction = 10*TWO_PI/num_genes;
    float spiral_strength = 0.0;

    for (size_t index =0; index < gene_fpkm.size(); index++){
        //float value = pow(2,gene_fpkm[index] );
        float value = gene_fpkm[index];

        if (value == min_value){
            continue;
        }

        c.setHsb(index *hsb_angle_fraction, 200.,200.);


        ofVec3f step = getDirection(value);
        float x_coord = cos(angle_fraction * index) *current_point.x;
        float y_coord = sin(angle_fraction * index) *current_point.y;
        ofVec3f rotate_step(x_coord, y_coord, 0.);

        current_point +=  step;
        points.push_back(current_point);
        mesh.addVertex(current_point);
        mesh.addColor(c);
        line.addVertex(current_point);

    }
}

void GenomeViewer::setColor(int i){
    ofColor c;
    c.setHsb((i+3)*255./6., 0.9*255, 0.9*255, 0.9*255);
    for (size_t index =0; index < points.size(); index++){
        mesh.setColor(index, c);
        projected_mesh.setColor(index, c);

    }
}
void GenomeViewer::setSpectrumColor(){
    ofColor c;
    float hsb_angle_fraction = 255.0/num_genes;

    for (size_t index =0; index < points.size(); index++){
        c.setHsb(index *hsb_angle_fraction, 200.,200.);
        mesh.setColor(index, c);
        projected_mesh.setColor(index, c);

    }
}


void GenomeViewer::resize(int x,int y,int w,int h){
    viewMain.x=x;
    viewMain.y = y;
    viewMain.width = w;
    viewMain.height =h;
}

void GenomeViewer::draw(){
    cam.begin(viewMain);
    ofNoFill();
    ofSetColor(255);
    if (DRAW_POINTS==0){

        mesh.draw();
        projected_mesh.draw();
    }

    if (DRAW_POINTS==1){

        projected_mesh.draw();
    }
    if (DRAW_POINTS==2){

        mesh.draw();
    }

    cam.end();
}
void GenomeViewer::toggleDrawPoints(){
   DRAW_POINTS +=1;
   DRAW_POINTS = DRAW_POINTS%3;
}


void GenomeViewer::update(){
    cam_distance +=cam_movement;
    cam.setDistance(cam_distance);

    rotation_value +=rotation;
    if (rotation !=0.){
//        ofVec3f pos = cam.getPosition();
//        float radius  = pos.length();
//        pos += ofVec3f(cos(rotation_value*2*PI/1000.)*radius, sin(rotation_value*2*PI/1000.)*radius,0.);
//        cam.setPosition(pos);
//        cam.lookAt(ofVec3f(0.,0.,0.));
        cam.orbit(rotation_value,0.,cam_distance);
    }
}


void GenomeViewer::forward(){
    cam_movement -=1;
    if (cam_movement >0) cam_movement=0.;
}


void GenomeViewer::backward(){
    cam_movement +=1;
    if (cam_movement <0.) cam_movement=0.;
}


void GenomeViewer::setRotation(float r){

    rotation += r;
    if (r<0. && rotation >0.) rotation=0.;
    if (r>0. && rotation <0.) rotation=0.;

}

void GenomeViewer::resetRotation(){
    rotation = 0;
    rotation_value= 0;
    planeRot.makeRotate(cam.getLookAtDir(), -plane_normal_vector);
    cam.setOrientation(planeRot);
}

void GenomeViewer::setMode(int m ){
    if (m ==0){
        projected_mesh.setMode(OF_PRIMITIVE_POINTS);

    }
    else if (m ==1){
        projected_mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    }

    else if (m ==2){
        projected_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    }
}
