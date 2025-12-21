#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<chrono>
#include<random>
#include<memory>

using namespace std;

//First of all we will create the base class where all the properties will be kept
class Asteroid {
  private:
    int length;
    int width;
    int height;
    string color;
    string texture;
    string material;

    //Extrinsic properties(not applicable in this case because is without flyweight)
    int positionX;
    int positionY;
    int velocityX;
    int velocityY;
  
  public:
    //Ctor for the asteroid
    Asteroid(int l, int w, int h, string col, string tex, string mat, int vx, int vy, int px, int py){
      this->length = l;
      this->width = w;
      this->height = h;
      this->color = col;
      this->texture = tex;
      this->material = mat;
      this->velocityX = vx;
      this->velocityY = vy;
      this->positionX = px;
      this->positionY = py;
    }

    void render() {
      cout << "Rendering" << color << "asteroid at " << positionX << ", " << positionY << endl;
    }

    //Now lets calculate the memory usage
    static size_t memoryUsage() {
      return sizeof(int) * 7 + sizeof(string) * 3 + 32 * 3;
    }
};

class SpaceGame {
  private:
    vector<Asteroid*> asteroids;
  public:
    void spawnAsteroid(int count) {
      cout << "Spawing: " << count << "asteroids" << endl;
      
      //List of data available for creating the asteroid
      vector<string> colors = {"red", "green", "blue"};
      vector<string> textures = {"rock", "metal", "ice"};
      vector<string> materials = {"rock", "metal", "ice"};
      int sizes[] = {10, 20, 30};

      for(int i=0; i<count; i++) {
      //We  use modulo to make sure to get only 3 types of combinations
        int type = i % 3;

        asteroids.push_back(new Asteroid(
          sizes[type], sizes[type], sizes[type] * 10, 
          colors[type], textures[type], materials[type], 
          100 + i * 50, 
          100 + i * 50, 
          1,
          2
        ));
      }
      cout << "Created " << asteroids.size() << " asteroids objects" << endl;
    }

    size_t calculateMemoryUsage() {
      return asteroids.size() * Asteroid::memoryUsage();
    }

    int getAsteroidCount() {
      return asteroids.size();
    }
};

int main() {
  const int ASTEROID_COUNT = 1000000;
  SpaceGame* game = new SpaceGame();
  game->spawnAsteroid(ASTEROID_COUNT);

  size_t totalMemory = game->calculateMemoryUsage();
  cout << "Total memory usage: " << totalMemory/1048576 << " MB" << endl;

  cout << "Asteroid count: " << game->getAsteroidCount() << endl;
}