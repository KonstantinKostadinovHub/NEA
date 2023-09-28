#include "GeometryManager.h"

#include "PlaygroundUI.h"

#include "BezierCurve.h"
#include "Plotter.h"

void GeometryManager::AddShape(std::shared_ptr<Shape> shape)
{
	m_shapes.push_back(shape);
}

void GeometryManager::ShowStats()
{
	if (m_lastShape)
	{
		Plotter::ControlPointsGraph(m_lastShape->m_type, m_lastShape->GetControlPointsCount());
	}
}

void GeometryManager::Update()
{
	if (PlaygrounUI::GetSelected() != plTool::None && Input::IsMousePressed(mouseBtn::click)) 
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
				if (data.first)
				{
					printf("Set control array \n");
					m_selectedIndex = data.first;
				}
			}
			else
			{
				m_selectedIndex = size_t(-1);
				if (Input::MouseOnClick(mouseBtn::click))
				{
					if (m_lastShape)
					{
						m_lastShape->AddPoint({ (float)Input::MouseCoor().x, (float)Input::MouseCoor().y });
					}
					else
					{
						switch (PlaygrounUI::GetSelected())
						{
						case plTool::Line:
							m_shapes.push_back(std::make_shared<Line>(
								sf::Vector2f(Input::MouseCoor())
								));
							break;
						case plTool::BezierCurve:
							m_shapes.push_back(std::make_shared<BezierCurve>(
								sf::Vector2f(Input::MouseCoor())
								));
							break;
						default:
							break;
						}
						m_lastShape = m_shapes[m_shapes.size() - 1];
					}
				}
			}
		}
	}
	else
	{
		m_selectedIndex = size_t(-1);
	}

	ShowStats();
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
