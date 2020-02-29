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

	scoreText = new Actor(this);
	scoreText->SetPosition(Vector2(SCREEN_WIDTH / 2, 32));
	scoreTsc = new TextSpriteComponent(scoreText);
	scoreTsc->SetText("Score: 0");
	scoreTsc->SetTextSize(80);

	levels[0] = "Assets/Maps/Mario01.csv";
	levels[1] = "Assets/Mario_TestLevel2.csv";
	levels[2] = "Assets/MarioBigTest.csv";
	levels[3] = "Assets/MarioSmallTest.csv";

	mapActor = new Actor(this);
	map = new TileMapComponent(mapActor);

	SDL_Texture* tilesTexture = mEngine->GetTexture("Assets/TileMap.png");
	map->SetTexture(tilesTexture);
	map->LoadMap(levels[currentLevel]);
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
	score += amount;
	std::string text = "Score: " + std::to_string(score);
	scoreTsc->SetText(text);
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
	}

	for (auto& koopa : mKoopas) {
		RemoveKoopa(koopa);
	}

	for (auto& powBlock : mPowBlocks) {
		powBlock->SetState(Actor::EDead);
		RemovePowBlock(powBlock);
	}

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
	score = 0;
	scoreTsc->SetText("Score: " + score);
	currentLevel++; 
	EmptyMap();
	map->LoadMap(levels[currentLevel]);
}

void Game::PollInput()
{
	mEngine->PollInput();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	mPlayer->HandleEvents(state);

	if (state[SDL_SCANCODE_1]) {
		score = 0;
		scoreTsc->SetText("Score: " + score);
		EmptyMap();
		map->LoadMap(levels[0]);
		
	}
	else if (state[SDL_SCANCODE_2]) {
		score = 0;
		scoreTsc->SetText("Score: " + score);
		EmptyMap();
		map->LoadMap(levels[1]);
	}
	else if (state[SDL_SCANCODE_3]) {
		score = 0;
		scoreTsc->SetText("Score: " + score);
		EmptyMap();
		map->LoadMap(levels[2]);
	}
	else if (state[SDL_SCANCODE_4]) {
		score = 0;
		scoreTsc->SetText("Score: " + score);
		EmptyMap();
		map->LoadMap(levels[3]);
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


	mEngine->Update();
}

void Game::Render()
{
	mEngine->Render();
}

void Game::Shutdown()
{
	mEngine->Shutdown();
}