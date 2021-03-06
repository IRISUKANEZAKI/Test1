#include"Dxlib.h"

// 定数の定義
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

// ﾌﾟﾚｲﾔｰ
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32

// 弾
#define SHOT_SIZE_X 32
#define SHOT_SIZE_Y 32

// 敵
#define ENEMY_SIZE_X 64
#define ENEMY_SIZE_Y 64

// 爆発
#define BLAST_ANI 24
#define BLAST_SIZE_X 96
#define BLAST_SIZE_Y 96

// 背景
#define BG_SIZE_Y 960

// 変数の定義
// ﾌﾟﾚｲﾔｰ
int playerImage;
int playerPosX;
int playerPosY;
int playerSpeed;
bool playerFlag;

// 弾
int shotImage;
int shotPosX[3];
int shotPosY[3];
int shotFlag[3];
int shotSpeed;

// 敵
int enemyImage;
int enemyPosX;
int enemyPosY;
int enemySpeed;
bool enemyFlag;

// 背景
int bgImage;
int bgPosX;
int bgPosY;

// 爆発
int blastImage[BLAST_ANI];
int blastAni;
bool blastFlag;
int blastPosX;
int blastPosY;

// WinMain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ------------- ｼｽﾃﾑ処理
	SetWindowText("1916208_金崎依里朱");
	// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	// 640×480ﾄﾞｯﾄ65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);							// true:window false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1) return -1;				// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);					// ひとまずﾊﾞｯｸバッファに描画

	// ｸﾞﾗﾌｨｯｸの登録
	playerImage = LoadGraph("image/player.png");
	shotImage = LoadGraph("image/shot.png");
	enemyImage = LoadGraph("image/enemy.png");
	bgImage = LoadGraph("image/haikei.png");
//	blastImage = LoadGraph("image/blast.png");
	LoadDivGraph("image/blast.png", 24, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImage);

	// 変数の初期化
	playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X)/2;
	playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
	playerSpeed = 4;
	playerFlag = true;

	shotPosX[0] = 640;
	shotPosY[0] = 0;
	shotSpeed = 15;
	shotFlag[0] = false;		// 弾を撃ったら　true
	shotPosX[1] = 0;
	shotPosY[1] = 0;
	shotFlag[1] = false;
	shotPosX[2] = 0;
	shotPosY[2] = 0;
	shotFlag[2] = false;

	enemyPosX = (SCREEN_SIZE_X - ENEMY_SIZE_X)/2;
	enemyPosY = (SCREEN_SIZE_Y - ENEMY_SIZE_Y)/2;
	enemySpeed = 2;
	enemyFlag = true;
	
	bgPosY = 0;

	blastAni = 0;
	blastPosX = 0;
	blastPosY = 0;
	blastFlag = false;
	
	

	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// ﾒｲﾝ処理

		// キー操作
		// ｽﾋﾟｰﾄﾞを変える
		if (CheckHitKey(KEY_INPUT_ADD) == 1)			// +keyを押すとｽﾋﾟｰﾄﾞが上がる
		{
			playerSpeed = playerSpeed + 1;
		}
		if (CheckHitKey(KEY_INPUT_SUBTRACT) == 1)		// -keyを押すとｽﾋﾟｰﾄﾞが下がる
		{
			playerSpeed = playerSpeed - 1;
			if (playerSpeed < 1)
			{
				playerSpeed = 1;
			}
		}

		// *爆発させる
		if (CheckHitKey(KEY_INPUT_MULTIPLY) == 1)	// *キーで爆発させる
		{
			blastFlag = true;
		}

		// 敵を再表示させる
		if (CheckHitKey(KEY_INPUT_DIVIDE) == 1)		// /キーで敵を再表示する
		{
			enemyPosX = GetRand(SCREEN_SIZE_X - ENEMY_SIZE_X);
			enemyPosY = GetRand(100);
			enemyFlag = true;

		}

		// 2486 移動させる
		if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1)		// 右移動
		{
			if (playerPosX < SCREEN_SIZE_X - PLAYER_SIZE_X)
			{
				playerPosX = playerPosX + playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1)		// 左移動
		{
			if (playerPosX > 0)
			{
				playerPosX = playerPosX - playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD8) == 1)		// 上移動
		{
			if (playerPosY > 0)
			{
				playerPosY = playerPosY - playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD2) == 1)		// 下移動
		{
			if (playerPosY < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPosY = playerPosY + playerSpeed;
			}
		}

		// 敵の移動
		enemyPosY = enemyPosY + enemySpeed;
		if (enemyPosY > SCREEN_SIZE_Y)
		{
			enemyPosY = -ENEMY_SIZE_Y;
		}
		
		// 弾の発射
		if (shotFlag[0] == true)
		{
			shotPosY[0] = shotPosY[0] - shotSpeed;
			if (shotPosY[0] < -SHOT_SIZE_Y)		// 弾が画面外に出たときにfalseにする
			{
				shotFlag[0] = false;
			}
		}
		else
		{
			if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
			{
				shotFlag[0] = true;
				shotPosX[0] = playerPosX;
				shotPosY[0] = playerPosY;
			}
		}

		// 3WEY弾の発射
		if (shotFlag[0] == true
			&& shotFlag[1] == true
			&& shotFlag[2] == true)
		{
			shotPosY[0] -= shotSpeed;
			shotPosX[1] -= shotSpeed;
			shotPosY[1] -= shotSpeed;
			shotPosX[2] += shotSpeed;
			shotPosY[2] -= shotSpeed;
			if (shotPosY[0] < -SHOT_SIZE_Y)
			{
				shotFlag[0] = false;
				shotFlag[1] = false;
				shotFlag[2] = false;
			}
		}
		else
		{
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				shotFlag[0] = true;
				shotPosX[0] = playerPosX;
				shotPosY[0] = playerPosY;
				shotFlag[1] = true;
				shotPosX[1] = playerPosX;
				shotPosY[1] = playerPosY;
				shotFlag[2] = true;
				shotPosX[2] = playerPosX;
				shotPosY[2] = playerPosY;		
			}
		}

		// 当たり判定
		// 点と敵
		//		if (enemyPosX <= shotPosX
		//			&& shotPosX <= enemyPosX + ENEMY_SIZE_X
		//			&& enemyPosY <= shotPosY
		//			&& shotPosY <= enemyPosY + ENEMY_SIZE_Y)
		//		{
		//			enemyFlag = false;
		//		}

		// 自機と敵
		if (playerFlag == true
			&& enemyFlag == true)
		{
			if (enemyPosY + ENEMY_SIZE_Y >= playerPosY
				&& enemyPosY <= playerPosY + PLAYER_SIZE_Y
				&& enemyPosX <= playerPosX + PLAYER_SIZE_X
				&& enemyPosX + ENEMY_SIZE_X >= playerPosX)
			{
				blastFlag = true;
				blastPosX = (playerPosX - (BLAST_SIZE_X - PLAYER_SIZE_X) / 2);
				blastPosY = (playerPosY - (BLAST_SIZE_Y - PLAYER_SIZE_Y) / 2);
				DrawBox(enemyPosX, enemyPosY, enemyPosX + ENEMY_SIZE_X, enemyPosY + ENEMY_SIZE_Y, 0x00ffff, true);
				playerFlag = false;
			}
		}

		// 弾と敵
		if (shotFlag[0] == true
			&& enemyFlag == true
			&& playerFlag == true)
		{
			if (enemyPosY + ENEMY_SIZE_Y >= shotPosY[0]
				&& enemyPosY <= shotPosY[0] + SHOT_SIZE_Y
				&& enemyPosX <= shotPosX[0] + SHOT_SIZE_X
				&& enemyPosX + ENEMY_SIZE_X >= shotPosX[0])
			{
				enemyFlag = false;
				shotFlag[0] = false;
				blastFlag = true;
				blastPosX = (enemyPosX - (BLAST_SIZE_X - ENEMY_SIZE_X) / 2);
				blastPosY = (enemyPosY - (BLAST_SIZE_Y - ENEMY_SIZE_Y) / 2);
			}
		}

		// 敵を倒したら再表示
		if (enemyFlag == false)
		{
			enemyPosX = GetRand(SCREEN_SIZE_X - ENEMY_SIZE_X);
			enemyPosY = GetRand(100);
			enemyFlag = true;
		}

		// 自機が倒されたら初期位置に再表示
		if (playerFlag == false)
		{
			playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
			playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
			playerFlag = true;
		}

		// 背景の移動
		bgPosY = bgPosY + 1;

		ClsDrawScreen();		// 画面消去

		// 背景の表示
		DrawGraph(0, bgPosY, bgImage, false);
		DrawGraph(0, bgPosY - BG_SIZE_Y, bgImage, false);
		if (bgPosY >= BG_SIZE_Y)
		{
			bgPosY = 0;
		}
	
		// 画面の対角線表示
		DrawLine(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff);
		DrawLine(SCREEN_SIZE_X, 0, 0, SCREEN_SIZE_Y, 0xffffff);

		// 敵の表示
		if (enemyFlag == true)
		{
			DrawGraph(enemyPosX, enemyPosY, enemyImage, true);
			DrawBox(enemyPosX, enemyPosY, enemyPosX + ENEMY_SIZE_X, enemyPosY + ENEMY_SIZE_Y, 0xffffff,false);
		}
		
		// 弾の表示
		if (shotFlag[0] == true
			&& playerFlag == true)
		{
			DrawGraph(shotPosX[0], shotPosY[0], shotImage, true);
		}
		if (shotFlag[1]== true
			&& playerFlag == true)
		{
			DrawGraph(shotPosX[1], shotPosY[1], shotImage, true);
		}
		if (shotFlag[2] == true
			&& playerFlag == true)
		{
			DrawGraph(shotPosX[2], shotPosY[2], shotImage, true);
		}


		// 爆発の表示
		if (blastFlag == true)
		{
			DrawGraph(blastPosX, blastPosY, blastImage[blastAni], true);
			blastAni = blastAni + 1;
			if (blastAni >= BLAST_ANI)
			{
				blastAni = 0;
				blastFlag = false;
			}
		}

		// ﾌﾟﾚｲﾔｰの表示
		if (playerFlag == true)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);
			DrawBox(playerPosX, playerPosY, playerPosX + PLAYER_SIZE_X, playerPosY + PLAYER_SIZE_Y, 0xffffff, false);
		}

		// 文字の表示
		DrawFormatString(0, 0, 0xffffff, "Speed:%d", playerSpeed);

		ScreenFlip();			// 裏画面を表画面に瞬間ｺﾋﾟｰ
	}
	DxLib_End();				// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;					// このﾌﾟﾛｸﾞﾗﾑの終了
}