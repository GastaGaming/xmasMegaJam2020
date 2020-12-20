#pragma once
#include <Urho3D/Urho3DAll.h>
#include <string>

class Snowball : public LogicComponent
{
	URHO3D_OBJECT(Snowball, LogicComponent)

public:
	int framecount_;
	float time_;

public:
	// Construct
	explicit Snowball(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Perform post-load after deserialization. Acquire the components from the scene nodes.
	/*void ApplyAttributes() override;*/
	/// Handle physics world update. Called by LogicComponent base class.
	void Update(StringHash eventType, VariantMap& eventData);
	//void PostUpdate(float timeStep) override;
	/// Init player. Make references to systems etc. Called by the application.
	virtual void Init(Scene* scene_, Vector2 launchDir_);
private:
	void TimesUp();

private:
	Timer lifeTimeTmr = Timer();

	bool stillAlive = false;
	float lifeTime = 500; //Milliseconds
	float launchSpeed = 10.f;
};

