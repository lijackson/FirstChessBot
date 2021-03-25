#ifndef RUNNER_H
#define RUNNER_H

#include <iostream>
#include <vector>
#include <map>

#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

class Renderer : protected sf::RenderWindow{

    private:
    std::map<char, sf::Texture> texture_map;
    sf::Sprite background;
    int scr_w;
    int scr_h;
    bool open;

    void draw_image(char type, int x, int y);

    public:
    // This initializes a Renderer with width p_w, and height p_h
    Renderer(int p_w, int p_h);

    // This draws the board, should be called every frame
    void draw_board(char board[8][8]);

    // This is a getter function to determine if the window is still open
    bool is_open();

};

int main();

#endif