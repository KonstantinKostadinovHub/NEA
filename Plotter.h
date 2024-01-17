#include "imgui/implot.h"

#include "defines.h"

class Plotter {
public:
	Plotter() = delete;
	~Plotter() = delete;

	static void ControlPointsGraph(SHAPE shape, size_t numberOfPoints);
	static void VelocityGraph(const sf::VertexArray& points, size_t pointsPerSection);

	static void DrawTangentVectors(const sf::VertexArray& points);
private:
	static void LineCPG(size_t numberOfPoints);
	static void BezierCurveCPG(size_t numberOfPoints);
	static void BezierSplineCPG(size_t numberOfPoints);
	static void HermiteSplineCPG(size_t numberOfPoints);

	const static size_t m_detailOfGraph = 20;
	const static size_t m_tangentStep = 5;
};