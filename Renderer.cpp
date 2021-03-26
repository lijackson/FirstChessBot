#include "Renderer.h"

std::map<char, sf::Texture> texture_map;
sf::Sprite background;
int scr_w;
int scr_h;
bool open;

Renderer::Renderer(int p_w, int p_h) : sf::RenderWindow(sf::VideoMode(p_w, p_h), "Chess Time") {

    scr_w = p_w;
    scr_h = p_h;
    open = true;
    
    // Load all the textures

    std::cout << "Loading textures";
    sf::Texture board_texture;
    if(!texture_map['#'].loadFromFile("./assets/board.jpg"))
        std::cout << "Error: failed to load ./assets/board.jpg" << std::endl;
    background = sf::Sprite(board_texture);
    background.setScale(scr_w / 1000.0, scr_h / 1000.0);
    std::cout << ".";
    
    // TODO: Turn this into a nice looking loop. Maybe define a resource map or something.
    if(!texture_map['P'].loadFromFile("./assets/white_pawn.png"))
        std::cout << std::endl << "Error: failed to load ./assets/white_pawn.png" << std::endl;
    std::cout << ".";

    if(!texture_map['p'].loadFromFile("./assets/black_pawn.png"))
        std::cout << std::endl << "Error: failed to load ./assets/black_pawn.png" << std::endl;
    std::cout << ".";

    if(!texture_map['N'].loadFromFile("./assets/white_knight.png"))
        std::cout << std::endl << "Error: failed to load ./assets/white_knight.png" << std::endl;
    std::cout << ".";

    if(!texture_map['n'].loadFromFile("./assets/black_knight.png"))
        std::cout << std::endl << "Error: failed to load ./assets/black_knight.png" << std::endl;
    std::cout << ".";

    if(!texture_map['B'].loadFromFile("./assets/white_bishop.png"))
        std::cout << std::endl << "Error: failed to load ./assets/white_bishop.png" << std::endl;
    std::cout << ".";

    if(!texture_map['b'].loadFromFile("./assets/black_bishop.png"))
        std::cout << std::endl << "Error: failed to load ./assets/black_bishop.png" << std::endl;
    std::cout << ".";

    if(!texture_map['R'].loadFromFile("./assets/white_rook.png"))
        std::cout << std::endl << "Error: failed to load ./assets/white_rook.png" << std::endl;
    std::cout << ".";

    if(!texture_map['r'].loadFromFile("./assets/black_rook.png"))
        std::cout << std::endl << "Error: failed to load ./assets/black_rook.png" << std::endl;
    std::cout << ".";

    if(!texture_map['Q'].loadFromFile("./assets/white_queen.png"))
        std::cout << std::endl << "Error: failed to load ./assets/white_queen.png" << std::endl;
    std::cout << ".";

    if(!texture_map['q'].loadFromFile("./assets/black_queen.png"))
        std::cout << std::endl << "Error: failed to load ./assets/black_queen.png" << std::endl;
    std::cout << ".";
    
    if(!texture_map['K'].loadFromFile("./assets/white_king.png"))
        std::cout << std::endl << "Error: failed to load ./assets/white_knight.png" << std::endl;
    std::cout << ".";

    if(!texture_map['k'].loadFromFile("./assets/black_king.png"))
        std::cout << std::endl << "Error: failed to load ./assets/black_king.png" << std::endl;
    std::cout << ".Finished" << std::endl;
}

void Renderer::draw_image(char type, int x, int y) {
    sf::Sprite s(texture_map[type]);
    s.setScale(2.5 * scr_w / 1000.0, 2.5 * scr_h / 1000.0);
    s.setPosition(x * scr_w / 8.0 + 4, y * scr_h / 8.0 + 4);
    draw(s);
}

void Renderer::draw_board(char board[8][8]) {
    sf::Event event;
    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            open = false;
            close();
            std::cout << "Exiting..." << std::endl;
        }
    }

    clear();

    // Drawing
    sf::Sprite bg(texture_map['#']);
    bg.setPosition(0, 0);
    bg.setScale(scr_w / 1000.0, scr_h / 1000.0);
    draw(bg);
    
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] != ' ') draw_image(board[r][c], c, r);
        }
    }
    
    // End drawing
    display();
}

bool Renderer::is_open() {
    return open;
}