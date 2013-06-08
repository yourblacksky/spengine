#pragma once

class textBox {

private:
	int height;
	int width;
	int lineDis;
	int wordDis;
	bool autoSwitch;

public:
	textBox();
	textBox(int LD, int WD, int H, int W, bool AW);
	int getLDis();
	int getWDis();
	int getHeight();
	int getWidth();
	bool getAutoSwi();
	void setAutoSwi(bool AW);
	void setLDis(int LD);
	void setWDis(int WD);
};