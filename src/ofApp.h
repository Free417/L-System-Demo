#pragma once

#include "ofMain.h"
#include "ofxLSystem.h"
#include "Camera.h"
#include "CameraMatrices.h"

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

		// Saves current mesh if desired for later use
		void saveMesh();
		
	private: 
		// Used to spawn forest and replace current one (if present)
		void regenerateForest(int nTree, Constants constants, ofMesh& forest);

		// Used for optimization
		void ofApp::drawFrameTime();

		// Used for splitLine to calculate the angle used for next production
		int angleDepart = 0;

		// Set window height
		const int kWindow_height = 1000;

		// Set window width
		const int kWindow_width = 1200;

		// 
		void splitLine(int iX, int iY, int iThickness, float angle);

		// L-System
		ofxLSystem tree;

		// Mesh for the trees
		ofMesh forest;

		// Number of trees to spawn
		int nTree = 30;

		// Light source
		ofLight light;

		// Camera
		ofEasyCam cam;

		// Plane
		ofPlanePrimitive plane;

		// Material for plane
		ofMaterial roadMaterial;

		// Material for trees
		ofMaterial treeMaterial;
};
