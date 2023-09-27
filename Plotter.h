#include "imgui/implot.h"

#include "defines.h"

class Plotter {
public:
	Plotter() = delete;
	~Plotter() = delete;

	static void ControlPointsGraph(SHAPE shape, size_t numberOfPoints);
private:
	static void LineCPG(size_t numberOfPoints);
	static void BezierCurveCPG(size_t numberOfPoints);

	const static size_t m_detailOfGraph = 20;
};