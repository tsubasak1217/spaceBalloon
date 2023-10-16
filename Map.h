#pragma once
#include <Vector2.h>
#include <Novice.h>
#include "ChangeScene.h"
#include "MyFunc.h"

class Map {

private:

	//
	float theta_;
	int titleTimeCount_;

	//タイトルのオブジェクト
	Vector2 cloudPos_[2];

	//タイトルロゴ
	Vector2 titleLogoPos_[2];

	//縦横の配列数
	static const int mapRow = 240;
	static const int mapCol = 40;

	//座標
	Vector2 pos_[mapRow][mapCol];
	std::vector<Vector2>birdPos_;
	std::vector<Vector2Int>birdAddress_;
	std::vector<int>birdDirection_;

	//縦横の幅
	Vector2 size_;
	float miniMapSize;

	//ブロックの種類を番号で示す(マップチップ)
	std::vector<std::vector<int>>blockType_;
	std::vector<std::vector<int>>savedBlockType_;

	//プレイヤーからのブロック保存命令を受け取るフラグ
	bool saveBlockOrder_;

	//プレイヤーからのブロック復元命令を受け取るフラグ
	bool resetBlockOrder_;

	//
	bool isTimeStop_;
	int stopLimit_;

	unsigned int skyColor_;

public:
	//イニシャライズ
	void Init();

	//アクセッサ
	int GetBlockType(int row, int col) { return blockType_[row][col]; }
	void SetBlockType(int row, int col, int blockType) { blockType_[row][col] = blockType; }

	int GetSavedBlockType(int row, int col) { return savedBlockType_[row][col]; }
	void SetSavedBlockType(int row, int col, int savedBlockType) { savedBlockType_[row][col] = savedBlockType; }

	Vector2 GetPos(int row, int col) { return pos_[row][col]; }
	std::vector<Vector2>GetBirdPos() { return birdPos_; }
	std::vector<Vector2Int>GetBirdAddress() { return birdAddress_; }

	Vector2 GetSize() { return size_; }

	bool GetIsTimeStop() { return isTimeStop_; }
	void SetIsTimeStop(bool flag) { isTimeStop_ = flag; }

	int GetStopLimit() { return stopLimit_; }
	void SetStopLimit(int value) { stopLimit_ = value; }

	unsigned int GetSkyColor() { return skyColor_; }
	void SetSkyColor(unsigned int color) { skyColor_ = color; }

	void SetSaveBlockOrder(bool flag) { saveBlockOrder_ = flag; }
	void SetResetBlockOrder(bool flag) { resetBlockOrder_ = flag; }

	//アップデート
	void Update(Scene scene);

	//ドロー
	void Draw(GlobalVariable globalV, Scene scene,ChangeScene changeScene);

	enum Direction {
		Up,
		Right,
		Down,
		Left
	};

	int titleImgs_[6] = {
	Novice::LoadTexture("./Resources./Images./title./bg_sky.png"),
	Novice::LoadTexture("./Resources./Images./title./cloud1.png"),
	Novice::LoadTexture("./Resources./Images./title./cloud2.png"),
	Novice::LoadTexture("./Resources./Images./title./space.png"),
	Novice::LoadTexture("./Resources./Images./title./balloon.png"),
	Novice::LoadTexture("./Resources./Images./title./rope.png"),
	};

};

