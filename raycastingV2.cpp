#include <iostream>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

const int mapSize = 40;


string map[] = {
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xoooooooooooooooooooooooooooooooooooooox",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
};

void ClearScreen(){	
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void render3D(vector<double>rays, int rayCount){
	int maxDistance = 90;
	vector<string>positions;
	for(int i = 0; i < rayCount; i++){
		int height = round(rays[i] * 2);
		for (int rep = 0; rep < floor(maxDistance/rayCount); rep++){
			positions.push_back("");
			
			for (int y = 0; y < round((maxDistance - (maxDistance - height))/2); y++)
				positions[positions.size() - 1] += " ";
				
			for (int y = 0; y < maxDistance - height; y++)
				positions[positions.size() - 1] += "@";
			
			int toFull = maxDistance - positions[positions.size() - 1].size();
			for (int y = 0; y < toFull; y++)
				positions[positions.size() - 1] += " ";
		}
	}
	
	vector<string>revPositions = positions;
	for (int y = 0; y < positions[0].size(); y++){
		for (int x = 0; x < positions.size(); x++){
			revPositions[y][x] = positions[x][y];
		}
	}
	for (int x = 0; x < positions.size(); x++){
		cout << revPositions[x] << endl;
	}
}

vector<double> shootRays(double startX, double startY, double playerAngle, int fov, int rayCount){
    double rad = 0;
    double dirX = 0;
    double dirY = 0;
    double rayX = 0;
    double rayY = 0;
    vector<double>rays;

    for (int angle = playerAngle - fov/2; angle <= playerAngle + fov/2; angle += fov/rayCount){
        rad = angle * M_PI/180;
        dirX = sin(rad);
        dirY = cos(rad);
        rayX = startX;
        rayY = startY;
        while (true){
        	//cout << "X: " << rayX << " Y: " << rayY << endl;
            rayX += dirX;
            rayY -= dirY;
			
			int roundX = round(rayX);
			int roundY = round(rayY);
            if (map[roundY][roundX] == 'x')
            	break;
        }
        
        rays.push_back(sqrt((rayX - startX) * (rayX - startX) + (rayY - startY) * (rayY - startY)) * cos(playerAngle * M_PI/180 - rad));
    }

    return rays;
}

int main(){
    int angle = 0;
    char ch = ' ';
    double rad = 0;
    double playerX = 20;
    double playerY = 20;
    int roundX = 0;
    int roundY = 0;
    double dirX = 0;
    double dirY = 0;
    int fov = 60;
    int rayCount = 30;
    vector<double>rays;

	while (true){
        ch = _getch();
        rad = angle * M_PI/180;
        dirX = round(sin(rad) * 100) / 100;
        dirY = round(cos(rad) * 100) / 100;
        if (ch == 'w' || ch == 'W'){
            playerX += dirX;
            playerY -= dirY;
            
            roundX = round(playerX);
			roundY = round(playerY);
            if (map[roundY][roundX] == 'x'){
            	playerX -= dirX;
            	playerY += dirY;
			}
        }

        if (ch == 's' || ch == 'S'){
            playerX -= dirX;
            playerY += dirY;
            
            roundX = round(playerX);
			roundY = round(playerY);
            if (map[roundY][roundX] == 'x'){
            	playerX += dirX;
            	playerY -= dirY;
			}
        }

        if (ch == 'd' || ch == 'D'){
            angle = (angle+5)%360;
            cout << angle;
        }

        if (ch == 'a' || ch == 'A'){
            angle -= 5;

            if (angle == -5)
                angle = 355;
            cout << angle;
        }
		
		rays = shootRays(playerX, playerY, angle, fov, rayCount);
		
        ClearScreen();
        render3D(rays, rayCount);
    }

    int endProgram;
    cin >> endProgram;

    return 0;
}
