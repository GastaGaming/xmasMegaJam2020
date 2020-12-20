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
	//Pit�� s��t�� kokoa collisionia varte jossain kohtaa
	//Node* snowBall = scene_->CreateChild("Snowball");
	//snowBall->SetPosition(node_->GetPosition() + launchDir_.Normalized() * 5.f);//Magic number spawn distance
	
	SharedPtr<RigidBody2D> rigidBody(node_->CreateComponent<RigidBody2D>());
	rigidBody->SetBodyType(BT_DYNAMIC);
	rigidBody->SetGravityScale(0.f);

	SharedPtr<StaticSprite2D> staticSprite(node_->CreateComponent<StaticSprite2D>());
	staticSprite->SetSprite(cache_->GetResource<Sprite2D>("xmash2D/SnowBoll.png"));

	SharedPtr<CollisionBox2D> collBox(node_->CreateComponent<CollisionBox2D>());
	collBox->SetSize(node_->GetScale2D()); //Pit�isi sovittaa noden kokoiseksi
	

	rigidBody->ApplyLinearImpulse(launchDir_.Normalized() * launchSpeed, Vector2::ZERO, true);

	lifeTimeTmr.Reset();
	stillAlive = true;

	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Snowball, Update));
	//SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Snowball, PostUpdate));
}

void Snowball::Update(StringHash eventType, VariantMap& eventData)
{
	float timeStep = eventData[Update::P_TIMESTEP].GetFloat();
	framecount_++;
	time_ += timeStep;

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
	node_->Remove();
}