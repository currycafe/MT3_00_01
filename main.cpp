#include <Novice.h>
#include<math.h>

const char kWindowTitle[] = "GC2A_11_シラトリナオヤ_タイトル";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;


struct Vector3 {
	float x;
	float y;
	float z;
};
struct Scalar {
	float k;
};


Vector3 Add(Vector3 v1, Vector3 v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(Vector3 v1, Vector3 v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
Vector3 Multiply(Vector3 v1, Scalar S) {
	Vector3 result;
	result.x = v1.x * S.k;
	result.y = v1.y * S.k;
	result.z = v1.z * S.k;
	return result;
}

float Dot(Vector3 v1, Vector3 v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

float Length(Vector3 v1) {
	float result;
	result = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return result;
}

Vector3 Normalize(Vector3 v2) {
	Vector3 result;
	result.x = v2.x / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	result.y = v2.y / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	result.z = v2.z / sqrtf(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	return result;
}


void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);

}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();


		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector3 v1 = { 1.0f,3.0f,-5.0f };
		Vector3 v2 = { 4.0f,-1.0f,2.0f };
		Scalar k = { 4.0f };


		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSubtract = Subtract(v1, v2);
		Vector3 resultMultiply = Multiply(v1, k);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, kRowHeight * 0, resultAdd, "   :Add");
		VectorScreenPrintf(0, kRowHeight * 1, resultSubtract, "   :Subtract");
		VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, "   :Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.2f  :Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.2f  :Length", resultLength);
		VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, "   :Normalize");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
