#include "Plotter.h"

#include <iostream>
#include <string>

void Plotter::ControlPointsGraph(SHAPE shape, size_t numberOfPoints)
{
	switch (shape)
	{
	case SHAPE::NONE:
		break;
	case SHAPE::LINE:
		LineCPG(numberOfPoints);
		break;
	case SHAPE::BEZIER_CURVE:
		BezierCurveCPG(numberOfPoints);
		break;
	default:
		break;
	}
}

void Plotter::VelocityGraph(const sf::VertexArray& points, size_t pointsPerSection)
{
	float* xCoor = new float[pointsPerSection];
	float* yCoor = new float[pointsPerSection];
	ImPlot::SetNextAxesLimits(-10.0, 10.0, -10.0, 10.0);

	if (ImPlot::BeginPlot("Velocity Graph"))
	{
		for (size_t p = 0; p < points.getVertexCount() - 1; p++)
		{
			xCoor[p % pointsPerSection] = points[p].position.x - points[p + 1].position.x;
			yCoor[p % pointsPerSection] = points[p].position.y - points[p + 1].position.y;

			if (p % pointsPerSection == pointsPerSection - 1)
			{
				if (p != points.getVertexCount() - 2)
				{
					ImPlot::PlotLine(std::to_string(p / pointsPerSection).c_str(), xCoor, yCoor, pointsPerSection - 1);
				}
				else
				{
					ImPlot::PlotLine(std::to_string(p / pointsPerSection).c_str(), xCoor, yCoor, pointsPerSection - 1);
				}
			}
		}
	}
	ImPlot::EndPlot();
}

void Plotter::LineCPG(size_t numberOfPoints)
{
	
}

void Plotter::BezierCurveCPG(size_t numberOfPoints)
{
	float progress = 0;
	float step = 1.0f / (float)(m_detailOfGraph - 1);
	std::vector<float[m_detailOfGraph]> impactOfPoint(numberOfPoints);
	float x_data[m_detailOfGraph];
	for (size_t i = 0; i < m_detailOfGraph; i++)
	{
		x_data[i] = progress;

 		for (size_t point = 0; point < numberOfPoints; point++)
		{
			impactOfPoint[point][i] = (float)binomialCoefficient(numberOfPoints - 1, point) * powf(1.0f - progress, numberOfPoints - point - 1) * powf(progress, point);
		}
		progress += step;
	}
	ImPlot::SetNextAxesLimits(0, 1, 0, 1);
	if (ImPlot::BeginPlot("Control Point Impact Graph", ImVec2(200, 200)))
	{
		for (size_t j = 0; j < numberOfPoints; j++)
		{
			ImPlot::PlotLine(std::to_string(j).c_str(), x_data, impactOfPoint[j], m_detailOfGraph);
		}
	}
	ImPlot::EndPlot();
}
