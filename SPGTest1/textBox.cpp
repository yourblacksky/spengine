#include "StdAfx.h"
#include "textBox.h"

textBox::textBox(){

	lineDis = 0;
	wordDis = 0;
	height = 600;
	width = 400;
	autoSwitch = false;
}

textBox::textBox(int LD, int WD, int H, int W, bool AW) {

	this->lineDis = LD;
	this->wordDis = WD;
	this->height = H;
	this->width = W;
	this->autoSwitch = AW;
}

int textBox::getLDis() {

	return lineDis;
}

int textBox::getWDis() {

	 return wordDis;
}

int textBox::getHeight() {

	return height;
}

int textBox::getWidth() {

	return width;
}

bool textBox::getAutoSwi() {

	return autoSwitch;
}

void textBox::setLDis(int LD) {

	this->lineDis = LD;
}

void textBox::setAutoSwi(bool AW) {

	this->autoSwitch = AW;
}

void textBox::setWDis(int WD) {

	this->wordDis = WD;
}