#include "Runner.h"

class Piece {
private:
    int x;
    int y;
    char type;
    sf::Sprite sprite;

public:
    Piece(int p_x, int p_y, char p_type, sf::Texture* t) {
        
        type = p_type;

        sprite = sf::Sprite(*t);
        sprite.setScale(2, 2);
        set_loc(p_x, p_y);
    }

    void set_loc(int p_x, int p_y) {
        x = p_x;
        y = p_y;
        sprite.setPosition(80 * p_x - 5, 80 * p_y - 5);
    }

    sf::Sprite get_sprite() {
        return sprite;
    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess Time");

    // Load all the textures
    sf::Texture board_texture;
    if(!board_texture.loadFromFile("./assets/board.jpg"))
        std::cout << "Error: failed to load ./assets/board.jpg" << std::endl;
    
    sf::Texture wpt;
    if(!wpt.loadFromFile("./assets/white_pawn.png"))
        std::cout << "Error: failed to load ./assets/white_pawn.png" << std::endl;

    sf::Texture bpt;
    if(!bpt.loadFromFile("./assets/black_pawn.png"))
        std::cout << "Error: failed to load ./assets/black_pawn.png" << std::endl;

    sf::Texture wnt;
    if(!wnt.loadFromFile("./assets/white_knight.png"))
        std::cout << "Error: failed to load ./assets/white_knight.png" << std::endl;

    sf::Texture bnt;
    if(!bnt.loadFromFile("./assets/black_knight.png"))
        std::cout << "Error: failed to load ./assets/black_knight.png" << std::endl;

    sf::Texture wbt;
    if(!wbt.loadFromFile("./assets/white_bishop.png"))
        std::cout << "Error: failed to load ./assets/white_bishop.png" << std::endl;

    sf::Texture bbt;
    if(!bbt.loadFromFile("./assets/black_bishop.png"))
        std::cout << "Error: failed to load ./assets/black_bishop.png" << std::endl;

    sf::Texture wrt;
    if(!wrt.loadFromFile("./assets/white_rook.png"))
        std::cout << "Error: failed to load ./assets/white_rook.png" << std::endl;

    sf::Texture brt;
    if(!brt.loadFromFile("./assets/black_rook.png"))
        std::cout << "Error: failed to load ./assets/black_rook.png" << std::endl;

    sf::Texture wqt;
    if(!wqt.loadFromFile("./assets/white_queen.png"))
        std::cout << "Error: failed to load ./assets/white_queen.png" << std::endl;

    sf::Texture bqt;
    if(!bqt.loadFromFile("./assets/black_queen.png"))
        std::cout << "Error: failed to load ./assets/black_queen.png" << std::endl;
    
    sf::Texture wkt;
    if(!wkt.loadFromFile("./assets/white_king.png"))
        std::cout << "Error: failed to load ./assets/white_knight.png" << std::endl;

    sf::Texture bkt;
    if(!bkt.loadFromFile("./assets/black_king.png"))
        std::cout << "Error: failed to load ./assets/black_king.png" << std::endl;


    sf::Sprite background(board_texture);
    background.setScale(0.64064, 0.64064);

    std::vector<Piece> pieces;
    pieces.push_back(Piece(0, 0, 'r', &brt));
    pieces.push_back(Piece(1, 0, 'n', &bnt));
    pieces.push_back(Piece(2, 0, 'b', &bbt));
    pieces.push_back(Piece(3, 0, 'q', &bqt));
    pieces.push_back(Piece(4, 0, 'k', &bkt));
    pieces.push_back(Piece(5, 0, 'b', &bbt));
    pieces.push_back(Piece(6, 0, 'n', &bnt));
    pieces.push_back(Piece(7, 0, 'r', &brt));
    for (int i = 0; i < 8; i++) {
        pieces.push_back(Piece(i, 1, 'p', &bpt));
    }
    
    pieces.push_back(Piece(0, 7, 'R', &wrt));
    pieces.push_back(Piece(1, 7, 'N', &wnt));
    pieces.push_back(Piece(2, 7, 'B', &wbt));
    pieces.push_back(Piece(3, 7, 'Q', &wqt));
    pieces.push_back(Piece(4, 7, 'K', &wkt));
    pieces.push_back(Piece(5, 7, 'B', &wbt));
    pieces.push_back(Piece(6, 7, 'N', &wnt));
    pieces.push_back(Piece(7, 7, 'R', &wrt));
    for (int i = 0; i < 8; i++) {
        pieces.push_back(Piece(i, 6, 'P', &wpt));
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        draw(window, background, pieces);

    }

    return 0;
}

void draw(sf::RenderWindow &window, sf::Sprite background, std::vector<Piece> pieces) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();

    // Drawing
    window.draw(background);
    for (Piece p : pieces) {
        window.draw(p.get_sprite());
    }

    // End drawing

    window.display();
}