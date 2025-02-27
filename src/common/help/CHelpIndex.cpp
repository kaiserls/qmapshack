/**********************************************************************************************
    Copyright (C) 2018 Oliver Eichler <oliver.eichler@gmx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************************/

#include "help/CHelpIndex.h"

#include <QtGui>
#include <QtHelp>
#include <QtWidgets>

CHelpIndex::CHelpIndex(QHelpEngine* engine, QWidget* parent)
    : QWidget(parent)
{
    labelSearch = new QLabel(tr("Search:"), this);
    lineSearch = new QLineEdit(this);
    index = engine->indexWidget();

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(labelSearch);
    l->addWidget(lineSearch);
    l->addWidget(index);

    setLayout(l);

    connect(lineSearch, &QLineEdit::textChanged, this, &CHelpIndex::slotSearch);
}

void CHelpIndex::slotSearch(const QString& text)
{
    index->filterIndices(text);
}

