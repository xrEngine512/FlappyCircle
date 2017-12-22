#include "GamePCH.h"
#include "Tools.h"
#include "RectanglePrimitive.h"
#include "CirclePrimitive.h"
#include "Pipe.h"
#include "Player.h"
#include "log.h"
#include <string>
#include <sstream>

#define LOG_TAG "Tools"


#ifdef LOG_VARS
#define LOG_VAR(var) log(#var + std::string(" is "), var)
#else
#define LOG_VAR(var)
#endif

const float EPSILON = 0.0000000001f;

float screenWidth = 0;
float screenHeight = 0;
float aspectRatio = 0;

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

template <typename T>
void log(const std::string& message, T val)
{
    const char* ss = (message + ToString(val)).c_str();

    LOG_INFO("%s", ss);
}

void Tools::UpdateScreenResolution()
{
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);

	screenWidth = viewport[2];
	screenHeight = viewport[3];
	aspectRatio = screenWidth / screenHeight;

    log("aspect ratio is", aspectRatio);
}

float Tools::GetAspectRatio()
{
	return aspectRatio;
}

Vector2D Tools::ConvertToUniform(const Vector2D& point)
{
	return Vector2D(point.x/aspectRatio, point.y);
}

bool Tools::Intersects(const GameObject* object1, const GameObject* object2)
{
	const Pipe* pipe = nullptr;
	const Player* player = nullptr;

	/*Discard all bad input and determine types*/
	if (pipe = dynamic_cast<const Pipe*>(object1))
		player = dynamic_cast<const Player*>(object2);
	else if (pipe = dynamic_cast<const Pipe*>(object2))
		player = dynamic_cast<const Player*>(object1);
	
	if(!(pipe && player))
		return false;

	/*Get needed data*/	
	auto playerPos = player->GetPosition();
	auto pipePos = pipe->GetPosition();
	
	auto& rect = static_cast<const RectanglePrimitive&>(pipe->Geometry());
	auto& circle = static_cast<const CirclePrimitive&>(player->Geometry());

	/*Do actual work*/

	return Intersects(pipePos, ConvertToUniform(rect.GetSize()), playerPos, circle.GetRadius());
}

bool Tools::Intersects(const Vector2D& rectPos, const Vector2D& rectSize, const Vector2D& circleCenter, float circleRadius)
{
    LOG_VAR(rectPos.x);
    LOG_VAR(rectPos.y);
    LOG_VAR(rectSize.x);
    LOG_VAR(rectSize.y);
    LOG_VAR(circleCenter.x);
    LOG_VAR(circleCenter.y);
    LOG_VAR(circleRadius);


	if (Contains(rectPos, rectSize, circleCenter)) {
        LOG_INFO("Contains true");
        return true;
    }

	Vector2D circleDistance;
	Vector2D rectCenter = Vector2D(rectPos.x + rectSize.x / 2, rectPos.y - rectSize.y / 2);

    LOG_VAR(rectCenter.x);
    LOG_VAR(rectCenter.y);

	circleDistance.x = fabs(rectCenter.x - circleCenter.x);
	circleDistance.y = fabs(rectCenter.y - circleCenter.y);

    LOG_VAR(circleDistance.x);
    LOG_VAR(circleDistance.y);

	if (circleDistance.x > rectSize.x / 2 + circleRadius) { return false; }
	if (circleDistance.y > rectSize.y / 2 + circleRadius) { return false; }

	if (circleDistance.x <= rectSize.x / 2) {LOG_INFO("First condition"); return true; }
	if (circleDistance.y <= rectSize.y / 2) {LOG_INFO("Second condition"); return true; }

	auto cornerDistance_sq = pow(circleDistance.x - rectSize.x / 2, 2) +
		pow(circleDistance.y - rectSize.y / 2, 2);

    LOG_VAR(cornerDistance_sq);

	return cornerDistance_sq <= pow(circleRadius, 2);
}

bool Tools::Contains(const Vector2D& rectPos, const Vector2D& rectSize, const Vector2D& point)
{
 	auto left = rectPos.x;
	auto right = rectPos.x + rectSize.x;

	if (right < left)
		std::swap(left, right);

	auto top = rectPos.y;
	auto bottom = rectPos.y - rectSize.y;

	if (bottom < top)
		std::swap(top, bottom);

	return	point.x > left && point.x < right &&
			point.y > top  && point.y < bottom;
}



float Area(const vector<Vector2D> &contour)
{
	int n = contour.size();

	float A = 0.0f;

	for (int p = n - 1, q = 0; q<n; p = q++)
	{
		A += contour[p].x*contour[q].y - contour[q].x*contour[p].y;
	}
	return A*0.5f;
}

/*
InsideTriangle decides if a point P is Inside of the triangle
defined by A, B, C.
*/
bool InsideTriangle(float Ax, float Ay,
	float Bx, float By,
	float Cx, float Cy,
	float Px, float Py)

{
	float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
	float cCROSSap, bCROSScp, aCROSSbp;

	ax = Cx - Bx;  ay = Cy - By;
	bx = Ax - Cx;  by = Ay - Cy;
	cx = Bx - Ax;  cy = By - Ay;
	apx = Px - Ax;  apy = Py - Ay;
	bpx = Px - Bx;  bpy = Py - By;
	cpx = Px - Cx;  cpy = Py - Cy;

	aCROSSbp = ax*bpy - ay*bpx;
	cCROSSap = cx*apy - cy*apx;
	bCROSScp = bx*cpy - by*cpx;

	return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
};

bool Snip(const vector<Vector2D> &contour, int u, int v, int w, int n, int *V)
{
	int p;
	float Ax, Ay, Bx, By, Cx, Cy, Px, Py;

	Ax = contour[V[u]].x;
	Ay = contour[V[u]].y;

	Bx = contour[V[v]].x;
	By = contour[V[v]].y;

	Cx = contour[V[w]].x;
	Cy = contour[V[w]].y;

	if (EPSILON > (((Bx - Ax)*(Cy - Ay)) - ((By - Ay)*(Cx - Ax)))) return false;

	for (p = 0; p<n; p++)
	{
		if ((p == u) || (p == v) || (p == w)) continue;
		Px = contour[V[p]].x;
		Py = contour[V[p]].y;
		if (InsideTriangle(Ax, Ay, Bx, By, Cx, Cy, Px, Py)) return false;
	}

	return true;
}

std::vector<Vector2D> Tools::Triangulate(const std::vector<Vector2D>& polygon)
{
	std::vector<Vector2D> result;

	/* allocate and initialize list of Vertices in polygon */

	int n = polygon.size();
	if (n < 3) return result;

	int *V = new int[n];

	/* we want a counter-clockwise polygon in V */

	if (0.0f < Area(polygon))
		for (int v = 0; v<n; v++) V[v] = v;
	else
		for (int v = 0; v<n; v++) V[v] = (n - 1) - v;

	int nv = n;

	/*  remove nv-2 Vertices, creating 1 triangle every time */
	int count = 2 * nv;   /* error detection */

	for (int m = 0, v = nv - 1; nv>2; )
	{
		/* if we loop, it is probably a non-simple polygon */
		if (0 >= (count--))
		{
			//** Triangulate: ERROR - probable bad polygon!
			return result;
		}

		/* three consecutive vertices in current polygon, <u,v,w> */
		int u = v; if (nv <= u) u = 0;     /* previous */
		v = u + 1; if (nv <= v) v = 0;     /* new v    */
		int w = v + 1; if (nv <= w) w = 0;     /* next     */

		if (Snip(polygon, u, v, w, nv, V))
		{
			int a, b, c, s, t;

			/* true names of the vertices */
			a = V[u]; b = V[v]; c = V[w];

			/* output Triangle */
			result.push_back(polygon[a]);
			result.push_back(polygon[b]);
			result.push_back(polygon[c]);

			m++;

			/* remove v from remaining polygon */
			for (s = v, t = v + 1; t<nv; s++, t++) V[s] = V[t]; nv--;

			/* resest error detection counter */
			count = 2 * nv;
		}
	}
	delete V;

	return result;
}

Vector2D Tools::Vector2DPosition(int x, int y)
{
    x -= screenWidth / 2;
    y -= screenHeight / 2;
    return Vector2D(float(x) / (screenWidth / 2), float(y) / (screenHeight / 2));
}

Vector2D Tools::Vector2DSize(int x, int y)
{
    return Vector2D(float(x) / screenWidth, float(y) / screenHeight );
}
