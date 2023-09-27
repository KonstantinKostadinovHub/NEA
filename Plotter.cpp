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
	ImPlot::CreateContext();
	if (ImPlot::BeginPlot("Control Point Impact Graph"))
	{
		for (size_t j = 0; j < numberOfPoints; j++)
		{
			ImPlot::PlotLine(std::to_string(j).c_str(), x_data, impactOfPoint[j], m_detailOfGraph);
		}
	}
	ImPlot::EndPlot();
	ImPlot::DestroyContext();
}
