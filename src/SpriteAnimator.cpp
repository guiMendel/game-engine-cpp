#include "SpriteAnimator.h"

void SpriteAnimator::ConfigureSpriteFrames()
{
  // Get sprite ref
  auto sprite = spriteWeak.lock();

  if (!sprite)
  {
    enabled = false;
    return;
  }

  // Get frame count
  columnFrameCount = sprite->GetWidth() / frameDimensions.x;
  rowFrameCount = sprite->GetHeight() / frameDimensions.y;

  // Set first frame
  SetFrame(0);
}

void SpriteAnimator::Update(float deltaTime)
{
  // Count this frame's time
  frameElapsedTime += deltaTime;

  // Do nothing id timer isn't up
  if (frameElapsedTime < secondsPerFrame)
    return;

  // Advance frame
  SetFrame(currentFrame + 1);
}

void SpriteAnimator::SetFrame(int frameIndex)
{
  Assert(frameIndex >= 0, "Invalid frame index");

  // Get sprite
  auto sprite = spriteWeak.lock();

  if (!sprite)
  {
    enabled = false;
    return;
  }

  // Reset time
  frameElapsedTime = 0;

  // Update to this frame
  // Limit frame index to frame space
  currentFrame = frameIndex % GetFrameCount();

  // Finit's row
  int frameRow = currentFrame / columnFrameCount;

  // And it's column
  int frameColumn = currentFrame % columnFrameCount;

  // Set the sprite's clip
  sprite->SetClip(
      frameColumn * frameDimensions.x,
      frameRow * frameDimensions.y,
      frameDimensions.x,
      frameDimensions.y);
}
