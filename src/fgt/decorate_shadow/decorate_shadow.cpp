/****************************************************************************
* MeshLab                                                           o o     *
* A versatile mesh processing toolbox                             o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

#include "decorate_shadow.h"

using namespace vcg;

const QString DecorateShadowPlugin::Info(QAction *action)
 {
  switch(ID(action))
  {
    case DP_SHOW_AO_DEPTH_TRICK :      return tr("Enable ambient occlusion trick");
    case DP_SHOW_SIMPLE_SHADOW:      return tr("Enable simple shadow");
    case DP_SHOW_SSAO:      return tr("Enable SSAO");
    case DP_SHOW_VSM_SHADOW :      return tr("Enable variance shadow mapping");
 	 }
  assert(0);
  return QString();
 }
 
void DecorateShadowPlugin::initGlobalParameterSet(QAction *, FilterParameterSet *parset) 
{
    if(parset->findParameter(tr("NoisePath")) != NULL){
        qDebug("noise path already setted..doing nothing");
        return;
    }
    QString noiseDirPath = MainWindowInterface::getBaseDirPath() + tr("/textures/noise.png");
    parset->addString("NoisePath", noiseDirPath);
    GLfloat dims[4];
                glGetFloatv(GL_VIEWPORT, dims);
                int width = (int)dims[2];
                int height = (int)dims[3];
    this->_sm->Init(width, width);
}		
		
const QString DecorateShadowPlugin::ST(FilterIDType filter) const
{
  switch(filter)
  {
    case DP_SHOW_AO_DEPTH_TRICK     : return QString("AO depth trick");
    case DP_SHOW_SIMPLE_SHADOW      : return QString("simple shadow");
    case DP_SHOW_SSAO               : return QString("SSAO");
    case DP_SHOW_VSM_SHADOW         : return QString("VSM");
    default: assert(0);
  }
  return QString("error!");
}

void DecorateShadowPlugin::Decorate(QAction *a, MeshModel &m, FilterParameterSet *par, GLArea *gla, QFont /*qf*/)
{
    if(m.visible){
        if(a->text() == ST(DP_SHOW_SIMPLE_SHADOW)){
            this->_sm->RunShader(m, gla);
        }
    }
}

Q_EXPORT_PLUGIN(DecorateShadowPlugin)
