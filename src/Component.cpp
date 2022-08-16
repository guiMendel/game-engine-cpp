#include "GameObject.h"
#include "Component.h"
#include "Game.h"

using namespace std;

void Component::StartAndRegisterLayer()
{
  if (GetRenderLayer() != RenderLayer::None)
  {
    Game::GetInstance().GetState().RegisterLayerRenderer(GetShared());
  }

  Start();
}

shared_ptr<Component> Component::GetShared() const
{
  return gameObject.GetComponent(this);
}
