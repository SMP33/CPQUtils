
#ifndef ABSTRACTCLIENTHANDLER_H
#define ABSTRACTCLIENTHANDLER_H

#include <QByteArray>
#include <QObject>

class AbstractClientHandler : public QObject
{
  Q_OBJECT
public:
  explicit AbstractClientHandler(QObject* parent = nullptr);

public slots:
  virtual void read(const QByteArray& bytes);
  virtual void socketClosed();

signals:
  void write(const QByteArray& data);
  void closeSocket();
  void disconnected();
};

#endif // ABSTRACTCLIENTHANDLER_H
