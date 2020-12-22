#pragma once
#include <Urho3D/Urho3DAll.h>
class WinnerTrigger : public LogicComponent
{
	URHO3D_OBJECT(WinnerTrigger, LogicComponent)
public:
	// Construct
	explicit WinnerTrigger(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Perform post-load after deserialization. Acquire the components from the scene nodes.
	void ApplyAttributes() override;
	void SubscribeToEvents();
	/// Init player. Make references to systems etc. Called by the application.
	virtual void Init();
	void NodeCollision(StringHash eventType, VariantMap& eventData);
private:
};