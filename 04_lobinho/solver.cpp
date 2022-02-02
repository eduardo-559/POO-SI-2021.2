#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height) {
	auto dim = sprite.getLocalBounds();
	sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity {
    int x {0};
    int y {0};
    int step {0};
    sf::Sprite sprite;

Entity(int x, int y, int step, sf::Texture& texture):
	x {x}, y {y}, step {step}, sprite (texture) {
}

void draw(sf::RenderWindow& window) {
	this->sprite.setPosition(x * step, y * step);
	setSize(this->sprite, step, step);
	window.draw(this->sprite);
}

};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys) {
	if(key == move_keys[0])
	 entity.x--;
	else if(key == move_keys[1])
	 entity.y--;
	else if(key == move_keys[2])
	 entity.x++;
	else if(key == move_keys[3])
	 entity.y++;
}

sf::Texture loadTexture(std::string path) {
	sf::Texture texture;
	if (!texture.loadFromFile(path)) {
		std::cout << "Error loading texture" << std::endl;
        
	}
	return texture;
}

struct Board {
	int nc {0};
	int nl {0};
	int step {0};
	sf::Sprite sprite;
	sf::RectangleShape rect;

	Board(int nc, int nl, int step, sf::Texture& texture) {
		this->nc = nc;
		this->nl = nl;
		this->step = step;
		this->sprite.setTexture(texture);
		setSize(this->sprite, nc * step, nl * step);
		this->sprite.setPosition(0, 0);

		this->rect.setSize(sf::Vector2f(step, step));
		this->rect.setFillColor(sf::Color::Transparent);
		this->rect.setOutlineColor(sf::Color::Black);
		this->rect.setOutlineThickness(2);;
	}
	void draw(sf::RenderWindow& window) {
		window.draw(this->sprite);
        for (int i = 0; i < nc; i++) {
	        for ( int j = 0; j < nl; j++) {
		        rect.setPosition(i * step, j * step);
		        window.draw(rect);
	        } 
        }
    }
};

int Colidir(Entity& entitya, Entity& entityb) {
    if (entitya.x == entityb.x) {
        if(entitya.y == entityb.y)
            return 1;
    }
    return 0;
}

int main()
{
    sf::Texture pain_tex {loadTexture("painn.png")};
    sf::Texture naru_tex {loadTexture("narus.jpg")};
    sf::Texture grass_tex {loadTexture("grass.jpg")};

    const int STEP {100};

    Entity pain(1, 1, STEP, pain_tex);
    Entity naru(2, 2, STEP, naru_tex);
    Board board(7, 5, STEP, grass_tex);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
	            moveEntity(event.key.code, pain, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
                moveEntity(event.key.code, naru, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
            }
        }
        if (Colidir(pain, naru) == 1) {
            std::cout << "Fim de jogo" << std::endl;
            exit(1);
        }

        window.clear();
        board.draw(window);
        pain.draw(window);
        naru.draw(window);
        window.display();
    }
    return 0;
}