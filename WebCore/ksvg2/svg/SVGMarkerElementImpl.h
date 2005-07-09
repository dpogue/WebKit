/*
    Copyright (C) 2004 Nikolas Zimmermann <wildfox@kde.org>
				  2004 Rob Buis <buis@kde.org>

    This file is part of the KDE project

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#ifndef KSVG_SVGMarkerElementImpl_H
#define KSVG_SVGMarkerElementImpl_H

#include "SVGLangSpaceImpl.h"
#include "SVGFitToViewBoxImpl.h"
#include "SVGStyledElementImpl.h"
#include "SVGExternalResourcesRequiredImpl.h"

class KCanvasMarker;

namespace KDOM
{
	class DocumentImpl;
};

namespace KSVG
{
	class SVGAngleImpl;
	class SVGAnimatedAngleImpl;
	class SVGAnimatedLengthImpl;
	class SVGAnimatedEnumerationImpl;
	class SVGMarkerElementImpl : public SVGStyledElementImpl,
								 public SVGLangSpaceImpl,
								 public SVGExternalResourcesRequiredImpl,
								 public SVGFitToViewBoxImpl
	{
	public:
		SVGMarkerElementImpl(KDOM::DocumentImpl *doc, KDOM::NodeImpl::Id id, const KDOM::DOMString &prefix);
		virtual ~SVGMarkerElementImpl();

		// Derived from: 'ElementImpl'
		virtual void close();

		// 'SVGMarkerElement' functions
		SVGAnimatedLengthImpl *refX() const;
		SVGAnimatedLengthImpl *refY() const;
		SVGAnimatedEnumerationImpl *markerUnits() const;
		SVGAnimatedLengthImpl *markerWidth() const;
		SVGAnimatedLengthImpl *markerHeight() const;
		SVGAnimatedEnumerationImpl *orientType() const;
		SVGAnimatedAngleImpl *orientAngle() const;

		void setOrientToAuto();
		void setOrientToAngle(SVGAngleImpl *angle);

		virtual void parseAttribute(KDOM::AttributeImpl *);
	
		virtual bool implementsCanvasItem() const { return true; }

		virtual KCanvasItem *createCanvasItem(KCanvas *canvas, KRenderingStyle *style) const;

	private:
		mutable SVGAnimatedLengthImpl *m_refX;
		mutable SVGAnimatedLengthImpl *m_refY;
		mutable SVGAnimatedLengthImpl *m_markerWidth;
		mutable SVGAnimatedLengthImpl *m_markerHeight;
		mutable SVGAnimatedEnumerationImpl *m_markerUnits;
		mutable SVGAnimatedEnumerationImpl *m_orientType;
		mutable SVGAnimatedAngleImpl *m_orientAngle;
		KCanvasMarker *m_marker;
	};
};

#endif

// vim:ts=4:noet
