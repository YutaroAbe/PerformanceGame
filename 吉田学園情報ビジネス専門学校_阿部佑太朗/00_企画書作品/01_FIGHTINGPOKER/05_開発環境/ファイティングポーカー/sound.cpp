//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// サウンド処理 [sound.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "sound.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// パラメータ構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント(-1でループ再生)
} SOUNDPARAM;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイスへのポインタ
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

															// 各音素材のパラメータ
SOUNDPARAM g_aSoundParam[SOUND_LABEL_MAX] =
{
	{ "data/BGM/TITLE/title000.wav", -1 },						//	タイトル画面BGM
	{ "data/BGM/SELECT/Select000.wav", -1 },						//	セレクト画面BGM
	{ "data/BGM/BATTLETURN/R1R2R3R4/BattleTurn000.wav", -1 },		//  バトルR１からR4画面BGM
	{ "data/BGM/BATTLETURN/R5/BattleTurn001.wav", -1 },			//  バトルR5ゲーム画面BGM
	{ "data/BGM/POKERTURN/Pokerturn000.wav", -1 },				//  ポーカーフェイズ画面BGM
	{ "data/BGM/RESULT/Result000.wav", -1 },						//  リザルト画面BGM
	{ "data/BGM/RULEBOOK/Rulebook000.wav", -1 },					//  ルールブック画面BGM
	{ "data/BGM/CHARACTER/Character000.wav", -1 },				//  キャラクター画面BGM
	{ "data/BGM/CREDIT/Credit000.wav", -1 },						// クレジット画面BGM

	{ "data/SE/Decision000.wav", 0 },							// 　決定音SE
	{ "data/SE/Selecteditem000.wav", 0 },						// 　選択音SE
	{ "data/SE/SwordCutSound000.wav", 0 },						// 　ダメージ音
	{ "data/SE/pause.wav", 0 },									// 　ポーズSE
	{ "data/SE/cancel.wav", 0 },									// 　キャンセルSE

	{ "data/SE/HIT/Hit000.wav", 0 },								// 　ヒット音弱
	{ "data/SE/HIT/Hit001.wav", 0 },								// 　ヒット音大
	{ "data/SE/HIT/GUARD000.wav", 0 },								// 　ガード音

	{ "data/SE/SKILL/godSkill000.wav", 0 },							// 　ゴッドSKILL
	{ "data/SE/SKILL/heiminSkill000.wav", 0 },						// 　平民SKILL
	{ "data/SE/SKILL/maouSkill000.wav", 0 },						// 　魔王SKILL
	{ "data/SE/SKILL/ouSkill000.wav", 0 },							// 　王様SKILL
	{ "data/SE/SKILL/yushaSkill000.wav", 0 },						// 　勇者SKILL

	{ "data/SE/MAOU_CV/000_mou.wav", 0 },						// 　魔王[攻撃弱]
	{ "data/SE/MAOU_CV/001_mou.wav", 0 },						// 　魔王[攻撃強]
	{ "data/SE/MAOU_CV/002_mou.wav", 0 },						// 　魔王[ダメージ]
	{ "data/SE/MAOU_CV/003_mou.wav", 0 },						// 　魔王[ぶっ飛び]
	{ "data/SE/MAOU_CV/004_mou.wav", 0 },						// 　魔王[スキル]
	{ "data/SE/MAOU_CV/005_mou.wav", 0 },						// 　魔王[勝利]
	{ "data/SE/MAOU_CV/006_mou.wav", 0 },						// 　魔王[キャラクター画面]

	{ "data/SE/YUSHA_CV/000_yusha.wav", 0 },					// 　勇者[攻撃弱]
	{ "data/SE/YUSHA_CV/001_yusha.wav", 0 },					// 　勇者[攻撃強]
	{ "data/SE/YUSHA_CV/002_yusha.wav", 0 },					// 　勇者[ダメージ]
	{ "data/SE/YUSHA_CV/003_yusha.wav", 0 },					// 　勇者[ぶっ飛び]
	{ "data/SE/YUSHA_CV/004_yusha.wav", 0 },					// 　勇者[スキル]
	{ "data/SE/YUSHA_CV/005_yusha.wav", 0 },					// 　勇者[勝利]
	{ "data/SE/YUSHA_CV/006_yusha.wav", 0 },					// 　勇者[キャラクター画面]

	{ "data/SE/OU_CV/000_ou.wav", 0 },							// 　王[攻撃弱]
	{ "data/SE/OU_CV/001_ou.wav", 0 },							// 　王[攻撃強]
	{ "data/SE/OU_CV/002_ou.wav", 0 },							// 　王[ダメージ]
	{ "data/SE/OU_CV/003_ou.wav", 0 },							// 　王[ぶっ飛び]
	{ "data/SE/OU_CV/004_ou.wav", 0 },							// 　王[スキル]
	{ "data/SE/OU_CV/005_ou.wav", 0 },							// 　王[勝利]
	{ "data/SE/OU_CV/006_ou.wav", 0 },							// 　王[キャラクター画面]

	{ "data/SE/HEIMIN_CV/000_heimin.wav", 0 },					// 　平民[攻撃弱]
	{ "data/SE/HEIMIN_CV/001_heimin.wav", 0 },					// 　平民[攻撃強]
	{ "data/SE/HEIMIN_CV/002_heimin.wav", 0 },					// 　平民[ダメージ]
	{ "data/SE/HEIMIN_CV/003_heimin.wav", 0 },					// 　平民[ぶっ飛び]
	{ "data/SE/HEIMIN_CV/004_heimin.wav", 0 },					// 　平民[スキル]
	{ "data/SE/HEIMIN_CV/005_heimin.wav", 0 },					// 　平民[勝利]
	{ "data/SE/HEIMIN_CV/006_heimin.wav", 0 },					// 　平民[キャラクター画面]

	{ "data/SE/GOD_CV/000_god.wav", 0 },						// 　神[攻撃弱]
	{ "data/SE/GOD_CV/001_god.wav", 0 },						// 　神[攻撃強]
	{ "data/SE/GOD_CV/002_god.wav", 0 },						// 　神[ダメージ]
	{ "data/SE/GOD_CV/003_god.wav", 0 },						// 　神[ぶっ飛び]
	{ "data/SE/GOD_CV/004_god.wav", 0 },						// 　神[スキル]
	{ "data/SE/GOD_CV/005_god.wav", 0 },						// 　神[勝利]
	{ "data/SE/GOD_CV/006_god.wav", 0 },						// 　神[キャラクター画面]

	{ "data/SE/BATTLE_SE/r1.wav", 0 },							// 　ラウンド1
	{ "data/SE/BATTLE_SE/r2.wav", 0 },							// 　ラウンド2
	{ "data/SE/BATTLE_SE/r3.wav", 0 },							// 　ラウンド3
	{ "data/SE/BATTLE_SE/r4.wav", 0 },							// 　ラウンド4
	{ "data/SE/BATTLE_SE/r5.wav", 0 },							// 　ラウンド5
	{ "data/SE/BATTLE_SE/ko.wav", 0 },							// 　KO
	{ "data/SE/BATTLE_SE/fight.wav", 0 },						// 　fight
	{ "data/SE/BATTLE_SE/timeover.wav", 0 },					// 　タイムオーバー

	{ "data/SE/card_set.wav", 0 },								// カード配布音
	{ "data/SE/card_select.wav", 0 },							// カード選択音
	{ "data/SE/card_open.wav", 0 },								// カードめくり音

	{ "data/SE/announce.wav", 0 },								// アナウンス音

	{ "data/SE/special.wav", 0 },								//
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(g_aSoundParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = g_aSoundParam[nCntSound].nCntLoop;

		// オーディオバッファの登録
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;

	if (g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// セグメント再生(停止)
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = g_aSoundParam[label].nCntLoop;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// セグメント停止
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// セグメント停止
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void StopSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);

			// オーディオバッファの削除
			g_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// チャンクのチェック
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// チャンクデータの読み込み
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 音量調整再生
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SelectVolume(SOUND_LABEL label, float fVolume)
{
	// 音量調整
	g_apSourceVoice[label]->SetVolume(fVolume);
	PlaySound(label);

	// 音量をもとに戻す
	//g_apSourceVoice[label]->SetVolume(1.0f);
}



