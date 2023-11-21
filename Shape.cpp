#include "Shape.h"

#include "World.h"

bool Shape::m_drawOsculatingCircleGraph = false;

void Shape::UpdateLastVisiblePoint()
{
	if (m_lastPointInfo.first + 1 != m_curve.getVertexCount())
	{
		if (m_msPerPoint < World::GetTimeInMs() - m_lastPointInfo.second)
		{
			m_lastPointInfo.second = World::GetTimeInMs();
			m_lastPointInfo.first++;
			m_curveToDraw.clear();
			for (size_t i = 0; i <= m_lastPointInfo.first; i++)
			{
				m_curveToDraw.append(m_curve[i].position);
			}
		}
	}
}
