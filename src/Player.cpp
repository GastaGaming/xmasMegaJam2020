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
	if (input->GetKeyDown(KEY_I))
		node_->Translate(Vector3(0, 0, 1) * timeStep);
	if (input->GetKeyDown(KEY_K))
		node_->Translate(Vector3(0, 0, -1) * timeStep);
	if (input->GetKeyDown(KEY_J))
		node_->Translate(Vector3(-1, 0, 0) * timeStep);
	if (input->GetKeyDown(KEY_L))
		node_->Translate(Vector3(1, 0, 0) * timeStep);
}

void Player::Init(Scene* scene)
{
	// This function is called only from the main program when initially creating the vehicle, not on scene load
	auto* cache = GetSubsystem<ResourceCache>();
	Scene* scene_ = scene;

	input = scene_->GetSubsystem<Input>();

	StaticModel* playerBoxObject = node_->CreateComponent<StaticModel>();
	playerBoxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
	playerBoxObject->SetMaterial(cache->GetResource<Material>("Materials/Water.xml"));
	playerBoxObject->SetCastShadows(true);
	/*auto* hullObject = player_->CreateComponent<StaticModel>();
	auto* hullShape = player_->CreateComponent<CollisionShape>();

	player_->SetScale(Vector3(3, 3, 3));
	hullObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
	hullObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));
	hullObject->SetCastShadows(true);
	hullShape->SetBox(Vector3::ONE);*/
	camera = node_->CreateChild("Camera");
	Camera* cameraComponent = camera->CreateComponent<Camera>();
	cameraComponent->SetFarClip(2000);
	/*cameraComponent->SetOrthographic(true);*/
}
