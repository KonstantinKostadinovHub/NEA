#include "GeometryManager.h"

#include "PlaygroundUI.h"

#include "BezierCurve.h"
#include "BezierSpline.h"
#include "Hermite.h"
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
	case SHAPE::BEZIER_SPLINE:
		m_shapes.push_back(std::make_shared<BezierSpline>(
			sf::Vector2f(Input::MouseCoor())
			));
		break;
	case SHAPE::HERMITE:
		m_shapes.push_back(std::make_shared<Hermite>(
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
		Shape::m_drawOsculatingCircleGraph = false;
		if(m_statsUI.GetSelected() == STAT::OSCULATING_CIRCLE) Shape::m_drawOsculatingCircleGraph = true;
		if (ImGui::Begin("Graphs", NULL, DEFAULT_WINDOW))
		{
			switch (m_statsUI.GetSelected())
			{
			case STAT::FIRST_DERIVATIVE:
				Plotter::Graph(m_lastShape->GetFirstDerivative(), "First Derivative");
				break;
			case STAT::SECOND_DERIVATIVE:
				Plotter::Graph(m_lastShape->GetSecondDerivative(), "Second Derivative");
				break;
			case STAT::PERPENDICULARS:
				Plotter::DrawTangentVectors(m_lastShape->GetVertexArray());
				break;
			case STAT::AGENT:
				CreateAgent(m_lastShape->GetVertexArray());
				break;
			case STAT::CONTROL_POINT_GRAPH:
				Plotter::ControlPointsGraph(m_lastShape->m_type, m_lastShape->GetControlPointsCount());
				break;
			default:
				break;
			}
		}
		ImGui::End();
	}
}

void GeometryManager::CreateAgent(const sf::VertexArray& v)
{
	Agent agent;
	agent.Init(v);
	m_agents.push_back(agent);
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
			m_selectionFlag = 0;
			if (Input::IsKeyPressed(sf::Keyboard::LShift))
			{
				m_selectionFlag = 1;
			}
			m_lastShape->SetPoint(m_selectedIndex, sf::Vector2f(Input::MouseCoor()), m_selectionFlag);
		}
		else
		{
			auto data = CheckForSelection(sf::Vector2f(Input::MouseCoor()));
			if (data.first != size_t(-1))
			{
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

	for (size_t i = 0; i < m_agents.size(); i++) 
	{
		if (!m_agents[i].Update())
		{
			m_agents.erase(m_agents.begin() + i);
			i--;
		}
	}
}

void GeometryManager::RemoveShape(size_t index)
{
	m_shapes.erase(m_shapes.begin() + index);
}

void GeometryManager::Draw()
{
	m_statsUI.Run();

	for (auto& shape : m_shapes)
	{
		shape->Draw();
	}

	for (auto& a : m_agents)
	{
		a.Draw();
	}

	ShowStats();

	m_infoCard.Draw();
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