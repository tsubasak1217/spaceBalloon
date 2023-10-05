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
		std::istringstream iss(line);
		//issからカンマ区切りでデータを読み込みvalueに格納
		while (std::getline(iss, value, ',')) {
			// int型に変換
			int intValue = std::stoi(value);
			//行に値を入れる
			row.push_back(intValue);
		}

		//行の値を配列に入れる
		intArray.push_back(row);
	}

	return intArray;
}



float CheckLength(Vector2 pos1, Vector2 pos2) {
	float xLength = (pos1.x - pos2.x);
	float yLength = (pos1.y - pos2.y);
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

