#include "WinnerTrigger.h"
WinnerTrigger::WinnerTrigger(Context* context) : LogicComponent(context)
{
}
void WinnerTrigger::RegisterObject(Context* context)
{
	context->RegisterFactory<WinnerTrigger>();
}
void WinnerTrigger::ApplyAttributes()
{
}
void WinnerTrigger::SubscribeToEvents()
{
	SubscribeToEvent(E_NODECOLLISIONSTART, URHO3D_HANDLER(WinnerTrigger, NodeCollision));
}
void WinnerTrigger::Init()
{
	//SubscribeToEvent(E_NODECOLLISIONSTART, URHO3D_HANDLER(WinnerTrigger, NodeCollision));
}

void WinnerTrigger::NodeCollision(StringHash eventType, VariantMap& eventData)
{
	Node* otherNode = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
	RigidBody2D* otherBody = static_cast<RigidBody2D*>(eventData["OtherBody"].GetPtr());
	VectorBuffer contacts = eventData["Contacts"].GetBuffer();
	if (otherNode)
	{
		URHO3D_LOGINFO("WOITIT PELIN");
	}

}