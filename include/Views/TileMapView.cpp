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
        //std::cout << temp << std::endl;
       /*  if(temp == ""){
            i++;
            continue;
            } */
        for(char singleTile: temp){
          /*   if(singleTile == ' '){
                j++;
                continue;
            } */
            //std::cout << singleTile;
            tiles[i][j] = singleTile;
            //std::cout << tiles[i][j] << "(" << i<< "," <<j <<")" << " ";
            j++;
        }
        //std::cout << std::endl;
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
                case 'z':
                //std::cout << "found regular box" << std::endl;
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::regular_box);
                    break;
                case 't':
                   // std::cout << "found a tree " << std::endl;
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::tree);;
                    break;
                case 'r':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::stone_black);
                    break;
                case 'R':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::stone_blue);
                    break;
                case 'b':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::big_box_horizontal);
                    break;
                case 'B':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::big_box_horizontal);
                    break;
                case 'c':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::container_horizontal);
                    break;
                case 'C':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::container_vertical);
                    break;
                case 'S':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::sandbag_vertical);
                    break;
                case 's':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::sandbag_horizontal);
                    break;
                case 'u':
                    addEntities((j)*tile_size_x,(i)*tile_size_y,DefaultResources::bush);
                    break;
                

            }
        }
    }
    return true;
}

void TileMapView::addEntities(int posX, int posY, DefaultResources id){
    //std::cout << entityList.size() << std::endl;
    entityList.emplace_back(new StaticEntities(sf::Vector2f(posX,posY),id,false));
} 




