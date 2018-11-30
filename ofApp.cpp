#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);

	this->size = 45;
	this->font.loadFont("fonts/msgothic.ttc", this->size * 0.8, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<int> row_values;
	vector<int> col_values;

	ofDrawLine(0, this->size * 3 + 5, ofGetWidth(), this->size * 3 + 5);
	ofDrawLine(this->size * 4 - 5, 0, this->size * 4 - 5, ofGetHeight());

	for (int y = 4 * this->size; y <= ofGetHeight(); y += this->size) {

		int row_value = 0;
		int row_param = 8;
		for (int row = 0; row < 4; row++) {

			int x = row * this->size;
			int value = ofNoise(ofRandom(100), ofGetFrameNum() * 0.005) > 0.5 ? 0 : 1;

			this->font.drawString(to_string(value), x, y);

			row_value += value * row_param;
			row_param /= 2;
		}

		row_values.push_back(row_value);
	}

	for (int x = 4 * this->size; x <= ofGetWidth(); x += this->size) {
		
		int col_value = ofMap(ofNoise(ofRandom(100), ofGetFrameNum() * 0.005), 0, 1, 2, 8);
		col_value *= 16;
		int tmp_col_value = col_value;

		int col_param = 64;
		for (int col = 1; col < 4; col++) {

			int y = col * this->size;
			int value = tmp_col_value / col_param;

			this->font.drawString(to_string(value), x, y);
			tmp_col_value = tmp_col_value % col_param;
			col_param /= 2;
		}

		col_values.push_back(col_value);
	}

	for (int row_index = 0; row_index < row_values.size(); row_index++) {

		for (int col_index = 0; col_index < col_values.size(); col_index++) {

			char sum = row_values[row_index] + col_values[col_index];
			string sum_str = { sum };

			this->font.drawString(sum_str, col_index * this->size + this->size * 4, row_index * this->size + this->size * 4);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}