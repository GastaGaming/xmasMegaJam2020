#include "enemy.h"

Enemy::Enemy(Context* context) : LogicComponent(context)
{
	timeToDetect = 3.0f;
	detectionTimer = 0.0f;
	patrolSpeed = 3.0f;
	playerSeen = false;
	waypoints = new Vector<Vector2>();
	oldWaypointIndex = 0;
	currentWaypointIndex = 0;
	waypointTravelledDistance = 0.0f;
	distanceToNextWaypoint = 0.0f;
	directionToNextWaypoint = Vector2::ZERO;
}

void Enemy::ApplyAttributes()
{
}

void Enemy::SubscribeToEvents()
{
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Enemy, Update));
	SubscribeToEvent(E_PHYSICSBEGINCONTACT2D, URHO3D_HANDLER(Enemy, NodeCollision));
}

void Enemy::Init()
{
	SubscribeToEvents();
	
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	//spriteComponent = node_->CreateComponent<StaticSprite2D>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("xmash2D/Petteri.png");
	//spriteComponent->SetSprite(sprite);
	AnimationSet2D* petteriSet = cache->GetResource<AnimationSet2D>("xmash2D/Petteri/Petteri.scml");

	spriteComponent = node_->CreateComponent<AnimatedSprite2D>();
	spriteComponent->SetAnimationSet(petteriSet);
	spriteComponent->SetAnimation("Idle");
	spriteComponent->SetLayer(3); // Put character over tile map (which is on layer 0) and over Orcs (which are on layer 2)
	spriteComponent->SetEnabled(true);

	waypoints->Push(Vector2(node_->GetPosition().x_, node_->GetPosition().y_ + 0.0f));
	waypoints->Push(Vector2(node_->GetPosition().x_ + 10.0f, node_->GetPosition().y_ + 0.0f));
	waypoints->Push(Vector2(node_->GetPosition().x_ + 10.0f, node_->GetPosition().y_ + 10.0f));
	waypoints->Push(Vector2(node_->GetPosition().x_ + 0.0f, node_->GetPosition().y_ + 10.0f));

	//node_->SetPosition2D(waypoints->At(currentWaypointIndex));
	nextWaypoint();

	RigidBody2D* rigidBody = node_->CreateComponent<RigidBody2D>();
	rigidBody->SetBodyType(BT_KINEMATIC);
	rigidBody->SetGravityScale(0.f);

	CollisionBox2D* playerHitBox = node_->CreateComponent<CollisionBox2D>();
	// Set size
	playerHitBox->SetSize(sprite->GetTexture()->GetWidth() * 0.01f, sprite->GetTexture()->GetHeight() * 0.01f);

	laiffi = 3;
}

void Enemy::Update(StringHash eventType, VariantMap& eventData)
{
	float timeStep = eventData[Update::P_TIMESTEP].GetFloat();

	bool reached = moveTowardsNext(timeStep);
	if (reached)
	{
		nextWaypoint();
	}
}

void Enemy::RegisterObject(Context* context)
{
	context->RegisterFactory<Enemy>();
}

bool Enemy::moveTowardsNext(float timeStep)
{
	Vector2 moveDelta = directionToNextWaypoint * (patrolSpeed * timeStep);

	if (waypointTravelledDistance + moveDelta.Length() > distanceToNextWaypoint)
	{
		node_->SetPosition2D(waypoints->At(currentWaypointIndex));
		return true;
	}
	else
	{
		waypointTravelledDistance += moveDelta.Length();
		node_->Translate2D(moveDelta, TS_WORLD);
	}

	return false;
}

void Enemy::nextWaypoint()
{
	oldWaypointIndex = currentWaypointIndex;
	if (currentWaypointIndex >= waypoints->Size() -1)
	{
		currentWaypointIndex = 0;
	}
	else
	{
		currentWaypointIndex++;
	}

	distanceToNextWaypoint = (waypoints->At(currentWaypointIndex) - waypoints->At(oldWaypointIndex)).Length();
	directionToNextWaypoint = (waypoints->At(currentWaypointIndex) - waypoints->At(oldWaypointIndex)).Normalized();
	waypointTravelledDistance = 0.0f;
}

void Enemy::NodeCollision(StringHash eventType, VariantMap& eventData)
{
	//URHO3D_LOGINFO("Collision detected");
	Node* otherNode = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
	Node* antavaNode = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());
	//URHO3D_LOGINFO(otherNode->GetName());
	if (antavaNode->GetName() == "Snowball" && otherNode->GetName() == "Petteri")
	{
		URHO3D_LOGINFO("AI MUN POLVI");
		laiffi -= 1;
	}

	if (laiffi <=0)
	{
		LifeIsGone();
	}
}

void Enemy::LifeIsGone()
{
	node_->Remove();
}
