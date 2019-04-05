#include "Tilemap.h"


Tilemap::Tilemap(const char* tmxFile){


        doc.LoadFile(tmxFile);
        map = doc.FirstChildElement("map");

        map->QueryIntAttribute("width", &_width);
        map->QueryIntAttribute("height", &_height);
        map->QueryIntAttribute("tilewidth", &_tilewidth);
        map->QueryIntAttribute("tileheight", &_tileheight);

        tileset = map->FirstChildElement("tileset");
        img = tileset->FirstChildElement("image");

        const char *filename = img->Attribute("source");
        char result[strlen(foldersrc) + strlen(filename)];

        strcpy(result,foldersrc);
        strcat(result,filename);
       cout << "LLEGO3" << endl;

        tileset->QueryIntAttribute("tilecount", &_tilecount);
        img->QueryIntAttribute("width", &_imgWidth);
        img->QueryIntAttribute("height", &_imgHeight);

        _tilesetTexture.loadFromFile(result);

        _tilesetSprite = new sf::Sprite[_tilecount];

        for(int i = 0; i < _tilecount; i++){
            //cout << "PosX: " << posX << " - PosY: " << posY << " - width: " << _tilewidth << " - height: " << _tileheight << endl;
            _tilesetSprite[i].setTextureRect(sf::IntRect(posX, posY, _tilewidth, _tileheight));
            posX += _tilewidth;
            if(posX >= _imgWidth){
                posX = 0;
                posY += _tileheight;
            }
        }

        _numLayers = 0;
        layer = map->FirstChildElement("layer");
        while(layer){
            _numLayers++;
            layer = layer->NextSiblingElement("layer");
        }

        _tilemap = new int**[_numLayers];
        for(int i=0; i < _numLayers; i++){
            _tilemap[i] = new int*[_height];
        }
        for(int l=0; l < _numLayers; l++){
            for(int y=0; y < _height;y++){
                _tilemap[l][y] = new int[_width];
            }
        }

        _tilemapSprite = new sf::Sprite***[_numLayers];
        for (int l = 0; l < _numLayers; l++){
            _tilemapSprite[l] = new sf::Sprite**[_height];
        }

        for(int l=0; l < _numLayers; l++){
            for(int y = 0; y < _height; y++){
                _tilemapSprite[l][y] = new sf::Sprite*[_width];
                for(int x= 0; x<_width; x++){
                    _tilemapSprite[l][y][x] = new sf::Sprite();
                }
            }
        }

        XMLElement *data[_numLayers];
        layer = map->FirstChildElement("layer");
        for(int l=0; l<_numLayers; l++){
            data[l] = layer->FirstChildElement("data")->FirstChildElement("tile");
            layer = layer->NextSiblingElement("layer");
        }

        for(int l=0; l < _numLayers; l++){
            cout << "Layer num " << l << endl;
            for(int y=0; y < _height; y++) {
                for(int x = 0; x < _width; x++){
                	//if(map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile")->FirstChildElement("gid")){
                		//cout << "Hasta aqui0" << endl;
                		//if(data[l]){
                		//cout << data[1] << endl;

                		//cout << data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]) << endl;

                		data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);

                		cout << "Tile l y x: " << l << " " << y << " " << x << " --gid: " << _tilemap[l][y][x] << endl;

                		//}
                	//}else{

                		//if(data[l]){
                		//data[l]->QueryIntAttribute(NULL, &_tilemap[l][y][x]);
                	//	cout << "Hasta aqui3" << endl;
                	//	}
                	//}

						data[l] = data[l]->NextSiblingElement("tile");

                }
            }
        }

cout << "Tiles leidos --------" << endl;
        for(int l=0; l < _numLayers;l++){
            for(int y=0; y < _height; y++){
                for(int x = 0; x < _width; x++){
                    int gid = _tilemap[l][y][x]-1;

                    if(gid>20){
                        gid = NULL;
                    }
                    //cout << "Executing " << l << " " << y << " " << x << " gid: " << gid << endl;
                    if(gid !=NULL && gid>0){
                        //cout << "Gid things 1" << endl;
                    	_tilemapSprite[l][y][x] = new sf::Sprite(_tilesetTexture, _tilesetSprite[gid].getTextureRect());
                    	//cout << "Gid things 2" << endl;
                        _tilemapSprite[l][y][x]->setPosition(x*(_tilewidth/2), y*(_tileheight/2));
                        //cout << "Gid things done" << endl;
    		       }else{
                       //_tilemapSprite[l][y][x] = new sf::Sprite(_tilesetTexture, _tilesetSprite[200].getTextureRect());
                       _tilemapSprite[l][y][x] = NULL;

                    }
                }
            }
        }
    }

    void Tilemap::draw(sf::RenderWindow &window){
        for(int l = 0; l < _numLayers; l++){
            for(int y = 0; y < _height; y++){
                for(int x = 0; x < _width; x++){

                    if(_tilemapSprite[l][y][x] != NULL){
                        _tilemapSprite[l][y][x]->setScale(sf::Vector2f(1.0f, 1.0f));
                        window.draw(*(_tilemapSprite[l][y][x]));
                    }

                }
            }
        }
    }
