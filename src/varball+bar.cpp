#include "varball+bar.h"
float width = 480;
float height = 720;
float radius = 10;
float speed = 400.f;  
float ballVelX = speed; 
float ballVelY = -speed;
float toadogocX = (width / 2) - radius;
float toadogocY = height - 15.01f - (2 * radius);

int level = 1;
int leveltmp = 1;

float ballX = (width / 2) - radius;
float ballY = height - 20.01f - (2 * radius);

float barWidth = width / 2;  
float barHeight = 15;
float barX = (width - barWidth) / 2; 
float barY = height - 20;
