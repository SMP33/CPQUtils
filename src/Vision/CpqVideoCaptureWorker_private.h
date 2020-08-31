#ifndef CPQVIDEOCAPTUREWORKER_H
#define CPQVIDEOCAPTUREWORKER_H

#include <QtCore/QObject>

class CpqVideoCaptureWorker : public QObject
{
    Q_OBJECT
public:
    explicit CpqVideoCaptureWorker(QObject *parent = nullptr);

signals:

};

#endif // CPQVIDEOCAPTUREWORKER_H
