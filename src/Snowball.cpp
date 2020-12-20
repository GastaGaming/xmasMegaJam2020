#include "Snowball.h"

Snowball::Snowball(Context* context) : LogicComponent(context)
{
	// Only the physics update event is needed: unsubscribe from the rest for optimization
	SetUpdateEventMask(USE_FIXEDUPDATE);
}

void Snowball::RegisterObject(Context* context)
{
	context->RegisterFactory<Snowball>();
}

void Snowball::Init(Scene* scene_, Vector2 launchDir_)
{
	ResourceCache* cache_ = GetSubsystem<ResourceCache>();
	//Pitää säätää kokoa collisionia varte jossain kohtaa
	//Node* snowBall = scene_->CreateChild("Snowball");
	//snowBall->SetPosition(node_->GetPosition() + launchDir_.Normalized() * 5.f);//Magic number spawn distance

	auto* rigidBody = node_->CreateComponent<RigidBody2D>();
	rigidBody->SetBodyType(BT_DYNAMIC);
	rigidBody->SetGravityScale(0.f);

	auto* staticSprite = node_->CreateComponent<StaticSprite2D>();
	staticSprite->SetSprite(cache_->GetResource<Sprite2D>("xmash2D/SnowBoll.png"));

	auto* collBox = node_->CreateComponent<CollisionBox2D>();
	collBox->SetSize(node_->GetScale2D()); //Pitäisi sovittaa noden kokoiseksi

	rigidBody->ApplyLinearImpulse(launchDir_.Normalized() * launchSpeed, Vector2::ZERO, true);

	lifeTimeTmr.Reset();
	stillAlive = true;
}

void Snowball::Update(float timeStep)
{
	if (stillAlive)
	{
		if (lifeTimeTmr.GetMSec(false) > lifeTime)
		{
			TimesUp();
		}
	}
}

//void Snowball::PostUpdate(float timeStep)
//{
//
//}

void Snowball::TimesUp()
{
	Vector<SharedPtr<Component>> comps = node_->GetComponents();
	node_->~Node();
}