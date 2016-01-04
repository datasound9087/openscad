#pragma once

#include "Geometry.h"
#include "system-gl.h"
#include "linalg.h"
#include "GeometryUtils.h"
#include "renderer.h"
#include "Polygon2d.h"
#include "linalg.h"
#include <vector>
#include <string>

#include <boost/logic/tribool.hpp>
BOOST_TRIBOOL_THIRD_STATE(unknown)

class PolySet : public Geometry
{
public:
	Polygons polygons;

	PolySet(unsigned int dim, boost::tribool convex = unknown);
	PolySet(const Polygon2d &origin);
	virtual ~PolySet();

	virtual size_t memsize() const;
	virtual BoundingBox getBoundingBox() const;
	virtual std::string dump() const;
	virtual unsigned int getDimension() const { return this->dim; }
	virtual bool isEmpty() const { return polygons.size() == 0; }
	virtual Geometry *copy() const { return new PolySet(*this); }

	void quantizeVertices();
	size_t numPolygons() const { return polygons.size(); }

	void render_surface(Renderer::csgmode_e csgmode, const Transform3d &m, GLint *shaderinfo = NULL) const;
	void render_edges(Renderer::csgmode_e csgmode) const;

	void transform(const Transform3d &mat);
	const Transform3d &getTransform() const { return matrix; }
	void applyTransform();

	void resize(Vector3d newsize, const Eigen::Matrix<bool,3,1> &autosize);

	bool is_convex() const;
	boost::tribool convexValue() const { return this->convex; }

private:
	Transform3d matrix;
	Polygon2d polygon;
	unsigned int dim;
	mutable boost::tribool convex;
	mutable BoundingBox bbox;
	mutable bool dirty;
	friend class PolySetBuilder;
};
