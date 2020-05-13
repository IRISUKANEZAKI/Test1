#include"Dxlib.h"

// ’è”‚Ì’è‹`
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

// ÌßÚ²Ô°
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32

// ’e
#define SHOT_SIZE_X 32
#define SHOT_SIZE_Y 32

// “G
#define ENEMY_SIZE_X 64
#define ENEMY_SIZE_Y 64

// ”š”­
#define BLAST_ANI 24
#define BLAST_SIZE_X 96
#define BLAST_SIZE_Y 96

// ”wŒi
#define BG_SIZE_Y 960

// •Ï”‚Ì’è‹`
// ÌßÚ²Ô°
int playerImage;
int playerPosX;
int playerPosY;
int playerSpeed;
bool playerFlag;

// ’e
int shotImage;
int shotPosX[3];
int shotPosY[3];
int shotFlag[3];
int shotSpeed;

// “G
int enemyImage;
int enemyPosX;
int enemyPosY;
int enemySpeed;
bool enemyFlag;

// ”wŒi
int bgImage;
int bgPosX;
int bgPosY;

// ”š”­
int blastImage[BLAST_ANI];
int blastAni;
bool blastFlag;
int blastPosX;
int blastPosY;

// WinMainŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ------------- ¼½ÃÑˆ—
	SetWindowText("1916208_‹àèˆË—¢é");
	// ¼½ÃÑˆ—
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	// 640~480ÄŞ¯Ä65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);							// true:window false:ÌÙ½¸Ø°İ
	if (DxLib_Init() == -1) return -1;				// DX×²ÌŞ×Ø‰Šú‰»ˆ—
	SetDrawScreen(DX_SCREEN_BACK);					// ‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ƒoƒbƒtƒ@‚É•`‰æ

	// ¸Ş×Ì¨¯¸‚Ì“o˜^
	playerImage = LoadGraph("image/player.png");
	shotImage = LoadGraph("image/shot.png");
	enemyImage = LoadGraph("image/enemy.png");
	bgImage = LoadGraph("image/haikei.png");
//	blastImage = LoadGraph("image/blast.png");
	LoadDivGraph("image/blast.png", 24, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImage);

	// •Ï”‚Ì‰Šú‰»
	playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X)/2;
	playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
	playerSpeed = 4;
	playerFlag = true;

	shotPosX[0] = 640;
	shotPosY[0] = 0;
	shotSpeed = 15;
	shotFlag[0] = false;		// ’e‚ğŒ‚‚Á‚½‚ç@true
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
	
	

	// ¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// Ò²İˆ—

		// ƒL[‘€ì
		// ½Ëß°ÄŞ‚ğ•Ï‚¦‚é
		if (CheckHitKey(KEY_INPUT_ADD) == 1)			// +key‚ğ‰Ÿ‚·‚Æ½Ëß°ÄŞ‚ªã‚ª‚é
		{
			playerSpeed = playerSpeed + 1;
		}
		if (CheckHitKey(KEY_INPUT_SUBTRACT) == 1)		// -key‚ğ‰Ÿ‚·‚Æ½Ëß°ÄŞ‚ª‰º‚ª‚é
		{
			playerSpeed = playerSpeed - 1;
			if (playerSpeed < 1)
			{
				playerSpeed = 1;
			}
		}

		// *”š”­‚³‚¹‚é
		if (CheckHitKey(KEY_INPUT_MULTIPLY) == 1)	// *ƒL[‚Å”š”­‚³‚¹‚é
		{
			blastFlag = true;
		}

		// “G‚ğÄ•\¦‚³‚¹‚é
		if (CheckHitKey(KEY_INPUT_DIVIDE) == 1)		// /ƒL[‚Å“G‚ğÄ•\¦‚·‚é
		{
			enemyPosX = GetRand(SCREEN_SIZE_X - ENEMY_SIZE_X);
			enemyPosY = GetRand(100);
			enemyFlag = true;

		}

		// 2486 ˆÚ“®‚³‚¹‚é
		if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1)		// ‰EˆÚ“®
		{
			if (playerPosX < SCREEN_SIZE_X - PLAYER_SIZE_X)
			{
				playerPosX = playerPosX + playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1)		// ¶ˆÚ“®
		{
			if (playerPosX > 0)
			{
				playerPosX = playerPosX - playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD8) == 1)		// ãˆÚ“®
		{
			if (playerPosY > 0)
			{
				playerPosY = playerPosY - playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD2) == 1)		// ‰ºˆÚ“®
		{
			if (playerPosY < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPosY = playerPosY + playerSpeed;
			}
		}

		// “G‚ÌˆÚ“®
		enemyPosY = enemyPosY + enemySpeed;
		if (enemyPosY > SCREEN_SIZE_Y)
		{
			enemyPosY = -ENEMY_SIZE_Y;
		}
		
		// ’e‚Ì”­Ë
		if (shotFlag[0] == true)
		{
			shotPosY[0] = shotPosY[0] - shotSpeed;
			if (shotPosY[0] < -SHOT_SIZE_Y)		// ’e‚ª‰æ–ÊŠO‚Éo‚½‚Æ‚«‚Éfalse‚É‚·‚é
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

		// 3WEY’e‚Ì”­Ë
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

		// “–‚½‚è”»’è
		// “_‚Æ“G
		//		if (enemyPosX <= shotPosX
		//			&& shotPosX <= enemyPosX + ENEMY_SIZE_X
		//			&& enemyPosY <= shotPosY
		//			&& shotPosY <= enemyPosY + ENEMY_SIZE_Y)
		//		{
		//			enemyFlag = false;
		//		}

		// ©‹@‚Æ“G
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

		// ’e‚Æ“G
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

		// “G‚ğ“|‚µ‚½‚çÄ•\¦
		if (enemyFlag == false)
		{
			enemyPosX = GetRand(SCREEN_SIZE_X - ENEMY_SIZE_X);
			enemyPosY = GetRand(100);
			enemyFlag = true;
		}

		// ©‹@‚ª“|‚³‚ê‚½‚ç‰ŠúˆÊ’u‚ÉÄ•\¦
		if (playerFlag == false)
		{
			playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
			playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
			playerFlag = true;
		}

		// ”wŒi‚ÌˆÚ“®
		bgPosY = bgPosY + 1;

		ClsDrawScreen();		// ‰æ–ÊÁ‹

		// ”wŒi‚Ì•\¦
		DrawGraph(0, bgPosY, bgImage, false);
		DrawGraph(0, bgPosY - BG_SIZE_Y, bgImage, false);
		if (bgPosY >= BG_SIZE_Y)
		{
			bgPosY = 0;
		}
	
		// ‰æ–Ê‚Ì‘ÎŠpü•\¦
		DrawLine(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff);
		DrawLine(SCREEN_SIZE_X, 0, 0, SCREEN_SIZE_Y, 0xffffff);

		// “G‚Ì•\¦
		if (enemyFlag == true)
		{
			DrawGraph(enemyPosX, enemyPosY, enemyImage, true);
			DrawBox(enemyPosX, enemyPosY, enemyPosX + ENEMY_SIZE_X, enemyPosY + ENEMY_SIZE_Y, 0xffffff,false);
		}
		
		// ’e‚Ì•\¦
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


		// ”š”­‚Ì•\¦
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

		// ÌßÚ²Ô°‚Ì•\¦
		if (playerFlag == true)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);
			DrawBox(playerPosX, playerPosY, playerPosX + PLAYER_SIZE_X, playerPosY + PLAYER_SIZE_Y, 0xffffff, false);
		}

		// •¶š‚Ì•\¦
		DrawFormatString(0, 0, 0xffffff, "Speed:%d", playerSpeed);

		ScreenFlip();			// — ‰æ–Ê‚ğ•\‰æ–Ê‚ÉuŠÔºËß°
	}
	DxLib_End();				// DX×²ÌŞ×Ø‚ÌI—¹ˆ—
	return 0;					// ‚±‚ÌÌßÛ¸Ş×Ñ‚ÌI—¹
}