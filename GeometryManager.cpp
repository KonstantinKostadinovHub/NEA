#include "GeometryManager.h"

#include "PlaygroundUI.h"

#include "BezierCurve.h"
#include "Plotter.h"

void GeometryManager::CreatePoint()
{
	switch (PlaygrounUI::GetSelected())
	{
	case SHAPE::LINE:
		m_shapes.push_back(std::make_shared<Line>(
			sf::Vector2f(Input::MouseCoor())
			));
		break;
	case SHAPE::BEZIER_CURVE:
		m_shapes.push_back(std::make_shared<BezierCurve>(
			sf::Vector2f(Input::MouseCoor())
			));
		break;
	default:
		break;
	}
	m_lastShape = m_shapes[m_shapes.size() - 1];
}

void GeometryManager::ShowStats()
{
	if (m_lastShape)
	{
		if (ImGui::Begin("Graphs", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
		{
			//Plotter::ControlPointsGraph(m_lastShape->m_type, m_lastShape->GetControlPointsCount());
			//Plotter::VelocityGraph(m_lastShape->GetVertexArray(), m_lastShape->GetPointsPerSection());
			//Plotter::DrawTangentVectors(m_lastShape->GetVertexArray());
		}
		ImGui::End();
	}
}

bool GeometryManager::OverlapUI()
{
	sf::RectangleShape horizontalBar(sf::Vector2f(480, 64));
	horizontalBar.setPosition(sf::Vector2f(720, 27));
	sf::RectangleShape verticalBar(sf::Vector2f(53, 969));
	verticalBar.setPosition(sf::Vector2f(23, 81));
	sf::Vector2i m = Input::MouseCoor();
	return inRect(m, horizontalBar) || inRect(m, verticalBar);
}

void GeometryManager::Update()
{
	if (PlaygrounUI::GetSelected() != SHAPE::NONE && Input::IsMousePressed(mouseBtn::click) && !OverlapUI())
	{
		if (m_selectedIndex != size_t(-1))
		{
			m_lastShape->SetPoint(m_selectedIndex, sf::Vector2f(Input::MouseCoor()), m_selectionFlag);
		}
		else
		{
			auto data = CheckForSelection(sf::Vector2f(Input::MouseCoor()));
			if (data.first != size_t(-1))
			{
				printf("Set control array \n");
				m_selectedIndex = data.first;
			}
			else
			{
				m_selectedIndex = size_t(-1);
				if (Input::MouseOnClick(mouseBtn::click))
				{
					if (m_lastShape)
					{
						if (PlaygrounUI::GetSelected() != m_lastShape->m_type)
						{
							CreatePoint();
						}
						m_lastShape->AddPoint({ (float)Input::MouseCoor().x, (float)Input::MouseCoor().y });
					}
					else
					{
						CreatePoint();
					}
				}
			}
		}
	}
	else
	{
		m_selectedIndex = size_t(-1);
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

	ShowStats();
}

/*
* @return size_t - index of the point
* @return int - flag
*/
std::pair<size_t, int> GeometryManager::CheckForSelection(sf::Vector2f mousePos)
{
	for (const auto& shape : m_shapes)
	{
		if (shape)
		{
			auto res = shape->IsSelected();
			if (res.first != size_t(-1))
			{
				return res;
			}
		}
	}
	return {size_t(-1), -1};
}