#define TILEMAP_H
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Tilemap : public sf::Drawable, public sf::Transformable
{
public:

    Tilemap(const char* tmxFile);
    void draw(sf::RenderWindow &window);

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
    sf::Sprite *_tilesetSprite;
    XMLElement *layer;
    const char *foldersrc = "resources/";






private:

 
    sf::Texture m_tileset;
    sf::VertexArray m_vertices;
    sf::Sprite ****_tilemapSprite;
    sf::Texture _tilesetTexture;
    int _width;
    int _height;
    int _numLayers;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
};

