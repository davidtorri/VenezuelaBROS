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

        _tilesetSprite = new Sprite[_tilecount];

        for(int i = 0; i < _tilecount; i++){
            cout << "PosX: " << posX << " - PosY: " << posY << " - width: " << _tilewidth << " - height: " << _tileheight << endl;
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
            _tilemapSprite[l] = new Sprite**[_height];
        }

        for(int l=0; l < _numLayers; l++){
            for(int y = 0; y < _height; y++){
                _tilemapSprite[l][y] = new Sprite*[_width];
                for(int x= 0; x<_width; x++){
                    _tilemapSprite[l][y][x] = new Sprite();
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
            //cout << "Layer num " << l << endl;
            for(int y=0; y < _height; y++) {
                for(int x = 0; x < _width; x++){
                	//if(map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile")->FirstChildElement("gid")){
                		//cout << "Hasta aqui0" << endl;
                		//if(data[l]){
                		//cout << data[1] << endl;

                		//cout << data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]) << endl;

                		if( data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]) == 1 ){
                            _tilemap[l][y][x]=51;
                		}

                		//cout << "Capa[" << l << "] y:" << y << " x:" << x << " -gid: " << _tilemap[l][y][x]-1 << endl;

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
                    int dif = -1;
                    int gid = _tilemap[l][y][x]+dif;

                    if(gid==50){
                        gid = NULL;
                    }
                    //cout << "Executing " << l << " " << y << " " << x << " gid: " << gid << endl;
                    if(gid !=NULL && gid>dif-1){
                        //cout << "Gid things 1" << endl;
                    	_tilemapSprite[l][y][x] = new Sprite(_tilesetTexture, _tilesetSprite[gid].getTextureRect());
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
                        _tilemapSprite[l][y][x]->setScale(Vector2f(1.0f, 0.5f));
                        window.draw(*(_tilemapSprite[l][y][x]));
                    }

                }
            }
        }
    }

int Tilemap::getGid(int l, int y, int x){
    int gid = 3000;
    y = y/(_tileheight*0.5);
    x = x/(_tilewidth*0.5);

    if( x>=1 && x<=49 && y>=0 && y<=14 ){
        int layer0 = _tilemap[0][y][x];
        int layer1 = _tilemap[1][y][x];
        /*cout << "gid layer 0 " << layer0 << " for position x:" << x << " y:" << y << endl;
        cout << "gid layer 1 " << layer1 << " for position x:" << x << " y:" << y << endl;*/
        gid = layer1;
    }else{
        //cout << "Wrong x and y: " << x << ", " << y << endl;
        gid=15;
    }

    return gid;
}
