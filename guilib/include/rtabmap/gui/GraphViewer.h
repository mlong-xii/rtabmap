/*
Copyright (c) 2010-2016, Mathieu Labbe - IntRoLab - Universite de Sherbrooke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Universite de Sherbrooke nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef RTABMAP_GRAPHVIEWER_H_
#define RTABMAP_GRAPHVIEWER_H_

#include "rtabmap/gui/RtabmapGuiExp.h" // DLL export/import defines

#include <QGraphicsView>
#include <QtCore/QMap>
#include <QtCore/QSettings>
#include <rtabmap/core/Link.h>
#include <rtabmap/core/GeodeticCoords.h>
#include <opencv2/opencv.hpp>
#include <map>
#include <vector>

class QGraphicsItem;
class QGraphicsPixmapItem;
class QGraphicsItemGroup;

namespace rtabmap {

class NodeItem;
class LinkItem;

class RTABMAPGUI_EXP GraphViewer : public QGraphicsView {

	Q_OBJECT;

public:
	GraphViewer(QWidget * parent = 0);
	virtual ~GraphViewer();

	void updateGraph(const std::map<int, Transform> & poses,
					 const std::multimap<int, Link> & constraints,
					 const std::map<int, int> & mapIds);
	void updateGTGraph(const std::map<int, Transform> & poses);
	void updateGPSGraph(
			const std::map<int, Transform> & gpsMapPoses,
			const std::map<int, GPS> & gpsValues);
	void updateReferentialPosition(const Transform & t);
	void updateMap(const cv::Mat & map8U, float resolution, float xMin, float yMin);
	void updatePosterior(const std::map<int, float> & posterior);
	void updateLocalPath(const std::vector<int> & localPath);
	void setGlobalPath(const std::vector<std::pair<int, Transform> > & globalPath);
	void setCurrentGoalID(int id, const Transform & pose = Transform());
	void setLocalRadius(float radius);
	void clearGraph();
	void clearMap();
	void clearPosterior();
	void clearAll();

	void saveSettings(QSettings & settings, const QString & group = "") const;
	void loadSettings(QSettings & settings, const QString & group = "");

	//getters
	const QString & getWorkingDirectory() const {return _workingDirectory;}
	float getNodeRadius() const {return _nodeRadius;}
	float getLinkWidth() const {return _linkWidth;}
	const QColor & getNodeColor() const {return _nodeColor;}
	const QColor & getCurrentGoalColor() const {return _currentGoalColor;}
	const QColor & getNeighborColor() const {return _neighborColor;}
	const QColor & getGlobalLoopClosureColor() const {return _loopClosureColor;}
	const QColor & getLocalLoopClosureColor() const {return _loopClosureLocalColor;}
	const QColor & getUserLoopClosureColor() const {return _loopClosureUserColor;}
	const QColor & getVirtualLoopClosureColor() const {return _loopClosureVirtualColor;}
	const QColor & getNeighborMergedColor() const {return _neighborMergedColor;}
	const QColor & getRejectedLoopClosureColor() const {return _loopClosureRejectedColor;}
	const QColor & getLocalPathColor() const {return _localPathColor;}
	const QColor & getGlobalPathColor() const {return _globalPathColor;}
	const QColor & getGTColor() const {return _gtPathColor;}
	const QColor & getGPSColor() const {return _gpsPathColor;}
	const QColor & getIntraSessionLoopColor() const {return _loopIntraSessionColor;}
	const QColor & getInterSessionLoopColor() const {return _loopInterSessionColor;}
	bool isIntraInterSessionColorsEnabled() const {return _intraInterSessionColors;}
	bool isGridMapVisible() const;
	bool isOriginVisible() const;
	bool isReferentialVisible() const;
	bool isLocalRadiusVisible() const;
	float getLoopClosureOutlierThr() const {return _loopClosureOutlierThr;}
	float getMaxLinkLength() const {return _maxLinkLength;}
	bool isGraphVisible() const;
	bool isGlobalPathVisible() const;
	bool isLocalPathVisible() const;
	bool isGtGraphVisible() const;
	bool isGPSGraphVisible() const;
	bool isOrientationENU() const;

	// setters
	void setWorkingDirectory(const QString & path);
	void setNodeRadius(float radius);
	void setLinkWidth(float width);
	void setNodeColor(const QColor & color);
	void setCurrentGoalColor(const QColor & color);
	void setNeighborColor(const QColor & color);
	void setGlobalLoopClosureColor(const QColor & color);
	void setLocalLoopClosureColor(const QColor & color);
	void setUserLoopClosureColor(const QColor & color);
	void setVirtualLoopClosureColor(const QColor & color);
	void setNeighborMergedColor(const QColor & color);
	void setRejectedLoopClosureColor(const QColor & color);
	void setLocalPathColor(const QColor & color);
	void setGlobalPathColor(const QColor & color);
	void setGTColor(const QColor & color);
	void setGPSColor(const QColor & color);
	void setIntraSessionLoopColor(const QColor & color);
	void setInterSessionLoopColor(const QColor & color);
	void setIntraInterSessionColorsEnabled(bool enabled);
	void setGridMapVisible(bool visible);
	void setOriginVisible(bool visible);
	void setReferentialVisible(bool visible);
	void setLocalRadiusVisible(bool visible);
	void setLoopClosureOutlierThr(float value);
	void setMaxLinkLength(float value);
	void setGraphVisible(bool visible);
	void setGlobalPathVisible(bool visible);
	void setLocalPathVisible(bool visible);
	void setGtGraphVisible(bool visible);
	void setGPSGraphVisible(bool visible);
	void setOrientationENU(bool enabled);

signals:
	void configChanged();
	void mapShownRequested();

public slots:
	void restoreDefaults();

protected:
	virtual void wheelEvent ( QWheelEvent * event );
	virtual void contextMenuEvent(QContextMenuEvent * event);

private:
	QString _workingDirectory;
	QColor _nodeColor;
	QColor _currentGoalColor;
	QColor _neighborColor;
	QColor _loopClosureColor;
	QColor _loopClosureLocalColor;
	QColor _loopClosureUserColor;
	QColor _loopClosureVirtualColor;
	QColor _neighborMergedColor;
	QColor _loopClosureRejectedColor;
	QColor _localPathColor;
	QColor _globalPathColor;
	QColor _gtPathColor;
	QColor _gpsPathColor;
	QColor _loopIntraSessionColor;
	QColor _loopInterSessionColor;
	bool _intraInterSessionColors;
	QGraphicsItem * _root;
	QGraphicsItem * _graphRoot;
	QGraphicsItem * _globalPathRoot;
	QGraphicsItem * _localPathRoot;
	QGraphicsItem * _gtGraphRoot;
	QGraphicsItem * _gpsGraphRoot;
	QMap<int, NodeItem*> _nodeItems;
	QMultiMap<int, LinkItem*> _linkItems;
	QMap<int, NodeItem*> _gtNodeItems;
	QMap<int, NodeItem*> _gpsNodeItems;
	QMultiMap<int, LinkItem*> _gtLinkItems;
	QMultiMap<int, LinkItem*> _gpsLinkItems;
	QMultiMap<int, LinkItem*> _localPathLinkItems;
	QMultiMap<int, LinkItem*> _globalPathLinkItems;
	float _nodeRadius;
	float _linkWidth;
	QGraphicsPixmapItem * _gridMap;
	QGraphicsItemGroup * _referential;
	QGraphicsItemGroup * _originReferential;
	float _gridCellSize;
	QGraphicsEllipseItem * _localRadius;
	float _loopClosureOutlierThr;
	float _maxLinkLength;
	bool _orientationENU;
};

} /* namespace rtabmap */
#endif /* GRAPHVIEWER_H_ */
