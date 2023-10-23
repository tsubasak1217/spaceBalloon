#include "MyFunc.h"

//csvを読み込む関数
std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath) {
	//値を入れる配列
	std::vector<std::vector<int>> intArray;
	//ファイル
	std::ifstream file(csvFilePath);
	//ファイルの数値を入れる変数
	std::string line, value;

	//ファイルから読み取った1行をlineに格納
	while (std::getline(file, line)) {
		std::vector<int> row;
		//1行ごとの文字を入れる
		std::istringstream issLine(line);
		std::istringstream issValue(value);

		//issからカンマ区切りでデータを読み込みvalueに格納
		while (std::getline(issLine, value, ',')) {
			// int型に変換
			int intValue = atoi(value.c_str());
			issValue >> value;
			//行に値を入れる
			row.push_back(intValue);
		}

		//行の値を配列に入れる
		intArray.push_back(row);
	}

	return intArray;
}

//何もしない関数
void Void() { ; }

//フレーム数を時計に変換する関数
int FrameToClock(int count, int tranceMode) {

	int result = 0;
	enum TranceMode {
		Sec,
		Min,
		Hour
	};

	switch (tranceMode) {
	case Sec:
		result = count / 60;
		break;

	case Min:
		result = (count / 60)/60;
		break;

	case Hour:
		result = ((count / 60) / 60)/60;
		break;

	default:
		break;
	}

	return result;

};

float CheckLength(Vector2 pos1, Vector2 pos2) {
	float xLength = (pos1.x - pos2.x);
	float yLength = (pos1.y - pos2.y);
	return sqrtf(xLength * xLength + yLength * yLength);
}

float CheckLength(float pos1x, float pos1y, float pos2x, float pos2y) {
	float xLength = pos2x - pos1x;
	float yLength = pos2y - pos1y;
	return sqrtf(xLength * xLength + yLength * yLength);
}

float Cross(
	float lineStartX, float lineStartY,
	float lineEndX, float lineEndY,
	float targetX, float targetY
) {
	float lineLengthX = lineEndX - lineStartX;
	float lineLengthY = lineEndY - lineStartY;
	float lineLength = sqrtf(lineLengthX * lineLengthX + lineLengthY * lineLengthY);

	float line2TargetX = targetX - lineStartX;
	float line2TargetY = targetY - lineStartY;

	return ((lineLengthX * line2TargetY) - (lineLengthY * line2TargetX)) / lineLength;
}

float CrossV(Vector2 pos1, Vector2 pos2, Vector2 targetPos) {
	Vector2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	float lineLength = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
	Vector2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return ((lineVector.x * forTarget.y) - (lineVector.y * forTarget.x)) / lineLength;
}

Vector2 CrossPos(Vector2 line1Pos1, Vector2 line1Pos2, Vector2 line2Pos1, Vector2 line2Pos2) {
	float s1 =
		((line2Pos2.x - line2Pos1.x) * (line1Pos1.y - line2Pos1.y) -
			(line2Pos2.y - line2Pos1.y) * (line1Pos1.x - line2Pos1.x)) / 2.0f;

	float s2 =
		((line2Pos2.x - line2Pos1.x) * (line2Pos1.y - line1Pos2.y) -
			(line2Pos2.y - line2Pos1.y) * (line2Pos1.x - line1Pos2.x)) / 2.0f;

	Vector2 crossPos = {
		line1Pos1.x + (line1Pos2.x - line1Pos1.x) * s1 / (s1 + s2),
		line1Pos1.y + (line1Pos2.y - line1Pos1.y) * s1 / (s1 + s2)
	};

	return crossPos;
}

Vector2 ShiftLine(Vector2 pos1, Vector2 pos2, float distance) {

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float length = sqrtf(dx * dx + dy * dy);
	float normalizedX = dx / length;
	float normalizedY = dy / length;

	return{
	normalizedY * distance,
	-normalizedX * distance
	};
}

//================================================================
//                        行列関数
//================================================================

//加算
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
};

//減算
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
};

//乗算
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {

			result.m[i][j] =
				(matrix1.m[i][0] * +matrix2.m[0][j]) +
				(matrix1.m[i][1] * +matrix2.m[1][j]);
		}
	}

	return result;
};

//ベクトルとの乗算
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {

	return {
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1]
	};
};

//================================================================
//                        行列の表示の関数
//================================================================
void MatrixScreenPrintf(int posX, int posY, Matrix2x2 matrix) {

	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {

			Novice::ScreenPrintf(
				posX + col * 64,
				posY + row * 20,
				"%.02f",
				matrix.m[row][col]
			);
		}
	}
};
void Vector2ScreenPrintf(int posX, int posY, Vector2 vector) {

	Novice::ScreenPrintf(posX, posY, "%.02f", vector.x);
	Novice::ScreenPrintf(posX + 64, posY, "%.02f", vector.y);
};

//浮力を考慮した加速度を計算
float CalcSinkSpeed(float objectWeight, float spaceWeight, float gravity) {

	return gravity - (spaceWeight / objectWeight) * gravity;
}

bool IsHitBox_Ball(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius) {

	float distX = ballPos.x - boxCenter.x;
	float distY = ballPos.y - boxCenter.y;

	if (distX >= -boxSize.x / 2.0f && distX <= boxSize.x / 2.0f) {

		if (distY >= (-boxSize.y / 2.0f) - ballRasius && distY <= (boxSize.y / 2.0f) + ballRasius) {

			return true;

		} else {
			return false;
		}

	} else if (distY >= -boxSize.y / 2.0f && distY <= boxSize.y / 2.0f) {

		if (distX >= (-boxSize.x / 2.0f) - ballRasius && distX <= (boxSize.x / 2.0f) + ballRasius) {
			return true;

		} else {
			return false;
		}

	} else {

		if (distX < 0 && distY < 0) {
			if (
				CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}
		} else if (distX >= 0 && distY < 0) {
			if (
				CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}

		} else if (distX < 0 && distY >= 0) {
			if (
				CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}

		} else {
			if (
				CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}
		}
	}
}

int IsHitBox_BallDirection(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius) {

	float distX = ballPos.x - boxCenter.x;
	float distY = ballPos.y - boxCenter.y;

	if (distX >= -boxSize.x / 2.0f && distX <= boxSize.x / 2.0f) {

		if (distY >= (-boxSize.y / 2.0f) - ballRasius && distY <= (boxSize.y / 2.0f) + ballRasius) {

			if (distY >= 0) {
				return 1;//上面に当たった
			} else {
				return 3;//下面に当たった
			}

		} else {
			return false;
		}

	} else if (distY >= -boxSize.y / 2.0f && distY <= boxSize.y / 2.0f) {

		if (distX >= (-boxSize.x / 2.0f) - ballRasius && distX <= (boxSize.x / 2.0f) + ballRasius) {

			if (distX >= 0) {
				return 2;//右面に当たった
			} else {
				return 4;//左面に当たった
			}

		} else {
			return false;
		}

	} else {

		if (distX < 0 && distY >= 0) {//左上
			if (CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 1;//上面に当たった
				} else {
					return 4;//左面に当たった
				}

			} else {
				return false;
			}
		} else if (distX >= 0 && distY >= 0) {//右上
			if (CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 1;//上面に当たった
				} else {
					return 2;//右面に当たった
				}

			} else {
				return false;
			}

		} else if (distX < 0 && distY < 0) {//左下
			if (CheckLength(boxCenter.x - boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 3;//上面に当たった
				} else {
					return 4;//左面に当たった
				}

			} else {
				return false;
			}

		} else {//右下
			if (CheckLength(boxCenter.x + boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if (sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 3;//上面に当たった
				} else {
					return 2;//左面に当たった
				}

			} else {
				return false;
			}
		}
	}
}

bool CheckBalloonLimit(int hitDirection, int preHitDirection) {
	if (!((preHitDirection == 1 && hitDirection == 3) or (preHitDirection == 3 && hitDirection == 1)) &&
		!((preHitDirection == 2 && hitDirection == 4) or (preHitDirection == 4 && hitDirection == 2))) {
		return false;
	} else {
		return true;
	}
};

int Red(int color) { return (color >> 24) & 0xFF; }
int Green(int color) { return (color >> 16) & 0xFF; }
int Blue(int color) { return (color >> 8) & 0xFF; }
int Alpha(int color) { return color & 0xFF; }

int ChangeColor(int startColor, int aimColor, float divideNum, float rate) {

	//二色の差を求める
	int difRed = Red(aimColor) - Red(startColor);
	int difGreen = Green(aimColor) - Green(startColor);
	int difBlue = Blue(aimColor) - Blue(startColor);
	int difAlpha = Alpha(aimColor) - Alpha(startColor);

	//差分を任意の値で割る
	float dividedRed = float(difRed) / divideNum;
	float dividedGreen = float(difGreen) / divideNum;
	float dividedBlue = float(difBlue) / divideNum;
	float dividedAlpha = float(difAlpha) / divideNum;

	//割った値をrate倍する
	int Red = int(dividedRed * rate) << 24;
	int Green = int(dividedGreen * rate) << 16;
	int Blue = int(dividedBlue * rate) << 8;
	int Alpha = int(dividedAlpha * rate);

	//色を足して返す
	return startColor + Red + Green + Blue + Alpha;
}

int GrayScale(int color) {

	int Red = (color >> 24) & 0xFF;
	int Green = (color >> 16) & 0xFF;
	int Blue = (color >> 8) & 0xFF;

	int trancedRed = int(float(Red) * 0.2126f);
	int trancedGreen = int(float(Green) * 0.7152f);
	int trancedBlue = int(float(Blue) * 0.0722f);

	int gray = int(trancedRed + trancedGreen + trancedBlue);

	return 0xFF + (gray << 24) + (gray << 16) + (gray << 8);
}

//================================================================--
//                            星を描く
//================================================================--

void DrawStar(Vector2 center, float radius, float theta, int color) {

	Vector2 vertex[5];
	Vector2 preVertex[5];
	Vector2 crossPos[3];

	//初期座標
	for (int i = 0; i < 5; i++) {

		vertex[i].x = center.x + radius * cosf(((((2.0f / 5.0f) * i) - (1.0f / 2.0f)) * float(M_PI)));
		vertex[i].y = center.y + radius * sinf(((((2.0f / 5.0f) * i) - (1.0f / 2.0f)) * float(M_PI)));
	}

	crossPos[0] = CrossPos(vertex[2], vertex[4], vertex[3], vertex[0]);
	crossPos[1] = CrossPos(vertex[3], vertex[0], vertex[4], vertex[1]);
	crossPos[2] = CrossPos(vertex[4], vertex[1], vertex[0], vertex[2]);

	//回転
	for (int i = 0; i < 5; i++) {

		preVertex[i] = vertex[i];

		preVertex[i].x -= center.x;
		preVertex[i].y -= center.y;

		vertex[i].x = preVertex[i].x * cosf(theta) - preVertex[i].y * sinf(theta);
		vertex[i].y = preVertex[i].x * sinf(theta) + preVertex[i].y * cosf(theta);

		vertex[i].x += center.x;
		vertex[i].y += center.y;
	}

	crossPos[0] = CrossPos(vertex[2], vertex[4], vertex[3], vertex[0]);
	crossPos[1] = CrossPos(vertex[3], vertex[0], vertex[4], vertex[1]);
	crossPos[2] = CrossPos(vertex[4], vertex[1], vertex[0], vertex[2]);

	//描画
	for (int i = 0; i < 3; i++) {
		Novice::DrawTriangle(
			int(vertex[i].x),
			int(vertex[i].y),
			int(vertex[i + 2].x),
			int(vertex[i + 2].y),
			int(crossPos[i].x),
			int(crossPos[i].y),
			color,
			kFillModeSolid
		);
	}

};

//中心点を基準に三角形を描く関数
void DrawTriangle(Vector2 center, float radius, float theta, int color) {

	Vector2 vertex[3];
	Vector2 preVertex[3];

	//初期座標
	for (int i = 0; i < 3; i++) {
		vertex[i].x = center.x + cosf((-(1.0f / 2.0f) + (i * (2.0f / 3.0f))) * float(M_PI)) * radius;
		vertex[i].y = center.y + sinf((-(1.0f / 2.0f) + (i * (2.0f / 3.0f))) * float(M_PI)) * radius;
	}

	//回転
	for (int i = 0; i < 3; i++) {

		preVertex[i] = vertex[i];

		preVertex[i].x -= center.x;
		preVertex[i].y -= center.y;

		vertex[i].x = preVertex[i].x * cosf(theta) - preVertex[i].y * sinf(theta);
		vertex[i].y = preVertex[i].x * sinf(theta) + preVertex[i].y * cosf(theta);

		vertex[i].x += center.x;
		vertex[i].y += center.y;
	}

	//描画
	Novice::DrawTriangle(
		int(vertex[0].x),
		int(vertex[0].y),
		int(vertex[1].x),
		int(vertex[1].y),
		int(vertex[2].x),
		int(vertex[2].y),
		color,
		kFillModeSolid
	);

};