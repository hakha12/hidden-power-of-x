#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "common.hpp"

class Entity {
	public:
		Entity(int mainSize, Color color);
		~Entity();

		void Update(Vector2 speed);
		void Render();

		void SetCollisionColor(Color color);
		void SetPosition(int x, int y);
		void AddSideBodyFromCenter(int x, int y, int size);
		void AddCollisionFromCenter(int x, int y, int size);
		void ToggleCollisionVisibility();

		const Vector2 GetPosition();

		static bool CheckCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	
	private:
		void Init(int mainSize, Color col);
		void UpdateRectanglePos(Vector2 speed);

		Vector2 position;
		Rectangle mainBody;
		std::vector<Rectangle> sideBody;
		std::vector<Rectangle> collisionRec;
		Color color;
		Color collisionColor;
		bool isActive;
		bool isCollisionVisible;
};

#endif