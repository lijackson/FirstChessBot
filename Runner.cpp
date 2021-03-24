#include "Runner.h"

class Renderer : protected sf::RenderWindow {

    private:
    std::map<char, sf::Texture> texture_map;
    sf::Sprite background;
    int scr_w;
    int scr_h;
    bool open;

    void draw_image(char type, int x, int y) {
        sf::Sprite s(texture_map[type]);
        s.setScale(2.5 * scr_w / 1000.0, 2.5 * scr_h / 1000.0);
        s.setPosition(x * scr_w / 8.0 + 4, y * scr_h / 8.0 + 4);
        draw(s);
    }

    public:
    Renderer(int p_w, int p_h) : sf::RenderWindow(sf::VideoMode(p_w, p_h), "Chess Time") {

        scr_w = p_w;
        scr_h = p_h;
        open = true;
        
        // Load all the textures
        sf::Texture board_texture;
        if(!texture_map['#'].loadFromFile("./assets/board.jpg"))
            std::cout << "Error: failed to load ./assets/board.jpg" << std::endl;
        background = sf::Sprite(board_texture);
        background.setScale(scr_w / 1000.0, scr_h / 1000.0);
        
        if(!texture_map['P'].loadFromFile("./assets/white_pawn.png"))
            std::cout << "Error: failed to load ./assets/white_pawn.png" << std::endl;

        if(!texture_map['p'].loadFromFile("./assets/black_pawn.png"))
            std::cout << "Error: failed to load ./assets/black_pawn.png" << std::endl;

        if(!texture_map['N'].loadFromFile("./assets/white_knight.png"))
            std::cout << "Error: failed to load ./assets/white_knight.png" << std::endl;

        if(!texture_map['n'].loadFromFile("./assets/black_knight.png"))
            std::cout << "Error: failed to load ./assets/black_knight.png" << std::endl;

        if(!texture_map['B'].loadFromFile("./assets/white_bishop.png"))
            std::cout << "Error: failed to load ./assets/white_bishop.png" << std::endl;

        if(!texture_map['b'].loadFromFile("./assets/black_bishop.png"))
            std::cout << "Error: failed to load ./assets/black_bishop.png" << std::endl;

        if(!texture_map['R'].loadFromFile("./assets/white_rook.png"))
            std::cout << "Error: failed to load ./assets/white_rook.png" << std::endl;

        if(!texture_map['r'].loadFromFile("./assets/black_rook.png"))
            std::cout << "Error: failed to load ./assets/black_rook.png" << std::endl;

        if(!texture_map['Q'].loadFromFile("./assets/white_queen.png"))
            std::cout << "Error: failed to load ./assets/white_queen.png" << std::endl;

        if(!texture_map['q'].loadFromFile("./assets/black_queen.png"))
            std::cout << "Error: failed to load ./assets/black_queen.png" << std::endl;
        
        if(!texture_map['K'].loadFromFile("./assets/white_king.png"))
            std::cout << "Error: failed to load ./assets/white_knight.png" << std::endl;

        if(!texture_map['k'].loadFromFile("./assets/black_king.png"))
            std::cout << "Error: failed to load ./assets/black_king.png" << std::endl;

        char b1[8][8]= {{'q', 'k', ' ', ' ', ' ', 'Q', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', 'p', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', 'R', ' ', 'K',' '}};
        draw_board(b1);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    void draw_board(char board[8][8]) {
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
        
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (board[x][y] != ' ') draw_image(board[x][y], x, y);
            }
        }
        
        // End drawing
        display();
    }

    bool is_open() {
        return open;
    }
};

int main()
{
    Renderer r(800, 800);
    char b1[8][8]= {{'q', 'k', ' ', ' ', ' ', 'Q', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', 'p', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', 'R', ' ', 'K', ' '}};
    while (r.is_open())
    {
        r.draw_board(b1);
    }

    return 0;
}