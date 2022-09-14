#include "GameObject.h"
#include "Component.h"
#include "Game.h"

using namespace std;

void Component::StartAndRegisterLayer()
{
  if (started)
    return;

  if (GetRenderLayer() != RenderLayer::None)
  {
    Game::GetInstance().GetState().RegisterLayerRenderer(GetShared());
  }

  started = true;

  Start();
}

shared_ptr<Component> Component::GetShared() const
{
  return gameObject.GetComponent(this);
}
