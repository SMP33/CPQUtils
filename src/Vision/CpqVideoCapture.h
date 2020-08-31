#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>

class VideoSource : public QObject
{
  Q_OBJECT
public:
  explicit VideoSource(QObject* parent = nullptr);

signals:
};

#endif // VIDEOSOURCE_H
