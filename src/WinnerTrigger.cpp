#include "WinnerTrigger.h"
#include "Player.h"
WinnerTrigger::WinnerTrigger(Context* context) : LogicComponent(context)
{
}
void WinnerTrigger::RegisterObject(Context* context, Engine* engine)
{
	context->RegisterFactory<WinnerTrigger>();
	//engine_ = engine;
}
void WinnerTrigger::ApplyAttributes()
{
}
void WinnerTrigger::SubscribeToEvents()
{
	SubscribeToEvent(E_PHYSICSBEGINCONTACT2D, URHO3D_HANDLER(WinnerTrigger, NodeCollision));
}
void WinnerTrigger::Init()
{
	SubscribeToEvents();
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("xmash2D/Petteri.png");
	RigidBody2D* rigidBody = node_->CreateComponent<RigidBody2D>();
	rigidBody->SetBodyType(BT_DYNAMIC);
	rigidBody->SetGravityScale(0.f);

	CollisionBox2D* playerHitBox = node_->CreateComponent<CollisionBox2D>();
	//playerHitBox->SetTrigger(true);
	// Set size
	playerHitBox->SetSize(sprite->GetTexture()->GetWidth() * 0.01f, sprite->GetTexture()->GetHeight() * 0.01f);
}

void WinnerTrigger::NodeCollision(StringHash eventType, VariantMap& eventData)
{
	Node* nodeA = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
	Node* nodeB = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());
	String nodeAName = nodeA->GetName();
	String nodeBName = nodeA->GetName();

	if (nodeA->GetComponent<WinnerTrigger>() && nodeB->GetComponent<Player>())
	{
		URHO3D_LOGINFO(nodeAName +"xxxxx" + nodeBName);
		victory = true;
	}

}