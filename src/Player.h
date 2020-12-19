#pragma once
#include <Urho3D/Urho3DAll.h>
#include <string>

class Player : public LogicComponent
{
	URHO3D_OBJECT(Player, LogicComponent)

public:

	SharedPtr<Node> player_;
	float startFloat = 0;

	Input* input = nullptr;
	Node* camera = nullptr;

	// Construct
	explicit Player(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Perform post-load after deserialization. Acquire the components from the scene nodes.
	void ApplyAttributes() override;
	/// Handle physics world update. Called by LogicComponent base class.
	//void FixedUpdate(float timeStep) override;
	void Update(float timeStep) override;
	/// Initialize the vehicle. Create rendering and physics components. Called by the application.
	virtual void Init(Scene* scene);

private:

};

