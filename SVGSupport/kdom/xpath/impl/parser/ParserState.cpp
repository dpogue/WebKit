/*
    Copyright(C) 2004 Richard Moore <rich@kde.org>
    Copyright(C) 2005 Frans Englich <frans.englich@telia.com>

    This file is part of the KDE project

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or(at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include <qstring.h>

#include "ExprNodeImpl.h"
#include "ParserState.h"

using namespace KDOM;
using namespace KDOM::XPath;

ExprNodeImpl *ParserState::s_ast = 0;
QString ParserState::s_err = QString();

ExprNodeImpl *ParserState::node()
{
    return s_ast;
}

void ParserState::setNode(ExprNodeImpl *root)
{
    s_ast = root;
}

QString ParserState::error()
{
    return s_err;
}

void ParserState::setError(const QString &msg) 
{
    s_err = msg;
}

// vim:ts=4:noet
