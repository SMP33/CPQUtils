#ifndef CPQVIDEOCAPTUREWORKER_PRIVATE_H
#define CPQVIDEOCAPTUREWORKER_PRIVATE_H

#include <QtCore/QObject>

class CpqVideoCaptureWorker_private : public QObject
{
    Q_OBJECT
public:
    explicit CpqVideoCaptureWorker_private(QObject *parent = nullptr);

signals:

};

#endif // CPQVIDEOCAPTUREWORKER_PRIVATE_H
