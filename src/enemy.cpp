#include "enemy.h"

Enemy::Enemy(Context* context) : LogicComponent(context)
{
	SetUpdateEventMask(USE_UPDATE);
	timeToDetect = 3.0f;
	detectionTimer = 0.0f;
	playerSeen = false;
}

void Enemy::ApplyAttributes()
{
}

void Enemy::Start()
{
	
}

void Enemy::Update(float timeStep)
{
}

void Enemy::RegisterObject(Context* context)
{
	context->RegisterFactory<Enemy>();
}
