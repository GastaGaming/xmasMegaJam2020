#pragma once
#include <Urho3D/Urho3DAll.h>
#include <string>

#include "Snowball.h"

class Player : public LogicComponent
{
	URHO3D_OBJECT(Player, LogicComponent)

public:
	SharedPtr<Node> player_;
	float startFloat = 0;

	Scene* scene_ = nullptr;
	ResourceCache* cache_ = nullptr;
	Input* input_ = nullptr;
	Camera* camera_ = nullptr;

	bool Test = true; //To check player movement until there is background

public:
	// Construct
	explicit Player(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Perform post-load after deserialization. Acquire the components from the scene nodes.
	void ApplyAttributes() override;
	/// Handle physics world update. Called by LogicComponent base class.
	void Update(StringHash eventType, VariantMap& eventData);
	void PostUpdate(StringHash eventType, VariantMap& eventData);
	/// Init player. Make references to systems etc. Called by the application.
	virtual void Init(Scene* scene, Camera* sceneCamera);

	void ThrowProjectile();
	void NodeCollision(StringHash eventType, VariantMap& eventData);

private:
	Timer tmr = Timer();
	/*Vector<SharedPtr<Snowball*>> projectileUpdates;*/

	Vector2 moveDir_ = Vector2(0,0);
	Vector2 launchDir_ = Vector2(0,0);

	bool firing_ = false;
	float RoF_ = 500;//Milliseconds
	float launchSpeed = 10.f;
};

