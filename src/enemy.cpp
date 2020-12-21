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
}

void Enemy::Init()
{
	SubscribeToEvents();
	
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	spriteComponent = node_->CreateComponent<StaticSprite2D>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("xmash2D/Petteri.png");
	spriteComponent->SetSprite(sprite);

	waypoints->Push(Vector2(0.0f, 0.0f));
	waypoints->Push(Vector2(4.0f, 0.0f));
	waypoints->Push(Vector2(4.0f, 4.0f));
	waypoints->Push(Vector2(0.0f, 4.0f));

	node_->SetPosition2D(waypoints->At(currentWaypointIndex));
	nextWaypoint();
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
