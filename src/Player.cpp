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
	//SharedPtr<Node> spriteNode(scene_->CreateChild("StaticSprite2D"));
	//node_->AddChild(spriteNode);
	//spriteNode->SetScale2D(Vector2(1, 1));

	StaticSprite2D* staticSprite = node_->CreateComponent<StaticSprite2D>();
	staticSprite->SetSprite(cache_->GetResource<Sprite2D>("xmash2D/GreenThing.png"));

	CollisionBox2D* playerHitBox = node_->CreateComponent<CollisionBox2D>();
	// Set size
	playerHitBox->SetSize(node_->GetScale2D());

	launchDir_.x_ = node_->GetScale2D().x_;
	/*StaticModel* playerBoxObject = node_->CreateComponent<StaticModel>();
	playerBoxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
	playerBoxObject->SetMaterial(cache->GetResource<Material>("Materials/Water.xml"));
	playerBoxObject->SetCastShadows(true);*/
	/*auto* hullObject = player_->CreateComponent<StaticModel>();
	auto* hullShape = player_->CreateComponent<CollisionShape>();

	player_->SetScale(Vector3(3, 3, 3));
	hullObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
	hullObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
	hullObject->SetCastShadows(true);
	hullShape->SetBox(Vector3::ONE);*/
	/*cameraComponent->SetOrthographic(true);*/
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Player, Update));
	SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Player, PostUpdate));
}

//Handle physics update
void Player::Update(StringHash eventType, VariantMap& eventData)
{
	float timeStep = eventData[Update::P_TIMESTEP].GetFloat();
	framecount_++;
	time_ += timeStep;

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

	if (!moveDir_.Equals(Vector2::ZERO))
	{
		node_->Translate(moveDir_.Normalized() * movementSpeed * timeStep);
		launchDir_ = moveDir_;
	}

	if (input_->GetKeyDown(KEY_SPACE))
	{
		if (!firing_)
		{
			firing_ = true;
			ThrowProjectile();
		}
	}

	if (tmr.GetMSec(false) > RoF_)
	{
		firing_ = false;
		tmr.Reset();
	}

	/*if (projectileUpdates.Size()>0)
	{
		for (size_t i = 0; i < projectileUpdates.Size(); i++)
		{
			
		}
	}*/
}

void Player::PostUpdate(StringHash eventType, VariantMap& eventData)
{
	//Follow player with camera
	if (Test)
	{
		camera_->GetNode()->SetPosition(Vector3(node_->GetPosition().x_, node_->GetPosition().y_, -30.0f));
		Test = false;
	}

}

void Player::ThrowProjectile()
{
	//Pitää säätää kokoa collisionia varte jossain kohtaa
	Node* snowBall = scene_->CreateChild("Snowball");
	snowBall->SetPosition(node_->GetPosition()+launchDir_.Normalized()*5.f);//Magic number spawn distance
	Snowball* snowBallComp = snowBall->CreateComponent<Snowball>();
	snowBallComp->Init(scene_, launchDir_);

	//projectileUpdates.Push()
	////auto* rigidBody = snowBall->CreateComponent<RigidBody2D>();
	//rigidBody->SetBodyType(BT_DYNAMIC);
	//rigidBody->SetGravityScale(0.f);

	//auto* staticSprite = snowBall->CreateComponent<StaticSprite2D>();
	//staticSprite->SetSprite(cache_->GetResource<Sprite2D>("xmash2D/SnowBoll.png"));

	//auto* collBox = snowBall->CreateComponent<CollisionBox2D>();
	//collBox->SetSize(node_->GetScale2D()); //Pitäisi sovittaa noden kokoiseksi

	//rigidBody->ApplyLinearImpulse(launchDir_.Normalized() * launchSpeed, Vector2::ZERO, true);

}

