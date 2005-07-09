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
    aint with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include <qpoint.h>

#include "KRenderingPaintServerGradient.h"
#include "KCanvasMatrix.h"

KCSortedGradientStopList::KCSortedGradientStopList()
{
	setAutoDelete(true);
}

void KCSortedGradientStopList::addStop(float offset, const QColor &color)
{
	KCGradientOffsetPair *pair = new KCGradientOffsetPair;
	pair->offset = offset;
	pair->color = color;

	append(pair);
	sort();
}

int KCSortedGradientStopList::compareItems(QPtrCollection::Item item1, QPtrCollection::Item item2)
{
	KCGradientOffsetPair *pair1 = static_cast<KCGradientOffsetPair *>(item1);
	KCGradientOffsetPair *pair2 = static_cast<KCGradientOffsetPair *>(item2);

	if(pair1->offset == pair2->offset)
		return 0;
	else if(pair1->offset < pair2->offset)
		return -1;

	return 1;
}

// KRenderingPaintServerGradient
class KRenderingPaintServerGradient::Private
{
public:
	Private() { boundingBoxMode = true; spreadMethod = SPREADMETHOD_PAD; }
	~Private() { }

	KCSortedGradientStopList stops;
	KCGradientSpreadMethod spreadMethod;
	bool boundingBoxMode;
	KCanvasMatrix gradientTransform;
};

KRenderingPaintServerGradient::KRenderingPaintServerGradient() : KRenderingPaintServer(), KCanvasResource(), d(new Private())
{
}

KRenderingPaintServerGradient::~KRenderingPaintServerGradient()
{
	delete d;
}

KCSortedGradientStopList &KRenderingPaintServerGradient::gradientStops() const{

	return d->stops;
}

void KRenderingPaintServerGradient::setGradientStops(const KCSortedGradientStopList &stops)
{
	d->stops = stops;
}

KCGradientSpreadMethod KRenderingPaintServerGradient::spreadMethod() const
{
	return d->spreadMethod;
}

void KRenderingPaintServerGradient::setGradientSpreadMethod(const KCGradientSpreadMethod &method)
{
	d->spreadMethod = method;
}

bool KRenderingPaintServerGradient::boundingBoxMode() const
{
	return d->boundingBoxMode;
}

void KRenderingPaintServerGradient::setBoundingBoxMode(bool mode)
{
	d->boundingBoxMode = mode;
}

KCanvasMatrix KRenderingPaintServerGradient::gradientTransform() const
{
	return d->gradientTransform;
}

void KRenderingPaintServerGradient::setGradientTransform(const KCanvasMatrix &mat)
{
	d->gradientTransform = mat;
}

// KRenderingPaintServerLinearGradient
class KRenderingPaintServerLinearGradient::Private
{
public:
	Private() { }
	~Private() { }

	QPoint start, end;
};

KRenderingPaintServerLinearGradient::KRenderingPaintServerLinearGradient() : KRenderingPaintServerGradient(), d(new Private())
{
}

KRenderingPaintServerLinearGradient::~KRenderingPaintServerLinearGradient()
{
	delete d;
}

QPoint KRenderingPaintServerLinearGradient::gradientStart() const
{
	return d->start;
}

void KRenderingPaintServerLinearGradient::setGradientStart(const QPoint &start)
{
	d->start = start;
}

QPoint KRenderingPaintServerLinearGradient::gradientEnd() const
{
	return d->end;
}

void KRenderingPaintServerLinearGradient::setGradientEnd(const QPoint &end)
{
	d->end = end;
}

KCPaintServerType KRenderingPaintServerLinearGradient::type() const
{
	return PS_LINEAR_GRADIENT;
}

// KRenderingPaintServerRadialGradient
class KRenderingPaintServerRadialGradient::Private
{
public:
	Private() { }
	~Private() { }

	float radius;
	QPoint center, focal;
};

KRenderingPaintServerRadialGradient::KRenderingPaintServerRadialGradient() : KRenderingPaintServerGradient(), d(new Private())
{
}

KRenderingPaintServerRadialGradient::~KRenderingPaintServerRadialGradient()
{
	delete d;
}

QPoint KRenderingPaintServerRadialGradient::gradientCenter() const
{
	return d->center;
}

void KRenderingPaintServerRadialGradient::setGradientCenter(const QPoint &center)
{
	d->center = center;
}

QPoint KRenderingPaintServerRadialGradient::gradientFocal() const
{
	return d->focal;
}

void KRenderingPaintServerRadialGradient::setGradientFocal(const QPoint &focal)
{
	d->focal = focal;
}

float KRenderingPaintServerRadialGradient::gradientRadius() const
{
	return d->radius;
}

void KRenderingPaintServerRadialGradient::setGradientRadius(float radius)
{
	d->radius = radius;
}

KCPaintServerType KRenderingPaintServerRadialGradient::type() const
{
	return PS_RADIAL_GRADIENT;
}

// vim:ts=4:noet
