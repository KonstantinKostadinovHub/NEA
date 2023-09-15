#include "GeometryManager.h"

#include "PlaygroundUI.h"

void GeometryManager::AddShape(std::shared_ptr<Shape> shape)
{
	m_shapes.push_back(shape);
}

void GeometryManager::Update()
{
	if (PlaygrounUI::GetSelected() != plTool::None && Input::IsMousePressed(mouseBtn::click)) 
	{
		if (m_lastShape)
		{
			m_lastShape->AddPoint({(float)Input::MouseCoor().x, (float)Input::MouseCoor().y});
		}
		else {
			printf("Creating new line");
			m_shapes.push_back(std::shared_ptr<Line>(
				new Line(sf::Vector2f(Input::MouseCoor()))
				));
			m_lastShape = m_shapes[m_shapes.size() - 1];
		}
	}
}

void GeometryManager::RemoveShape(size_t index)
{
	m_shapes.erase(m_shapes.begin() + index);
}

void GeometryManager::Draw()
{
	for (auto& shape : m_shapes)
	{
		shape->Draw();
	}
}
