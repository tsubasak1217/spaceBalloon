#pragma once
#include <Novice.h>
#include "Easing.h"
#include "MyFunc.h"
#include "GlobalVariable.h"


class Scene{

private:
	int sceneNum_;

public:
	//イニシャライズ
	void Init(){
		sceneNum_ = clear;
	}

	//アクセッサ
	int GetSceneNum() { return sceneNum_; }
	void SetSceneNum(int scene) { sceneNum_ = scene; }
};


