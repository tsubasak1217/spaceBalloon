#pragma once
#include "GlobalVariable.h"

class Scene{

private:
	int sceneNum_;

public:
	//イニシャライズ
	void Init(){
		sceneNum_ = title;
	}

	//アクセッサ
	int GetSceneNum() { return sceneNum_; }
	void SetSceneNum(int scene) { sceneNum_ = scene; }
};

