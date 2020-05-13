#include"Dxlib.h"

// �萔�̒�`
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

// ��ڲ԰
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32

// �e
#define SHOT_SIZE_X 32
#define SHOT_SIZE_Y 32

// �G
#define ENEMY_SIZE_X 64
#define ENEMY_SIZE_Y 64

// ����
#define BLAST_ANI 24
#define BLAST_SIZE_X 96
#define BLAST_SIZE_Y 96

// �w�i
#define BG_SIZE_Y 960

// �ϐ��̒�`
// ��ڲ԰
int playerImage;
int playerPosX;
int playerPosY;
int playerSpeed;
bool playerFlag;

// �e
int shotImage;
int shotPosX[3];
int shotPosY[3];
int shotFlag[3];
int shotSpeed;

// �G
int enemyImage;
int enemyPosX;
int enemyPosY;
int enemySpeed;
bool enemyFlag;

// �w�i
int bgImage;
int bgPosX;
int bgPosY;

// ����
int blastImage[BLAST_ANI];
int blastAni;
bool blastFlag;
int blastPosX;
int blastPosY;

// WinMain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ------------- ���я���
	SetWindowText("1916208_����˗���");
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	// 640�~480�ޯ�65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);							// true:window false:�ٽ�ذ�
	if (DxLib_Init() == -1) return -1;				// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);					// �ЂƂ܂��ޯ��o�b�t�@�ɕ`��

	// ���̨���̓o�^
	playerImage = LoadGraph("image/player.png");
	shotImage = LoadGraph("image/shot.png");
	enemyImage = LoadGraph("image/enemy.png");
	bgImage = LoadGraph("image/haikei.png");
//	blastImage = LoadGraph("image/blast.png");
	LoadDivGraph("image/blast.png", 24, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImage);

	// �ϐ��̏�����
	playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X)/2;
	playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
	playerSpeed = 4;
	playerFlag = true;

	shotPosX[0] = 640;
	shotPosY[0] = 0;
	shotSpeed = 15;
	shotFlag[0] = false;		// �e����������@true
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
	
	

	// �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// Ҳݏ���

		// �L�[����
		// ��߰�ނ�ς���
		if (CheckHitKey(KEY_INPUT_ADD) == 1)			// +key�������ƽ�߰�ނ��オ��
		{
			playerSpeed = playerSpeed + 1;
		}
		if (CheckHitKey(KEY_INPUT_SUBTRACT) == 1)		// -key�������ƽ�߰�ނ�������
		{
			playerSpeed = playerSpeed - 1;
			if (playerSpeed < 1)
			{
				playerSpeed = 1;
			}
		}

		// *����������
		if (CheckHitKey(KEY_INPUT_MULTIPLY) == 1)	// *�L�[�Ŕ���������
		{
			blastFlag = true;
		}

		// �G���ĕ\��������
		if (CheckHitKey(KEY_INPUT_DIVIDE) == 1)		// /�L�[�œG���ĕ\������
		{
			enemyPosX = GetRand(SCREEN_SIZE_X - ENEMY_SIZE_X);
			enemyPosY = GetRand(100);
			enemyFlag = true;

		}

		// 2486 �ړ�������
		if (CheckHitKey(KEY_INPUT_NUMPAD6) == 1)		// �E�ړ�
		{
			if (playerPosX < SCREEN_SIZE_X - PLAYER_SIZE_X)
			{
				playerPosX = playerPosX + playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD4) == 1)		// ���ړ�
		{
			if (playerPosX > 0)
			{
				playerPosX = playerPosX - playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD8) == 1)		// ��ړ�
		{
			if (playerPosY > 0)
			{
				playerPosY = playerPosY - playerSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD2) == 1)		// ���ړ�
		{
			if (playerPosY < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPosY = playerPosY + playerSpeed;
			}
		}

		// �G�̈ړ�
		enemyPosY = enemyPosY + enemySpeed;
		if (enemyPosY > SCREEN_SIZE_Y)
		{
			enemyPosY = -ENEMY_SIZE_Y;
		}
		
		// �e�̔���
		if (shotFlag[0] == true)
		{
			shotPosY[0] = shotPosY[0] - shotSpeed;
			if (shotPosY[0] < -SHOT_SIZE_Y)		// �e����ʊO�ɏo���Ƃ���false�ɂ���
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

		// 3WEY�e�̔���
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

		// �����蔻��
		// �_�ƓG
		//		if (enemyPosX <= shotPosX
		//			&& shotPosX <= enemyPosX + ENEMY_SIZE_X
		//			&& enemyPosY <= shotPosY
		//			&& shotPosY <= enemyPosY + ENEMY_SIZE_Y)
		//		{
		//			enemyFlag = false;
		//		}

		// ���@�ƓG
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

		// �e�ƓG
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

		// �G��|������ĕ\��
		if (enemyFlag == false)
		{
			enemyPosX = GetRand(SCREEN_SIZE_X - ENEMY_SIZE_X);
			enemyPosY = GetRand(100);
			enemyFlag = true;
		}

		// ���@���|���ꂽ�珉���ʒu�ɍĕ\��
		if (playerFlag == false)
		{
			playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
			playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
			playerFlag = true;
		}

		// �w�i�̈ړ�
		bgPosY = bgPosY + 1;

		ClsDrawScreen();		// ��ʏ���

		// �w�i�̕\��
		DrawGraph(0, bgPosY, bgImage, false);
		DrawGraph(0, bgPosY - BG_SIZE_Y, bgImage, false);
		if (bgPosY >= BG_SIZE_Y)
		{
			bgPosY = 0;
		}
	
		// ��ʂ̑Ίp���\��
		DrawLine(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0xffffff);
		DrawLine(SCREEN_SIZE_X, 0, 0, SCREEN_SIZE_Y, 0xffffff);

		// �G�̕\��
		if (enemyFlag == true)
		{
			DrawGraph(enemyPosX, enemyPosY, enemyImage, true);
			DrawBox(enemyPosX, enemyPosY, enemyPosX + ENEMY_SIZE_X, enemyPosY + ENEMY_SIZE_Y, 0xffffff,false);
		}
		
		// �e�̕\��
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


		// �����̕\��
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

		// ��ڲ԰�̕\��
		if (playerFlag == true)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);
			DrawBox(playerPosX, playerPosY, playerPosX + PLAYER_SIZE_X, playerPosY + PLAYER_SIZE_Y, 0xffffff, false);
		}

		// �����̕\��
		DrawFormatString(0, 0, 0xffffff, "Speed:%d", playerSpeed);

		ScreenFlip();			// ����ʂ�\��ʂɏu�Ժ�߰
	}
	DxLib_End();				// DXײ���؂̏I������
	return 0;					// ������۸��т̏I��
}