#include "TileMapView.hpp"

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
            tiles[j][i] = singleTile;
            j++;
        }
        i++;
        }  

    }else{
        std::cout << "unable to open tileFiles" << std::endl;
    }
    return success;
}

bool TileMapView::processTiles(){
    for(int i{0};i<max_tiles_y;i++){
        for(int j{0};j<max_tiles_x;j++){
            switch(tiles[j][i]){
                case '0':
                    break;
                case 't':
                    addEntities(j*tile_size_x,i*tile_size_y,Entities::Tree);
                    break;
                case 'b':
                     addEntities(j*tile_size_x,i*tile_size_y,Entities::WoodenBox);
                     break;
                case 's':
                    addEntities(j*tile_size_x,i*tile_size_y,Entities::Stone);
                    break;
            }
        }
    }
    return true;
}

void TileMapView::addEntities(int posX, int posY, Entities type){
    
}
