#pragma once
#include "util/log.h"
#include "graphics/sprite.h"
#include "game/map.h"
#include "graphics/buffers/vertexarray.h"

extern Log gameLog;
extern Sprite defaultSprite;
extern Texture* snowman;
extern Tile defTile;
extern VertexArray* vao;
extern BufferLayout tileLayout;
extern Buffer* texCoordBuffer;
extern BufferLayout texCoordLayout;
extern Buffer* tileVertices;
extern IndexBuffer* tileIndices;
