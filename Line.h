#include "SFML/Graphics.hpp"

class Line {
public:
	Line(){};
	Line(sf::Vector2f s, sf::Vector2f e) { m_line.append(s); m_line.append(e); };
	virtual ~Line(){};

	void setColor(sf::Color c);
	void setVertex(std::size_t i, sf::Vector2f v);

	void draw();
private:
	sf::VertexArray m_line;

	sf::Color m_color;

};