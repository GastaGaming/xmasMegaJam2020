#include <string>
#include <sstream>
//Just lazy fucker include whole urho
#include <Urho3D/Urho3DAll.h>
#include "enemy.h"
#include "TileMapLoader.h"
#include "Player.h"
#include "Snowball.h"

// Alternatively, you can replace all above Urho3D include statements by the single following one:
// #include <Urho3D/Urho3DAll.h>

using namespace Urho3D;
/**
* Using the convenient Application API we don't have
* to worry about initializing the engine or writing a main.
* You can probably mess around with initializing the engine
* and running a main manually, but this is convenient and portable.
*/
class MyApp : public Application
{
public:
    int framecount_;
    float time_;
    SharedPtr<Text> text_;
    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;
    
    TileMapLoader m_tileMapLoader;
    SharedPtr<Node> playerNode_;
    SharedPtr<Node> enemyNode_;

    bool drawPhysicsDebug_;

    /**
    * This happens before the engine has been initialized
    * so it's usually minimal code setting defaults for
    * whatever instance variables you have.
    * You can also do this in the Setup method.
    */
    MyApp(Context * context) : Application(context),framecount_(0),time_(0), drawPhysicsDebug_(false)
    {
    }

    /**
    * This method is called before the engine has been initialized.
    * Thusly, we can setup the engine parameters before anything else
    * of engine importance happens (such as windows, search paths,
    * resolution and other things that might be user configurable).
    */
    virtual void Setup()
    {
        // These parameters should be self-explanatory.
        // See http://urho3d.github.io/documentation/1.7/_main_loop.html
        // for a more complete list.
        #ifdef __DEBUG__ // Symbol '__DEBUG__' is usually defined when running cmake tool
        engineParameters_[EP_FULL_SCREEN]=false;  // (Urho3D::)EP_FULL_SCREEN = "Fullscreen"
        engineParameters_[EP_WINDOW_RESIZABLE]=true;
        #else
        engineParameters_[EP_FULL_SCREEN] = false;  // If we compile for release, then we can display in fullscreen
        #endif

        // Configuration not depending whether we compile for debug or release.
        engineParameters_[EP_WINDOW_WIDTH]=1280;
        engineParameters_[EP_WINDOW_HEIGHT]=720;
        GetSubsystem<Engine>()->SetMaxFps(999999);
        // All 'EP_' constants are defined in ${URHO3D_INSTALL}/include/Urho3D/Engine/EngineDefs.h file
        Player::RegisterObject(context_);
        Enemy::RegisterObject(context_);
        Snowball::RegisterObject(context_);
    }

    /**
    * This method is called after the engine has been initialized.
    * This is where you set up your actual content, such as scenes,
    * models, controls and what not. Basically, anything that needs
    * the engine initialized and ready goes in here.
    */
    virtual void Start()
    {

        
        // We will be needing to load resources.
        // All the resources used in this example comes with Urho3D.
        // If the engine can't find them, check the ResourcePrefixPath (see http://urho3d.github.io/documentation/1.7/_main_loop.html).
        ResourceCache* cache=GetSubsystem<ResourceCache>();

        // Let's setup a scene to render.
        scene_ = new Scene(context_);
        // Let the scene have an Octree component!
        scene_->CreateComponent<Octree>();
        scene_->CreateComponent<PhysicsWorld>();
        scene_->CreateComponent<PhysicsWorld2D>();
        // Let's add an additional scene component for fun.
        scene_->CreateComponent<DebugRenderer>();

        // We need a camera from which the viewport can render.
        cameraNode_ = scene_->CreateChild("Camera");
        Camera* camera = cameraNode_->CreateComponent<Camera>();
        //camera->SetFarClip(2000);
        camera->SetOrthographic(20);
        camera->SetOrthographic(true);
        // Now we setup the viewport. Of course, you can have more than one!
        Renderer* renderer=GetSubsystem<Renderer>();
        SharedPtr<Viewport> viewport(new Viewport(context_,scene_,camera));
        renderer->SetViewport(0,viewport);

        TileMapInfo2D info;
        m_tileMapLoader = *new TileMapLoader(cache);
        SharedPtr<Node> tileMapNode = m_tileMapLoader.CreateNodeFromTileMap(scene_, "xmash2D/Level/Level01.tmx", &info);
        TileMap2D* map = tileMapNode->GetComponent<TileMap2D>();

        String* asd = new String(map->GetTypeName()); 
        URHO3D_LOGINFO(*asd);

        //Setup player and pass camera to it, cause renderer wanted it first
        playerNode_ = scene_->CreateChild("Player");
        Player* playerComp = playerNode_->CreateComponent<Player>();
        playerComp->Init(scene_, camera);

        //Create test enemy
        enemyNode_ = scene_->CreateChild("TestEnemy");
        Enemy* enemyComp = enemyNode_->CreateComponent<Enemy>();
        enemyComp->Init();

        // We subscribe to the events we'd like to handle.
        // In this example we will be showing what most of them do,
        // but in reality you would only subscribe to the events
        // you really need to handle.
        // These are sort of subscribed in the order in which the engine
        // would send the events. Read each handler method's comment for
        // details.
        SubscribeToEvent(E_BEGINFRAME,URHO3D_HANDLER(MyApp,HandleBeginFrame));
        SubscribeToEvent(E_KEYDOWN,URHO3D_HANDLER(MyApp,HandleKeyDown));
        SubscribeToEvent(E_UPDATE,URHO3D_HANDLER(MyApp,HandleUpdate));
        SubscribeToEvent(E_POSTUPDATE,URHO3D_HANDLER(MyApp,HandlePostUpdate));
        SubscribeToEvent(E_RENDERUPDATE,URHO3D_HANDLER(MyApp,HandleRenderUpdate));
        SubscribeToEvent(E_POSTRENDERUPDATE,URHO3D_HANDLER(MyApp,HandlePostRenderUpdate));
        SubscribeToEvent(E_ENDFRAME,URHO3D_HANDLER(MyApp,HandleEndFrame));
    }

    /**
    * Good place to get rid of any system resources that requires the
    * engine still initialized. You could do the rest in the destructor,
    * but there's no need, this method will get called when the engine stops,
    * for whatever reason (short of a segfault).
    */
    virtual void Stop()
    {
    }

    /**
    * Every frame's life must begin somewhere. Here it is.
    */
    void HandleBeginFrame(StringHash eventType,VariantMap& eventData)
    {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }

    /**
    * Input from keyboard is handled here. I'm assuming that Input, if
    * available, will be handled before E_UPDATE.
    */
    void HandleKeyDown(StringHash eventType,VariantMap& eventData)
    {
        using namespace KeyDown;
        int key=eventData[P_KEY].GetInt();
        if(key==KEY_ESCAPE)
            engine_->Exit();

        if(key==KEY_TAB)    // toggle mouse cursor when pressing tab
        {
            GetSubsystem<Input>()->SetMouseVisible(!GetSubsystem<Input>()->IsMouseVisible());
        }

        if (key == KEY_9)
        {
            drawPhysicsDebug_ = !drawPhysicsDebug_;
        }
    }

    /**
    * You can get these events from when ever the user interacts with the UI.
    */
    void HandleClosePressed(StringHash eventType,VariantMap& eventData)
    {
        engine_->Exit();
    }
    /**
    * Your non-rendering logic should be handled here.
    * This could be moving objects, checking collisions and reaction, etc.
    */
    void HandleUpdate(StringHash eventType,VariantMap& eventData)
    {
        float timeStep=eventData[Update::P_TIMESTEP].GetFloat();
        framecount_++;
        time_+=timeStep;
        
    }
    /**
    * Anything in the non-rendering logic that requires a second pass,
    * it might be well suited to be handled here.
    */
    void HandlePostUpdate(StringHash eventType,VariantMap& eventData)
    {
        float timeStep = eventData[Update::P_TIMESTEP].GetFloat();
        framecount_++;
        time_ += timeStep;

    }
    /**
    * If you have any details you want to change before the viewport is
    * rendered, try putting it here.
    * See http://urho3d.github.io/documentation/1.32/_rendering.html
    * for details on how the rendering pipeline is setup.
    */
    void HandleRenderUpdate(StringHash eventType, VariantMap & eventData)
    {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }
    /**
    * After everything is rendered, there might still be things you wish
    * to add to the rendering. At this point you cannot modify the scene,
    * only post rendering is allowed. Good for adding things like debug
    * artifacts on screen or brush up lighting, etc.
    */
    void HandlePostRenderUpdate(StringHash eventType, VariantMap & eventData)
    {
        // We could draw some debuggy looking thing for the octree.
        // scene_->GetComponent<Octree>()->DrawDebugGeometry(true);
        if (drawPhysicsDebug_)
        {
            scene_->GetComponent<PhysicsWorld2D>()->DrawDebugGeometry(scene_->GetComponent<DebugRenderer>(), drawPhysicsDebug_);
        }
    }
    /**
    * All good things must come to an end.
    */
    void HandleEndFrame(StringHash eventType,VariantMap& eventData)
    {
        // We really don't have anything useful to do here for this example.
        // Probably shouldn't be subscribing to events we don't care about.
    }
};

/**
* This macro is expanded to (roughly, depending on OS) this:
*
* > int RunApplication()
* > {
* > Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context());
* > Urho3D::SharedPtr<className> application(new className(context));
* > return application->Run();
* > }
* >
* > int main(int argc, char** argv)
* > {
* > Urho3D::ParseArguments(argc, argv);
* > return function;
* > }
*/
URHO3D_DEFINE_APPLICATION_MAIN(MyApp)
