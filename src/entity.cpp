#include "entity.hpp"

#define ENTITY_START_POS -100

Entity::Entity(int main_size, Color color){
	Init(main_size, color);
}

Entity::~Entity(){
	
}

void Entity::Update(Vector2 speed){
	if (!isActive) return;

	position = Vector2Add(position, speed);

	UpdateRectanglePos(speed);
}

void Entity::Render(){
	DrawRectangleRec(mainBody, color);
	for (auto i: sideBody) DrawRectangleRec(i, color);

	if (!isCollisionVisible) return;

	for (auto i: collisionRec) DrawRectangleRec(i, collisionColor);
}

void Entity::SetCollisionColor(Color color){
	collisionColor = color;
}

void Entity::SetPosition(int x, int y){
	position.x = x;
	position.y = y;

	mainBody.x = x - mainBody.width/2;
	mainBody.y = y - mainBody.height/2;
}

void Entity::AddSideBodyFromCenter(int x, int y, int size){
	Rectangle side = (Rectangle){(position.x + x) - size/2, (position.y + y) - size/2, size, size};

	sideBody.push_back(side);
}

void Entity::AddCollisionFromCenter(int x, int y, int size){
	Rectangle col = (Rectangle){position.x + x - size/2, position.y + y - size/2, size, size};

	collisionRec.push_back(col);
}

void Entity::ToggleCollisionVisibility(){
	isCollisionVisible = !isCollisionVisible;
}

const Vector2 Entity::GetPosition(){
	return position;
}

bool Entity::CheckCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2){
	for (auto i: e1->collisionRec){
		for (auto j: e2->collisionRec) {
			if (CheckCollisionRecs(i, j)) return true;
		}
	}

	return false;
}

void Entity::Init(int mainSize, Color col){
	mainBody = (Rectangle){ENTITY_START_POS, ENTITY_START_POS, mainSize, mainSize};

	color = col;
	isActive = true;
	isCollisionVisible = false;

}

void Entity::UpdateRectanglePos(Vector2 speed){
	mainBody.x += speed.x;
	mainBody.y += speed.y;

	for (auto& i : sideBody){
		i.x += speed.x;
		i.y += speed.y;
	}

	for (auto& i: collisionRec){
		i.x += speed.x;
		i.y += speed.y;
	}
}