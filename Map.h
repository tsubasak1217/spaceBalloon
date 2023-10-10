#pragma once
#include <Vector2.h>
#include <Novice.h>
#include "MyFunc.h"
#include "GlobalVariable.h"

class Map{

private:
	//縦横の配列数
	static const int mapRow = 240;
	static const int mapCol = 40;
	
	//座標
	Vector2 pos_[mapRow][mapCol];
	std::vector<Vector2>birdPos_;
	std::vector<Vector2>birdAddress_;
	std::vector<int>birdDirection_;

	//縦横の幅
	Vector2 size_;
	float miniMapSize;

	//ブロックの種類を番号で示す(マップチップ)
	std::vector<std::vector<int>>blockType_;

	bool isTimeStop_;
	int stopLimit_;

public:
	//イニシャライズ
	void Init();

	//アクセッサ
	int GetBlockType(int row, int col) { return blockType_[row][col]; }
	void SetBlockType(int row, int col,int blockType) { blockType_[row][col] = blockType; }

	Vector2 GetPos(int row, int col){ return pos_[row][col]; }
	std::vector<Vector2>GetBirdPos() { return birdPos_; }
	std::vector<Vector2>GetBirdAddress() { return birdAddress_; }

	Vector2 GetSize() { return size_; }

	bool GetIsTimeStop() { return isTimeStop_; }
	void SetIsTimeStop(bool flag) { isTimeStop_ = flag; }

	int GetStopLimit() { return stopLimit_; }
	void SetStopLimit(int value) { stopLimit_ = value; }

	//アップデート
	void Update();

	//ドロー
	void Draw(GlobalVariable globalV);

	enum Direction {
		Up,
		Right,
		Down,
		Left
	};
};

