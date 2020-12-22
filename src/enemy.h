#pragma once
//#include <Urho3D/Urho3DAll.h>
#include <Urho3D/Urho3DAll.h>
#include <string>

class Enemy : public LogicComponent
{
	URHO3D_OBJECT(Enemy, LogicComponent)
public:
	explicit Enemy(Context* context);

	void ApplyAttributes() override;

	void SubscribeToEvents();
	
	void Init();
	void Update(StringHash eventType, VariantMap& eventData);

	static void RegisterObject(Context* context);

private:
	bool moveTowardsNext(float timeStep);
	void nextWaypoint();
	
	AnimatedSprite2D* spriteComponent;
	float timeToDetect;
	bool playerSeen;
	float detectionTimer;
	float patrolSpeed;
	Vector<Vector2>* waypoints;

	Node* myNode_;

	int oldWaypointIndex;
	int currentWaypointIndex;
	float waypointTravelledDistance;
	float distanceToNextWaypoint;
	Vector2 directionToNextWaypoint;
};