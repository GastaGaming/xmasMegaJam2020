#pragma once
#include <Urho3D/Urho3DAll.h>
#include <string>

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
	

	bool Test = true;

	// Construct
	explicit Player(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Perform post-load after deserialization. Acquire the components from the scene nodes.
	void ApplyAttributes() override;
	/// Handle physics world update. Called by LogicComponent base class.
	void Update(float timeStep) override;
	void PostUpdate(float timeStep) override;
	/// Init player. Make references to systems etc. Called by the application.
	virtual void Init(Scene* scene, Camera* sceneCamera);

	void Snowball();

private:
	Vector3 moveDir_ = Vector3(0,0,0);
	Vector3 launchPoint_ = Vector3(0, 0);
};

