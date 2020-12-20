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

void Enemy::SubscribeToEvents()
{
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Enemy, Update));
}

void Enemy::Init()
{
	SubscribeToEvents();
	
	//Load sprite
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	
	//Create sprite renderer
	StaticSprite2D* spriteComponent = node_->CreateComponent<StaticSprite2D>();
	
	//Set sprite
	Sprite2D* sprite = cache->GetResource<Sprite2D>("xmash2D/Petteri.png");
	spriteComponent->SetSprite(sprite);

	node_->SetPosition2D(Vector2::ZERO);
}

void Enemy::Update(StringHash eventType, VariantMap& eventData)
{
	float timeStep = eventData[Update::P_TIMESTEP].GetFloat();

	//node_->SetPosition2D(node_->GetPosition2D() + Vector2((5.0f * timeStep), 0.0f));
	//node_->Rotate2D(10.0f * timeStep);
}

void Enemy::RegisterObject(Context* context)
{
	context->RegisterFactory<Enemy>();
}
