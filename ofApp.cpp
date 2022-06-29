#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(150, 2);
	this->noise_value = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.05, avg.y * 0.05, avg.z * 0.05, this->noise_value);

		float noise_radius = 150;
		noise_radius = ofMap(noise_value, 0, 1, 50, 350);

		int index = this->mesh.getNumVertices();

		this->mesh.addVertex(glm::normalize(avg) * (noise_radius + 100));
		this->mesh.addVertex(glm::normalize(triangle.getVertex(0)) * noise_radius);
		this->mesh.addVertex(glm::normalize(triangle.getVertex(1)) * noise_radius);
		this->mesh.addVertex(glm::normalize(triangle.getVertex(2)) * noise_radius);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);
	}

	if (ofGetFrameNum() % 120 < 60) {

		this->noise_value += ofMap(ofGetFrameNum() % 120, 0, 60, 0, 0.2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.43);
	ofRotateY(ofGetFrameNum() * 0.65);

	ofSetColor(235, 97, 1);
	this->mesh.drawFaces();

	ofSetColor(255);
	this->mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}