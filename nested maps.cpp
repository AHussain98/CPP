# include <iostream>
# include <map>
# include <string>
// a nested map is a map that contains another map

using level_map = std::map<int, std::string>; // used instread of typedef, as a macro

int main(){

std::map<int,std::string> level1 = { {1, "Player"},{10, "door"} }; // map with two elements with different keys
std::map<int,std::string> level2 = {{5, "Player"}, {10, "monster"}};

std::map<int, std::map<int,std::string>> game_world;   // you can put a map within a map

game_world.insert({1,level1});
game_world.insert({2,level2});

level_map level3 = { {10, "Player"}, {10,"Boss"}};
game_world.insert({3,level3});

for (auto i : game_world){
    std::cout << "Level number: " << i.first << " ";
    for (auto j : i.second){
        std::cout << j.first << ", " << j.second << std::endl;
    }
}

// create an iterator to the second level, I want to edit it
auto it = game_world.find(2);

it->second.insert({15, "Impossible monster"}); // they're in {} because they're initialside and created inplace as poirs, otherwise we'd have to do make_pair

// now delete the third level

game_world.erase(3);

// now reprint

for (auto i : game_world){
    std::cout << "Level number: " << i.first << " ";
    for (auto j : i.second){
        std::cout << j.first << ", " << j.second << std::endl;
    }
}



}