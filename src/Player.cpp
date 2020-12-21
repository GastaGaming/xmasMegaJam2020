#include "Player.h"
Player::Player(Context* context) : LogicComponent(context)
{
	// Only the physics update event is needed: unsubscribe from the rest for optimization
	SetUpdateEventMask(USE_FIXEDUPDATE);
}

void Player::RegisterObject(Context* context)
{
	context->RegisterFactory<Player>();
}

void Player::ApplyAttributes()
{
	// This function is called on each Serializable after the whole scene has been loaded. Reacquire wheel nodes from ID's
	// as well as all required physics components
	Scene* scene = GetScene();
}

void Player::Init(Scene* scene, Camera* sceneCamera)
{
	// This function is called only from the main program when initially creating the vehicle, not on scene load
	cache_ = GetSubsystem<ResourceCache>();
	scene_ = scene;

	input_ = scene_->GetSubsystem<Input>();
	camera_ = sceneCamera;

	//Get start position
	
	//Get art
	//StaticSprite2D* staticSprite = node_->CreateComponent<StaticSprite2D>();
	//staticSprite->SetSprite(cache_->GetResource<Sprite2D>("xmash2D/GreenThing.png"));

	animeSetTonttu = cache_->GetResource<AnimationSet2D>("xmash2D/Gnome/Gnome.scml");
	animeSeteGreenThing = cache_->GetResource<AnimationSet2D>("xmash2D/GreenThing/GreenThing.scml");


	animeSpriteTonttu = node_->CreateComponent<AnimatedSprite2D>();
	animeSpriteTonttu->SetAnimationSet(animeSetTonttu);
	animeSpriteTonttu->SetAnimation("Idle");
	animeSpriteTonttu->SetLayer(3); // Put character over tile map (which is on layer 0) and over Orcs (which are on layer 2)
	animeSpriteTonttu->SetEnabled(true);

	animeSpriteGreenThing = node_->CreateComponent<AnimatedSprite2D>();
	animeSpriteGreenThing->SetAnimationSet(animeSeteGreenThing);
	animeSpriteGreenThing->SetAnimation("Idle");
	animeSpriteGreenThing->SetLayer(3); // Put character over tile map (which is on layer 0) and over Orcs (which are on layer 2)
	animeSpriteGreenThing->SetEnabled(false);


	RigidBody2D* rigidBody = node_->CreateComponent<RigidBody2D>();
	rigidBody->SetBodyType(BT_DYNAMIC);
	rigidBody->SetGravityScale(0.f);


	CollisionBox2D* playerHitBox = node_->CreateComponent<CollisionBox2D>();
	// Set size
	playerHitBox->SetSize(animeSpriteTonttu->GetSprite()->GetTexture()->GetWidth()*0.01f, animeSpriteTonttu->GetSprite()->GetTexture()->GetHeight() * 0.01f);

	launchDir_.x_ = node_->GetScale2D().x_;

	//KOLINATESTI
	Node* loota = scene_->CreateChild("LOOTA");
	RigidBody2D* body2 = loota->CreateComponent<RigidBody2D>();
	body2->SetBodyType(BT_STATIC);
	body2->SetGravityScale(0.f);
	CollisionBox2D* box2 = loota->CreateComponent<CollisionBox2D>();
	box2->SetSize(Vector2::ONE);

	//LOPPU

	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Player, Update));
	SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Player, PostUpdate));
	SubscribeToEvent(E_NODECOLLISIONSTART, URHO3D_HANDLER(Player, NodeCollision));

}

//Handle physics update
void Player::Update(StringHash eventType, VariantMap& eventData)
{
	float timeStep = eventData[Update::P_TIMESTEP].GetFloat();
	moveDir_ = Vector2::ZERO;
	float movementSpeed = 5.0f;
	/*if (input->GetKeyDown(KEY_SHIFT))
		MOVE_SPEED *= 10;*/
	if (input_->GetKeyDown(KEY_W))
		moveDir_ += Vector2::UP;
	if (input_->GetKeyDown(KEY_S))
		moveDir_ += Vector2::DOWN;
	if (input_->GetKeyDown(KEY_A))
		moveDir_ += Vector2::LEFT;
	if (input_->GetKeyDown(KEY_D))
		moveDir_ += Vector2::RIGHT;

	AnimatedSprite2D* animatedSprite = node_->GetComponent<AnimatedSprite2D>();
	if (node_->GetComponent<AnimatedSprite2D>()->IsEnabled() == true && animatedSprite != animeSpriteTonttu)
	{
		animatedSprite = animeSpriteGreenThing;
	}

	if (!moveDir_.Equals(Vector2::ZERO))
	{
		node_->Translate(moveDir_.Normalized() * movementSpeed * timeStep);
		launchDir_ = moveDir_;
		if(animatedSprite->GetAnimation() != "Walk")
			animatedSprite->SetAnimation("Walk");
	}
	else
	{
		if (animatedSprite->GetAnimation() != "Idle")
			animatedSprite->SetAnimation("Idle");
	}

	if (input_->GetKeyDown(KEY_SPACE))
	{
		if (!firing_)
		{
			firing_ = true;
			ThrowProjectile();
		}
	}

	if (input_->GetKeyDown(KEY_F))
	{
		if (animatedSprite == animeSpriteTonttu)
		{
			animeSpriteTonttu->SetEnabled(false);
			animeSpriteGreenThing->SetEnabled(true);
		}
		else
		{
			animeSpriteTonttu->SetEnabled(true);
			animeSpriteGreenThing->SetEnabled(false);
		}
	}

	if (tmr.GetMSec(false) > RoF_)
	{
		firing_ = false;
		tmr.Reset();
	}
}

void Player::PostUpdate(StringHash eventType, VariantMap& eventData)
{
	//Follow player with camera
	if (Test)
	{
		camera_->GetNode()->SetPosition(Vector3(node_->GetPosition().x_, node_->GetPosition().y_, -30.0f));
		//Test = false;
	}

}

void Player::ThrowProjectile()
{
	//Pitää säätää kokoa collisionia varte jossain kohtaa
	Node* snowBall = scene_->CreateChild("Snowball");
	snowBall->SetPosition(node_->GetPosition()+launchDir_.Normalized()*5.f);//Magic number spawn distance
	Snowball* snowBallComp = snowBall->CreateComponent<Snowball>();
	snowBallComp->Init(scene_, launchDir_);

}

void Player::NodeCollision(StringHash eventType, VariantMap& eventData)
{
	URHO3D_LOGINFO("APUA");
	Node* otherNode = static_cast<Node*>(eventData["OtherNode"].GetPtr());
	RigidBody2D* otherBody = static_cast<RigidBody2D*>(eventData["OtherBody"].GetPtr());
	VectorBuffer contacts = eventData["Contacts"].GetBuffer();
	if (otherNode)
	{

	}

}

