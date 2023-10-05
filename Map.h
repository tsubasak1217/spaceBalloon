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
	 
public:
	//イニシャライズ
	void Init();

	//アクセッサ
	int GetBlockType(int row, int col) { return blockType_[row][col]; }
	void SetBlockType(int row, int col,int blockType) { blockType_[row][col] = blockType; }

	//ドロー
	void Draw(GlobalVariable globalV);
};

