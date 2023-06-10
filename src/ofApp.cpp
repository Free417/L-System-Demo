#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();	// IMPORTANT!

	// Used for optimization
	ofSetVerticalSync(false);

	ofFill();
	ofSetLineWidth(10);
	ofClear(0);
	ofScale(1.0f, -1.0f);
	ofTranslate(kWindow_width / 2, -kWindow_height + 75);
	ofLine(0, 0, 0, 300);
	angleDepart -= 1;
	splitLine(0, 300, 20, angleDepart);

	//light
	light.setPosition(500, 1000, 1600);
	light.enable();

	// The camera
	cam.setPosition(0, 100, 600);
	cam.lookAt(ofVec3f(0, 0, 0));
	//cam.setNearClip(0.01f);
	//cam.setMovementMaxSpeed( 25.f );

	// The plane
	plane.setPosition(100, 0, 0);
	plane.set(20000, 20000);
	plane.setResolution(20, 20);
	plane.rotate(270, 1, 0, 0);

	// The road
	roadMaterial.setDiffuseColor(ofFloatColor::moccasin);
	roadMaterial.setShininess(0.01);

	// The trees
	treeMaterial.setAmbientColor(ofFloatColor::hotPink);
	treeMaterial.setSpecularColor(ofFloatColor::blueSteel);
	treeMaterial.setDiffuseColor(ofFloatColor::yellowGreen);
	treeMaterial.setShininess(0.04);

	map<string, float> constants;
	constants.insert(make_pair("R", 1.356));

	ofDisableAlphaBlending();
	ofEnableDepthTest();

	// The light
	light.enable();
	light.setPosition(ofVec3f(400, 300, 200));
	light.lookAt(ofVec3f(0, 0, 0));

	string textureName = "texture.png";
	//string textureName = "bark.jpg";

	// Generate initial forest
	regenerateForest(nTree, constants, forest);

	ofEnableDepthTest();
}

void ofApp::regenerateForest(int nTree, Constants constants, ofMesh& forest)
{
	if (forest.getNumIndices() != 0)
	{
		// Clears previous forest, if there was one
		forest.clear();
	}
	for (int i = 0; i < nTree; i++) {
		// Initialization of L-System
		ofxLSystem tree;

		// Sets the axiom (the initial value
		tree.setAxiom("A(100)");

		// Sets rules to modify the axiom
		tree.setRules({ "A(s) -> F(s)[+A(s/R)][-A(s/R)]" });

		tree.setRandomYRotation(true);
		tree.setConstants(constants);
		tree.setStep(abs(ofRandom(6, 9)));
		tree.setScaleWidth(true);
		tree.setResolution(20);
		tree.setStep(abs(ofRandom(5, 7)));
		tree.setStepWidth(abs(ofRandom(30.5, 40.5)));
		tree.setStepLength(abs(ofRandom(150, 300)));
		tree.build();

		// Sets random position
		auto pos = ofVec2f(ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2),
			ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2));
		for (int i = 0; i < tree.getMesh().getNumVertices(); i++) {
			tree.getMesh().getVerticesPointer()[i] += ofVec3f(pos.x, 0, pos.y);
		}

		// Adds tree to mesh
		forest.append(tree.getMesh());
	}
}

//--------------------------------------------------------------
void ofApp::splitLine(int iX, int iY, int iThickness, float iAngle)
{
	if (iThickness - 1 > 0)
	{
		ofPushMatrix();
		ofTranslate(iX, iY);
		ofRotateZ(iAngle);
		ofSetLineWidth(iThickness - 1);
		ofLine(0, 0, iX * 0.75, iY * 0.75);
		splitLine(iX * 0.75, iY * 0.75, iThickness - 1, iAngle);
		ofPopMatrix();

		ofPushMatrix();
		ofLine(0, 0, iX * 0.75, iY * 0.75);
		ofSetColor(65, ofRandom(255), 0);
		splitLine(iX * 0.75, iY * 0.75, iThickness - 2, -iAngle);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	using namespace glm;

	ofDisableLighting();
	ofDisableDepthTest();

	// Sets the background color as a gradient
	ofBackgroundGradient(ofFloatColor::indigo, ofFloatColor::lemonChiffon, OF_GRADIENT_CIRCULAR);

	ofEnableDepthTest();
	ofEnableLighting();
	cam.begin();
	roadMaterial.begin();
	plane.draw();

	roadMaterial.end();
	treeMaterial.begin();
	forest.draw();
	treeMaterial.end();
	cam.end();

	// Used for optimization
	drawFrameTime();
}

void ofApp::drawFrameTime()
{
	glDisable(GL_CULL_FACE);
	std::string frameTimeStr{
		to_string(ofGetLastFrameTime() * 1000.0)
		+ "ms/n" + to_string(ofGetFrameRate()) + "fps" };
	ofDrawBitmapStringHighlight(frameTimeStr, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	map<string, float> constants;
	constants.insert(make_pair("R", 1.356));

	// Loads a new configuration of trees
	if (key == '`')
	{
		//needsReload = true;
		regenerateForest(nTree, constants, forest);
	}
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::saveMesh() {
	string randomFilename = ofGetTimestampString() + ".ply";
	forest.save(randomFilename);
}