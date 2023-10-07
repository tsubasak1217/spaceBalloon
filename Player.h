#pragma once
#include "Map.h"

class Player{

private:

	//座標、大きさ
	Vector2 pos_;
	Vector2 size_;
	
	//風船の膨張レベル
	float balloonLevel_ ;

	//移動系
	float gravity_;
	float airResistance_;
	float weight_;
	float volume_;

	float speed_;
	Vector2 windSpeed_;
	Vector2 velocity_;
	Vector2 acceleration_;

	//プレイヤーの番地
	Vector2Int address_;

	//色
	int color_;

	//イージング用変数
	float easeT_;
	float windT_;

	//ノックバックの時間変数
	int knockBackCount_;

	//ブロックと当たったかのフラグ
	int hitDirection_;
	int preHitDirection_;


public:

	//イニシャライズ(初期化関数)
	void Init() {
		
		balloonLevel_ = 0.0f;
		size_ = { 5.0f + (balloonLevel_ * 2.0f),5.0f + (balloonLevel_ * 2.0f) };
		pos_ = { 640.0f,size_.y };

		gravity_ = -0.8f;
		weight_ = 0.0f;
		volume_ = 1;
		airResistance_ = 0.5f;

		speed_ = 4.0f;
		windSpeed_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		acceleration_ = { 0.0f,0.0f };

		color_ = 0xff5181ff;

		easeT_ = 0.0f;
		windT_ = 0.0f;
		knockBackCount_ = 0;

		address_ = { int(pos_.x) / 64,int(pos_.y) / 64 };

		hitDirection_ = 0;
		preHitDirection_ = 0;
	}

	//アクセッサ
	Vector2 GetPos() { return pos_; }
	void SetPos(Vector2 pos) { pos_ = pos; }

	Vector2 GetSize() { return size_; }
	void SetSize(Vector2 size) { size_ = size; }

	float GetBalloonLevel() { return balloonLevel_; }
	void SetBalloonLevel(float ballonLevel) { balloonLevel_ = ballonLevel; }


	// アップデート
	void Update(char* keys, char* preKeys, int* cameraPosX,int* cameraPosY, int* miniCameraPos, Map map);

	//ドロー
	void Draw(GlobalVariable globalV);
};