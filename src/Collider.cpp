#include "Collider.h"
#include <memory>

using namespace std;

// Explicitly initialize box
Collider::Collider(GameObject &associatedObject, Rectangle box) : Component(associatedObject)
{
  SetBox(box);
}

// Use sprite's box
Collider::Collider(GameObject &associatedObject, std::shared_ptr<Sprite> sprite, Vector2 scale)
    : Collider(associatedObject,
               Rectangle(-sprite->GetWidth() * scale.x / 2, -sprite->GetHeight() * scale.y / 2,
                         sprite->GetWidth() * scale.x, sprite->GetHeight() * scale.y)) {}

void Collider::SetBox(const Rectangle &newBox)
{
  box = newBox;

  maxVertexDistance = sqrt(box.width * box.width + box.height * box.height) / 2;
}

Rectangle Collider::GetBox() const { return box; }

void Collider::Start()
{
  // Announce to game state
  gameObject.gameState.RegisterCollider(dynamic_pointer_cast<Collider>(GetShared()));
}