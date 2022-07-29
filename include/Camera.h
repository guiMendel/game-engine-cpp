#ifndef __CAMERA__
#define __CAMERA__

#include "GameObject.h"
#include "Vector2.h"
#include <memory>

class Camera
{
public:
  // Acceleration applied each frame to the camera towards 0 speed
  static const int gravity{70};

  // Max speed for the camera, in pixels per second
  static const int maxSpeed{700};

  // Acceleration applied to the camera on user input
  static const int acceleration{4000};

  // Coordinates of camera's center
  Vector2 position;

  // Current speed of camera
  Vector2 speed;

  // Start following new object
  void Follow(std::shared_ptr<GameObject> newFocus) { focus = newFocus; }

  // Follow no object
  void Unfollow() { focus.reset(); }

  // Update frame
  void Update(float deltaTime);

  static Camera &GetInstance()
  {
    static Camera instance;

    return instance;
  }

private:
  // Singleton
  Camera(){};

  // Which game object to follow
  std::weak_ptr<GameObject> focus;

  // Move the camera the current speed
  void Move(Vector2 speedModification, float deltaTime);
};

#endif