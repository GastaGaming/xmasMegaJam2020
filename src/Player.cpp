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

//Handle physics update
void Player::Update(float timeStep)
{
	/*if (input->GetKeyDown(KEY_SHIFT))
		MOVE_SPEED *= 10;*/
	if (input_->GetKeyDown(KEY_I))
		node_->Translate(Vector3(0, 10, 0) * timeStep);
	if (input_->GetKeyDown(KEY_K))
		node_->Translate(Vector3(0, -10, 0) * timeStep);
	if (input_->GetKeyDown(KEY_J))
		node_->Translate(Vector3(-10, 0, 0) * timeStep);
	if (input_->GetKeyDown(KEY_L))
		node_->Translate(Vector3(10, 0, 0) * timeStep);
}

void Player::PostUpdate(float timeStep)
{
	//Follow player with camera
	if (Test)
	{
		camera_->GetNode()->SetPosition(Vector3(node_->GetPosition().x_, node_->GetPosition().y_, -30.0f));
		Test = false;
	}

}

void Player::Init(Scene* scene, Camera* sceneCamera)
{
	// This function is called only from the main program when initially creating the vehicle, not on scene load
	auto* cache = GetSubsystem<ResourceCache>();
	Scene* scene_ = scene;

	input_ = scene_->GetSubsystem<Input>();
	camera_ = sceneCamera;

	//Get start position
	//Get art
	SharedPtr<Node> spriteNode(scene_->CreateChild("StaticSprite2D"));
	node_->AddChild(spriteNode);
	StaticSprite2D* staticSprite = spriteNode->CreateComponent<StaticSprite2D>();
	staticSprite->SetSprite(cache->GetResource<Sprite2D>("xmash2D/GreenThing.png"));

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
}
