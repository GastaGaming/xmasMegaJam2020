#pragma once
#include <Urho3D/Urho3DAll.h>
#include <string>

class Enemy : public LogicComponent
{
	URHO3D_OBJECT(Enemy, LogicComponent)
public:
	explicit Enemy(Context* context);

	void ApplyAttributes() override;

	void Start() override;

	void Update(float timeStep) override;

	static void RegisterObject(Context* context);

private:
	float timeToDetect;
	bool playerSeen;
	float detectionTimer;
};