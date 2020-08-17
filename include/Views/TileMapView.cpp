#include "TileMapView.hpp"
#include <iostream>
TileMapView::TileMapView(const std::string& str):fileName(str){
    loadTilesFromFiles();
}

bool TileMapView::loadTilesFromFiles(){
    bool success{false};
    std::ifstream tileStream;
    tileStream.open(fileName);
    if(tileStream.is_open()){
        success = true;
    
    std::string temp;
    int i{0};
    while(getline(tileStream,temp)){
        int j{0};
        for(char singleTile: temp){
            tiles[i][j] = singleTile;
            //std::cout << tiles[i][j] << "(" << i<< "," <<j <<")" << " ";

            j++;
        }
        
        i++;
        }  

    }else{
        //std::cout << "unable to open tileFiles" << std::endl;
    }
    return success;
}

bool TileMapView::processTiles(){
    for(int i{0};i<max_tiles_y;i++){
        for(int j{0};j<max_tiles_x;j++){
            switch(tiles[i][j]){
                case '0':
                    break;
                case 't':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,Entities::Tree);
                    break;
                case 'b':
                     addEntities((j)*tile_size_x,(i)*tile_size_y,Entities::WoodenBox);;
                     break;
                case 's':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,Entities::Tree);
                    break;
            }
        }
    }
    return true;
}

void TileMapView::addEntities(int posX, int posY, Entities type){
    //std::cout << entityList.size() << std::endl;
    entityList.emplace_back(new StaticEntities(sf::Vector2f(posX,posY),static_cast<int>(type),false));
} 




