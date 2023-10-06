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

	//縦横の幅
	Vector2 size_;
	
	//ブロックの種類を番号で示す(マップチップ)
	int blockType_[mapRow][mapCol];
	std::vector<std::vector<int>>blockCsv;

	enum BlockType {
		normal = 1,
		wind_up = 2,
		wind_right = 3,
		wind_down = 4,
		wind_left = 5,
		bird = 6,
		birdArea = 66,
		thunder = 7
	};
	 
public:
	//イニシャライズ
	void Init();

	//アクセッサ
	int GetBlockType(int row, int col) { return blockType_[row][col]; }
	void SetBlockType(int row, int col,int blockType) { blockType_[row][col] = blockType; }

	Vector2 GetPos(int row, int col){ return pos_[row][col]; }

	Vector2 GetSize() { return size_; }

	//ドロー
	void Draw(GlobalVariable globalV);
};

