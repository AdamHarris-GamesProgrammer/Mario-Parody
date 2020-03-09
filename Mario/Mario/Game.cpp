#include "Game.h"

#include "ComponentsList.h"
#include "Constants.h"

#include "Actor.h"

#include "Mario.h"
#include "Coin.h"
#include "Tile.h"
#include "LevelGoal.h"
#include "Koopa.h"
#include "PowBlock.h"
#include "ScoreManager.h"
#include "ButtonComponent.h"
#include "NextLevelButton.h"


bool Game::Initialize()
{
	mEngine = new BlueSky(this);
	if (mEngine->Initialize())
	{
		LoadContent();
		mEngine->RunLoop();

		return true;
	}
	else
	{
		return false;
	}
}

void Game::LoadContent()
{

	//Background clouds
	bgActor = new Actor(this);
	bgActor->SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	BGSpriteComponent* bg = new BGSpriteComponent(bgActor);
	bg->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	std::vector<SDL_Texture*> bgtexs = {
		mEngine->GetTexture("Assets/bgScrolling.png"),
		mEngine->GetTexture("Assets/bgScrolling.png")
	};

	bg->SetBGTexture(bgtexs);
	bg->SetScrollSpeed(-25.0f);

	gMusic = Mix_LoadMUS("Assets/Audio/BgMusic.mp3");

	if (!gMusic) {
		std::cout << "Error: Cannot load BgMusic.mp3: " << Mix_GetError() << std::endl;
	}

	//foreground textures
	fgActor = new Actor(this);
	fgActor->SetPosition(Vector2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 32.0f));

	BGSpriteComponent* fg = new BGSpriteComponent(fgActor);
	fg->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	std::vector<SDL_Texture*> fgtexs = {
		mEngine->GetTexture("Assets/BGForeground1.png"),
		mEngine->GetTexture("Assets/BGForeground2.png"),
		mEngine->GetTexture("Assets/BGForeground3.png")
	};

	fg->SetBGTexture(fgtexs);
	fg->SetScrollSpeed(-10.0f);

	//Mario
	mPlayer = new Mario(this);

	mCurrentLevel = 0;
	mScoreManager = new ScoreManager(this);
	mHighScore = mScoreManager->GetHighscore();
	std::cout << "Highscore: " << mHighScore << std::endl;
	mScoreText = new Actor(this);
	mScoreText->SetPosition(Vector2(SCREEN_WIDTH / 2, 32));
	mScoreTsc = new TextSpriteComponent(mScoreText);
	mScoreTsc->SetText("Score: 0");
	mScoreTsc->SetTextSize(72);

	mLevels[0] = "Assets/Maps/Mario01.csv";
	mLevels[1] = "Assets/Maps/Mario02.csv";
	mLevels[2] = "Assets/MarioBigTest.csv";
	mLevels[3] = "Assets/MarioSmallTest.csv";

	mapActor = new Actor(this);
	map = new TileMapComponent(mapActor);

	SDL_Texture* tilesTexture = mEngine->GetTexture("Assets/TileMap.png");
	map->SetTexture(tilesTexture);
	map->LoadMap(mLevels[mCurrentLevel]);

	mNextLevelScreen = new NextLevelScreen(this);
}

void Game::AddCoin(Coin* coin)
{
	mCoins.emplace_back(coin);
}

void Game::RemoveCoin(Coin* coin)
{
	auto iter = std::find(mCoins.begin(), mCoins.end(), coin);

	if (iter != mCoins.end()) {
		mCoins.erase(iter);
	}
}

void Game::IncrementScore(int amount) {
	mScore += amount;
	std::string text = "Score: " + std::to_string(mScore);
	mScoreTsc->SetText(text);
}

void Game::AddTile(Tile* tile)
{
	mTiles.emplace_back(tile);
}

void Game::RemoveTile(Tile* tile)
{
	auto iter = std::find(mTiles.begin(), mTiles.end(), tile);

	if (iter != mTiles.end()) {
		mTiles.erase(iter);
	}
}

void Game::SetPlayerSpawnPoint(Vector2 position) {
	mPlayer->SetPosition(position);
	mPlayer->ChangePlayerTile(position);
}

void Game::EmptyMap() {
	for(auto & tile : mTiles) {
		tile->SetState(Actor::EDead);
		
	}

	for (auto& koopa : mKoopas) {
		koopa->SetState(Actor::EDead);
		RemoveKoopa(koopa);
	}

	for (auto& powBlock : mPowBlocks) {
		//powBlock->SetState(Actor::EDead);
		RemovePowBlock(powBlock);
	}

	mPowBlocks.clear();
	map->ClearMap();
}

void Game::AddKoopa(Koopa* koopa)
{
	mKoopas.emplace_back(koopa);
}

void Game::RemoveKoopa(Koopa* koopa)
{
	auto iter = std::find(mKoopas.begin(), mKoopas.end(), koopa);

	if (iter != mKoopas.end()) {
		mKoopas.erase(iter);
	}
}

void Game::AddPowBlock(class PowBlock* powBlock)
{
	mPowBlocks.emplace_back(powBlock);
}

void Game::RemovePowBlock(class PowBlock* powBlock)
{
	auto iter = std::find(mPowBlocks.begin(), mPowBlocks.end(), powBlock);

	if (iter != mPowBlocks.end()) {
		mPowBlocks.erase(iter);
	}
}

void Game::AddLevelGoal(LevelGoal* goal)
{
	mLevelGoal = goal;
}

void Game::NextLevel()
{
	mNextLevelScreen->SetActive(false);

	gameOver = true;

	mScore = 0;
	mScoreTsc->SetText("Score: " + mScore);
	mCurrentLevel++; 

	if (mCurrentLevel > 3) {
		mCurrentLevel = 0;
	}
	EmptyMap();
	mHighScore = mScoreManager->GetHighscore();
	map->LoadMap(mLevels[mCurrentLevel]);
	gameOver = false;
}

void Game::PollInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	mNextLevelScreen->Update(0.16f, event);

	mEngine->PollInput();

	const Uint8* state = SDL_GetKeyboardState(NULL);
	mPlayer->HandleEvents(state);

	if (state[SDL_SCANCODE_1]) {
		gameOver = true;
		mScore = 0;
		mScoreTsc->SetText("Score: " + mScore);
		mCurrentLevel = 0;
		EmptyMap();
		map->LoadMap(mLevels[mCurrentLevel]);
		gameOver = false;
		
	}
	else if (state[SDL_SCANCODE_2]) {
		gameOver = true;
		mScore = 0;
		mScoreTsc->SetText("Score: " + mScore);
		EmptyMap();
		mCurrentLevel = 1;
		map->LoadMap(mLevels[mCurrentLevel]);
		gameOver = false;
	}
	else if (state[SDL_SCANCODE_3]) {
		gameOver = true;
		mScore = 0;
		mScoreTsc->SetText("Score: " + mScore);
		EmptyMap();
		mCurrentLevel = 2;
		map->LoadMap(mLevels[mCurrentLevel]);
		gameOver = false;
	}
	else if (state[SDL_SCANCODE_4]) {
		gameOver = true;
		mScore = 0;
		mScoreTsc->SetText("Score: " + mScore);
		EmptyMap();
		mCurrentLevel = 3;
		map->LoadMap(mLevels[mCurrentLevel]);
		gameOver = false;
	}
}

void Game::Update()
{
	mCamera.x = mPlayer->GetPosition().x - SCREEN_WIDTH / 2;

	if (mCamera.x < 0)
		mCamera.x = 0;
	if (mCamera.x > mCamera.w)
		mCamera.x = mCamera.w;
	if (mCamera.y < 0)
		mCamera.y = 0;
	if (mCamera.y > mCamera.h)
		mCamera.y = mCamera.h;

	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(gMusic, -1);
	}

	mEngine->Update();
}

void Game::Render()
{
	mEngine->Render();
}

void Game::LoadNextLevelMenu()
{
	if (mScore > mHighScore) {
		mScoreManager->SetHighscore(mScore);
		mHighScore = mScore;
	}

	mNextLevelScreen->SetActive(true);
}

void Game::Shutdown()
{
	mEngine->Shutdown();
}