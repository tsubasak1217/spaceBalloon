#pragma once
#include "Map.h"
#include "Color.hpp"

class Player {

private:

	//座標、大きさ
	Vector2 pos_;
	Vector2 size_;

	//復活座標
	Vector2 respawnPos_;

	//風船の膨張レベル
	float balloonLevel_;

	//移動系
	float gravity_;
	float airResistance_;
	float weight_;
	float volume_;

	float speed_;
	Vector2 windSpeed_;
	Vector2 velocity_;
	Vector2 acceleration_;

	//加速系
	bool isAccelable_;
	bool isCountStart_;
	int doublePushLimit_;
	bool isDash_;
	int dashDirection_;
	int dashLimit_;

	//プレイヤーの番地
	Vector2Int address_;

	//プレイヤーの残機など
	int life_;
	bool isAlive_;
	bool isUnrivaled_;//無敵状態かどうか
	int unrivaledLimit_;
	int holdLimit_;

	//色
	int color_;

	//イージング用変数
	float easeT_;
	float windT_;

	//ノックバックの時間変数
	int knockBackCount_;

	//ブロックと当たった方向を格納する変数
	int hitDirection_;
	int preHitDirection_;

	//スコア変数
	int scoreCount_;
	int savedScoreCount_;

	//リトライの待ち時間
	int retryTimeCount_;

	//===================ロープ=======================
	Vector2 ropePos_[32];
	float ropeLength_;


	//===================死亡エフェクト=======================
	Vector2 savePos_;
	Vector2 triangleCenter_[24];
	float efectRadius_;
	float triangleTheta_[24];
	float triangleEaseT_;

public:

	//イニシャライズ(初期化関数)
	void Init(int sceneNum,Map map) {

		life_ = 1;
		isAlive_ = true;
		isUnrivaled_ = false;
		unrivaledLimit_ = 0;
		holdLimit_ = 300;

		balloonLevel_ = 0.0f;
		size_ = { 5.0f + (balloonLevel_ * 2.0f),5.0f + (balloonLevel_ * 2.0f) };
		address_ = { int(pos_.x) / 64,int(pos_.y) / 64 };
		ropeLength_ = 8.0f;

		gravity_ = -0.8f;
		weight_ = 0.0f;
		volume_ = 1;
		airResistance_ = 0.5f;

		speed_ = 4.0f;
		windSpeed_ = { 0.0f,0.0f };
		velocity_ = { 0.0f,0.0f };
		acceleration_ = { 0.0f,0.0f };
		easeT_ = 0.0f;
		windT_ = 0.0f;
		knockBackCount_ = 0;

		hitDirection_ = 0;
		preHitDirection_ = 0;

		isAccelable_ = false;
		isCountStart_ = false;
		doublePushLimit_ = 16;
		isDash_ = false;
		dashDirection_ = 0;
		dashLimit_ = 300;

		retryTimeCount_ = 100;

		color_ = 0xff5181ff;

		savePos_ = { 0.0f,0.0f };
		efectRadius_ = 240.0f;
		triangleEaseT_ = 0.0f;

		for (int i = 0; i < 24; i++) {
			triangleTheta_[i] = 0.0f;
			triangleCenter_[i] = {0.0f,0.0f};
		}

		switch (sceneNum) {
			//=====================================================================================
			//                                      タイトル
			//=====================================================================================
		case titleScene:

			pos_ = { 640.0f,340.0f + size_.y };
			respawnPos_ = pos_;

			ropePos_[0] = { pos_.x,pos_.y - size_.y };
			for (int i = 1; i < 32; i++) {

				ropePos_[i].x = ropePos_[i - 1].x;
				ropePos_[i].y = ropePos_[i - 1].y - ropeLength_;
				ropePos_[i] = { pos_.x,pos_.y - size_.y };
			}

			scoreCount_ = 0;
			savedScoreCount_ = 0;

			break;

			//=====================================================================================
			//                                     ゲーム本編
			//=====================================================================================
		case game:

			pos_ = map.GetFirstPlayerPos();
			respawnPos_ = pos_;

			ropePos_[0] = { pos_.x,pos_.y - size_.y };
			for (int i = 1; i < 32; i++) {

				ropePos_[i].x = ropePos_[i - 1].x;
				ropePos_[i].y = ropePos_[i - 1].y - ropeLength_;
			}


			break;

			//=====================================================================================
			//                                     クリア画面
			//=====================================================================================
		case clear:

			//pos_ = { 640.0f,320.0f + size_.y };
			//respawnPos_ = pos_;

			break;

		default:
			break;
		}
	}

	//アクセッサ
	Vector2 GetPos() { return pos_; }
	void SetPos(Vector2 pos) { pos_ = pos; }

	Vector2 GetSize() { return size_; }
	void SetSize(Vector2 size) { size_ = size; }

	float GetBalloonLevel() { return balloonLevel_; }
	void SetBalloonLevel(float ballonLevel) { balloonLevel_ = ballonLevel; }

	Vector2 GetVelocity() { return velocity_; }

	int GetLife() { return life_; }
	void SetLife(int life) { life_ = life; }

	int GetAlive() { return isAlive_; }
	void SetAlive(bool flag) { isAlive_ = flag; }

	bool GetIsUnrivaled() { return isUnrivaled_; }
	void SetIsUnrivaled(bool flag) { isUnrivaled_ = flag; }

	int GetUnrivaledLimit() { return unrivaledLimit_; }
	void SetUnrivaledLimit(int value) { unrivaledLimit_ = value; }



	// アップデート
	void Update(
		char* keys, char* preKeys,
		int* cameraPosX, int* cameraPosY, int* miniCameraPos,
		Map& map, Scene scene, ChangeScene& changeScene,
		GlobalVariable globalV
	);

	//ドロー
	void Draw(GlobalVariable globalV, Scene scene, ChangeScene changeScene);
	void DrawTutorial(GlobalVariable globalV);
	void Sound(char* keys, char* preKeys, Scene scene, Map map);

	//画像
	int playerImg[2] = {
		Novice::LoadTexture("./Resources./Images./game./tutorial.png"),
		Novice::LoadTexture("./Resources./Images./game./tutorial2.png"),
	};

	//音
	int playerSE[13] = {
		Novice::LoadAudio("./Resources./Sounds./up.mp3"),
		Novice::LoadAudio("./Resources./Sounds./bound.mp3"),
		Novice::LoadAudio("./Resources./Sounds./1up.mp3"),
		Novice::LoadAudio("./Resources./Sounds./star_get.mp3"),
		Novice::LoadAudio("./Resources./Sounds./brow.mp3"),
		Novice::LoadAudio("./Resources./Sounds./thunder1.mp3"),
		Novice::LoadAudio("./Resources./Sounds./accelCharge.mp3"),
		Novice::LoadAudio("./Resources./Sounds./thunder2.mp3"),
		Novice::LoadAudio("./Resources./Sounds./pan!.mp3"),
		Novice::LoadAudio("./Resources./Sounds./clock.mp3"),
		Novice::LoadAudio("./Resources./Sounds./wing.mp3"),
		Novice::LoadAudio("./Resources./Sounds./birdVoice.mp3"),
		Novice::LoadAudio("./Resources./Sounds./savePoint.mp3"),
	};

	int SEHandle[13] = {0};

	float volume[13] = { 0.0f };
};