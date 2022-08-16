#ifndef __RENDER_LAYER__
#define __RENDER_LAYER__

// Layers on which to render. The Last layers will be rendered on top of the first layers
enum class RenderLayer
{
  Background,
  Tilemap,
  Default,
  Enemies,
  Player,
  Projectiles,
  None
};

#endif