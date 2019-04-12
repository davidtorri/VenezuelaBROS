#define TILEMAP_H
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Tilemap : public Drawable, public Transformable
{
public:

    Tilemap(const char* tmxFile);
    void draw(RenderWindow &window);

    XMLDocument doc;
    XMLElement *map;
    XMLElement *tileset;
    XMLElement *img;
    int _tilewidth;
    int _tileheight;
    int _imgWidth;
    int _imgHeight;
    int _tilecount;
    int posX = 0;
    int posY = 0;
    int ***_tilemap;
    Sprite *_tilesetSprite;
    XMLElement *layer;
    const char *foldersrc = "resources/";
    int getGid(int l, int y, int x);

private:

    Texture m_tileset;
    VertexArray m_vertices;
    Sprite ****_tilemapSprite;
    Texture _tilesetTexture;
    int _width;
    int _height;
    int _numLayers;

    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
};

