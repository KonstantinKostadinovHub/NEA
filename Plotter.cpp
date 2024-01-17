#include "Plotter.h"

#include <iostream>
#include <string>

#include "World.h"

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
	case SHAPE::BEZIER_SPLINE:
		BezierSplineCPG(numberOfPoints);
		break;
	case SHAPE::HERMITE:
		HermiteSplineCPG(numberOfPoints);
		break;
	default:
		break;
	}
}

void Plotter::Graph(const sf::VertexArray& points, const char* name)
{
	float* xCoor = new float[points.getVertexCount()];
	float* yCoor = new float[points.getVertexCount()];
	
	float minX = points[0].position.x, maxX = points[0].position.x, minY = points[0].position.y, maxY = points[0].position.y;

	for(size_t i = 0; i < points.getVertexCount(); i ++)
	{
		xCoor[i] = points[i].position.x;
		yCoor[i] = points[i].position.y;
		
		minX = std::min(points[i].position.x, minX);
		maxX = std::max(points[i].position.x, maxX);
	
		minY = std::min(points[i].position.y, minY);
		maxY = std::max(points[i].position.y, maxY);
	}

	ImPlot::SetNextAxesLimits(minX, maxX, minY, maxY);

	if (ImPlot::BeginPlot(name, ImVec2(350, 350), ImPlotFlags_NoFrame))
	{	
		ImPlot::PlotLine("Graph", xCoor, yCoor, points.getVertexCount());
	}
	ImPlot::EndPlot();

	delete[points.getVertexCount()] xCoor;
	delete[points.getVertexCount()] yCoor;
}

void Plotter::DrawTangentVectors(const sf::VertexArray& points)
{
	sf::VertexArray tangent = sf::VertexArray(sf::LinesStrip, 2);
	sf::VertexArray perp = sf::VertexArray(sf::LinesStrip, 2);

	tangent[0].color = sf::Color(0, 255, 0, 255);
	tangent[1].color = sf::Color(0, 255, 0, 255);


	perp[0].color = sf::Color(255, 0, 0, 255);
	perp[1].color = sf::Color(255, 0, 0, 255);

	for (size_t i = m_tangentStep; i < points.getVertexCount(); i += m_tangentStep)
	{
		tangent[0].position = points[i].position;
		tangent[1].position = points[i].position * 2.0f - points[i - m_tangentStep].position;


		perp[0].position = points[i].position;
		perp[1].position = points[i].position +
			sf::Vector2f(points[i].position.y - points[i - m_tangentStep].position.y,
				points[i - m_tangentStep].position.x - points[i].position.x);

		World::draw(tangent);
		World::draw(perp);
	}
}

void Plotter::LineCPG(size_t numberOfPoints)
{
	float impactOfPoint[2];
	float x_data[2];
	
	ImPlot::SetNextAxesLimits(0, numberOfPoints, 0, 1);
	if (ImPlot::BeginPlot("Control Point Impact Graph", ImVec2(350, 350), ImPlotFlags_NoFrame))
	{
		for (size_t j = 0; j < numberOfPoints; j++)
		{
			impactOfPoint[0] = 0;
			impactOfPoint[1] = 1;
			x_data[0] = j;
			x_data[1] = j;
			ImPlot::PlotLine(std::to_string(j).c_str(), x_data, impactOfPoint, 2);
		}
	}
	ImPlot::EndPlot();
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
			impactOfPoint[point][i] = (float)binomialCoefficient(numberOfPoints - 1, point) 
				* powf(1.0f - progress, numberOfPoints - point - 1) * powf(progress, point);
		}
		progress += step;
	}
	ImPlot::SetNextAxesLimits(0, 1, 0, 1);
	if (ImPlot::BeginPlot("Control Point Impact Graph", ImVec2(350, 350), ImPlotFlags_NoFrame))
	{
		for (size_t j = 0; j < numberOfPoints; j++)
		{
			ImPlot::PlotLine(std::to_string(j).c_str(), x_data, impactOfPoint[j], m_detailOfGraph);
		}
	}
	ImPlot::EndPlot();
}

void Plotter::BezierSplineCPG(size_t numberOfPoints)
{
}

void Plotter::HermiteSplineCPG(size_t numberOfPoints)
{
}
