#include "level.hpp"


#define SPAWN_AREA 2200

#define BACKGROUND_INTERVAL 60
#define BACKGROUND_SPEED -5


#define PLAYER_STARTING_POS_X stateManager->GetSharedContext()->window->GetInternalSize().x/4
#define PLAYER_STARTING_POS_Y stateManager->GetSharedContext()->window->GetInternalSize().y/2
#define PLAYER_SIZE 100
#define PLAYER_COLLISION_SIZE 100
#define PLAYER_COLOR BLACK
#define PLAYER_MOVE_UP (Vector2){0, -10}
#define PLAYER_MOVE_DOWN (Vector2){0, 10}
#define PLAYER_MOVE_LEFT (Vector2){-10, 0}
#define PLAYER_MOVE_RIGHT (Vector2){10, 0}
#define PLAYER_HP 10

#define ENEMY_INTERVAL 90
#define ENEMY_SPEED (Vector2){-10, 0}
#define TOTAL_ENEMY_TYPE 3
#define ENEMY_MAINBODY_SIZE 100
#define ENEMY_SIDEBODY_SIZE 50
#define ENEMY_COLLISION_SIZE 150
#define ENEMY_COLOR RED
#define ENEMY_COLLISION_COLOR ORANGE

#define TYPE_ONE_COLLISION_DISTANCE -500
#define TYPE_TWO_COLLISION_DISTANCE 350
#define TYPE_THREE_COLLISION_DISTANCE -400

static std::shared_ptr<Entity> CreateTypeOneEnemy();
static std::shared_ptr<Entity> CreateTypeTwoEnemy();
static std::shared_ptr<Entity> CreateTypeThreeEnemy();

static bool isAudioLoaded;

void Level::Init(){
	ResetPlayer();
	ResetIntroBar();

	isPaused = false;
	isGameOver = false;

	isAudioLoaded = false;
	
}

void Level::Awake(){
	ResetPlayer();
	ResetIntroBar();

	if (!backgrounds.empty()) backgrounds.clear();
	if (!enemyList.empty()) enemyList.clear();

	isPaused = false;
	isGameOver = false;

	if (isAudioLoaded) return;

	isAudioLoaded = true;

	#if defined(PLATFORM_WEB)
		stateManager->GetSharedContext()->audio->Add("scoreTick", "270342__littlerobotsoundfactory__pickup_03.ogg");
		stateManager->GetSharedContext()->audio->Add("playerHit", "270344__littlerobotsoundfactory__shoot_00.ogg");
		stateManager->GetSharedContext()->audio->Add("movement", "270315__littlerobotsoundfactory__menu_navigate_03.ogg");
	#else
		stateManager->GetSharedContext()->audio->Add("scoreTick", "270342__littlerobotsoundfactory__pickup_03.wav");
		stateManager->GetSharedContext()->audio->Add("playerHit", "270344__littlerobotsoundfactory__shoot_00.wav");
		stateManager->GetSharedContext()->audio->Add("movement", "270315__littlerobotsoundfactory__menu_navigate_03.wav");
	#endif

}

void Level::Update(){
	static int bgTimer = BACKGROUND_INTERVAL;
	static int enemyTimer = ENEMY_INTERVAL;

	if (isGameOver){
		if (IsKeyPressed(KEY_ENTER)) stateManager->SwitchTo(StateType::LEVEL);
		if (IsKeyPressed(KEY_BACKSPACE)) stateManager->SwitchTo(StateType::INTRO);
	}

	if (IsKeyPressed(KEY_P)) isPaused = !isPaused;
	if (isPaused) return;
	

	CheckPlayerCollision();
	MovePlayer();
	BoundCheck();
	
	if (bgTimer == 0){
		SpawnBackground();
		bgTimer = BACKGROUND_INTERVAL;
	}

	if (enemyTimer == 0){
		SpawnEnemy();
		enemyTimer = ENEMY_INTERVAL;
	}
	for (auto i: enemyList) i->Update(ENEMY_SPEED);
	MoveBackground(BACKGROUND_SPEED);

	if (topBarRec.rec.height >= 0) topBarRec.rec.height -= 2;
	if (botBarRec.rec.y <= stateManager->GetSharedContext()->window->GetInternalSize().y) botBarRec.rec.y += 2;

	bgTimer--;
	enemyTimer--;
}

void Level::Render(){
	for (auto i: backgrounds) DrawRectangleRec(i.rec, i.color);

	if (isGameOver){
		DrawText("GAME OVER", stateManager->GetSharedContext()->window->GetInternalSize().x/6, 475, 100, BLACK);
		DrawText("Press ENTER to try again, or BACKSPACE to return", stateManager->GetSharedContext()->window->GetInternalSize().x/6, 600, 25, BLACK);

		return;
	} 
	
	player->Render();

	for (auto i: enemyList) i->Render();

	DrawRectangleRec(topBarRec.rec, BLACK);
	DrawRectangleRec(botBarRec.rec, BLACK);

	DrawText("ARROW KEYS: Move			P: Pause", 50, 150, 50, BLACK);
	DrawText(TextFormat("SCORE: %03i", playerScore), 50, 50, 100, BLACK);
}

void Level::ResetPlayer(){
	player = std::make_shared<Entity>(PLAYER_SIZE, PLAYER_COLOR);

	player->SetPosition(PLAYER_STARTING_POS_X, PLAYER_STARTING_POS_Y);
	player->AddCollisionFromCenter(0, 0, PLAYER_COLLISION_SIZE);

	playerHP = PLAYER_HP;
	playerScore = 0;
}

void Level::MovePlayer(){
	player->Update(Vector2Zero());

	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)){
		stateManager->GetSharedContext()->audio->Play("movement");
	}

	if (IsKeyDown(KEY_UP) && player->GetPosition().y >= 0) player->Update(PLAYER_MOVE_UP);
	if (IsKeyDown(KEY_DOWN) && player->GetPosition().y <= stateManager->GetSharedContext()->window->GetInternalSize().y) player->Update(PLAYER_MOVE_DOWN);
	if (IsKeyDown(KEY_LEFT) && player->GetPosition().x >= 0) player->Update(PLAYER_MOVE_LEFT);
	if (IsKeyDown(KEY_RIGHT) && player->GetPosition().x <= stateManager->GetSharedContext()->window->GetInternalSize().x) player->Update(PLAYER_MOVE_RIGHT);
}

void Level::CheckPlayerCollision(){
	for (auto i: enemyList){
		if (Entity::CheckCollision(player, i)){
			i->ToggleCollisionVisibility();
			stateManager->GetSharedContext()->audio->Play("playerHit");
			playerHP--;
		}
	}

	if (playerHP > 0) return;

	isPaused = true;
	isGameOver = true;
}

void Level::BoundCheck(){
	Background frontBG = backgrounds.front();
	std::shared_ptr<Entity> frontEnemy = enemyList.front();

	if (!frontEnemy) return;

	if (frontBG.rec.x + frontBG.rec.width < 0) backgrounds.pop_front();
	if (frontEnemy->GetPosition().x + ENEMY_COLLISION_SIZE < 0) {
		enemyList.pop_front();
		stateManager->GetSharedContext()->audio->Play("scoreTick");
		playerScore++;
	}
}

void Level::SpawnEnemy(){
	std::shared_ptr<Entity> enemy;
	int type = GetRandomValue(1, TOTAL_ENEMY_TYPE);

	switch (type){
		case 1: enemy = CreateTypeOneEnemy(); break;
		case 2: enemy = CreateTypeTwoEnemy(); break;
		case 3: enemy = CreateTypeThreeEnemy(); break;
		default: break;
	}

	enemyList.push_back(enemy);
}

void Level::SpawnBackground(){
	int colorValue = GetRandomValue(BACKGROUND_MIN_COLOR, BACKGROUND_MAX_COLOR);
	int sizeValue = GetRandomValue(BACKGROUND_MIN_SIZE, BACKGROUND_MAX_SIZE);

	Background bg = (Background){(Rectangle){SPAWN_AREA, GetRandomValue(0, 960), sizeValue, sizeValue}, (Color){colorValue, colorValue, colorValue, 255}};
	
	backgrounds.push_back(bg);
}

void Level::MoveBackground(int speed){
	for (auto &i: backgrounds) i.rec.x += speed;
}

void Level::ResetIntroBar(){
	topBarRec.rec = (Rectangle){0, 0, stateManager->GetSharedContext()->window->GetInternalSize().x, stateManager->GetSharedContext()->window->GetInternalSize().y/4};
	botBarRec.rec = (Rectangle){0, stateManager->GetSharedContext()->window->GetInternalSize().y*3/4, stateManager->GetSharedContext()->window->GetInternalSize().x, stateManager->GetSharedContext()->window->GetInternalSize().y/4};
	
}

std::shared_ptr<Entity> CreateTypeOneEnemy(){
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>(ENEMY_MAINBODY_SIZE, ENEMY_COLOR);
	enemy->SetPosition(SPAWN_AREA, GetRandomValue(0, 960));
	enemy->SetCollisionColor(ENEMY_COLLISION_COLOR);
	enemy->AddSideBodyFromCenter(-ENEMY_MAINBODY_SIZE, 0, ENEMY_SIDEBODY_SIZE);
	enemy->AddCollisionFromCenter(TYPE_ONE_COLLISION_DISTANCE, 0, ENEMY_COLLISION_SIZE);


	return enemy;
}

std::shared_ptr<Entity> CreateTypeTwoEnemy(){
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>(ENEMY_MAINBODY_SIZE, ENEMY_COLOR);
	enemy->SetPosition(SPAWN_AREA, GetRandomValue(0, 960));
	enemy->SetCollisionColor(ENEMY_COLLISION_COLOR);
	enemy->AddSideBodyFromCenter(0, ENEMY_MAINBODY_SIZE, ENEMY_SIDEBODY_SIZE);
	enemy->AddSideBodyFromCenter(0, -ENEMY_MAINBODY_SIZE, ENEMY_SIDEBODY_SIZE);
	enemy->AddCollisionFromCenter(0, TYPE_TWO_COLLISION_DISTANCE, ENEMY_COLLISION_SIZE);
	enemy->AddCollisionFromCenter(0, -TYPE_TWO_COLLISION_DISTANCE, ENEMY_COLLISION_SIZE);

	return enemy;
}

std::shared_ptr<Entity> CreateTypeThreeEnemy(){
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>(ENEMY_MAINBODY_SIZE, ENEMY_COLOR);
	enemy->SetPosition(SPAWN_AREA, GetRandomValue(0, 960));
	enemy->SetCollisionColor(ENEMY_COLLISION_COLOR);
	enemy->AddSideBodyFromCenter(-ENEMY_MAINBODY_SIZE, 0, ENEMY_SIDEBODY_SIZE);
	enemy->AddSideBodyFromCenter(-ENEMY_MAINBODY_SIZE, ENEMY_MAINBODY_SIZE, ENEMY_SIDEBODY_SIZE);
	enemy->AddSideBodyFromCenter(-ENEMY_MAINBODY_SIZE, -ENEMY_MAINBODY_SIZE, ENEMY_SIDEBODY_SIZE);
	enemy->AddCollisionFromCenter(TYPE_THREE_COLLISION_DISTANCE, 0, ENEMY_COLLISION_SIZE);
	enemy->AddCollisionFromCenter(TYPE_THREE_COLLISION_DISTANCE, TYPE_THREE_COLLISION_DISTANCE, ENEMY_COLLISION_SIZE);
	enemy->AddCollisionFromCenter(TYPE_THREE_COLLISION_DISTANCE, -TYPE_THREE_COLLISION_DISTANCE, ENEMY_COLLISION_SIZE);


	return enemy;
}