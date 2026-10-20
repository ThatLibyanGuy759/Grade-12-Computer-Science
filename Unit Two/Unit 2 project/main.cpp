#include <iostream>
#include <vector>

using namespace std;

void printGrid(int gridWidth, int gridHeight){
    for(int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            cout << "0 ";
        }
        cout << endl;
    }
}


int main(){
    int width;
    int height;

    cout << "what width do you want your grid?" << endl; 
    cin >> width;
    
    cout << "what height do you want your grid" << endl;
    cin >> height;

    printGrid(width, height);


    

}