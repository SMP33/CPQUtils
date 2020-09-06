#ifndef ABSTRACTCLIENTHANDLER_H
#define ABSTRACTCLIENTHANDLER_H

#include <QByteArray>
#include <QObject>

namespace cpq {
namespace web {

class AbstractClientHandler : public QObject
{
  Q_OBJECT
public:
  explicit AbstractClientHandler(QObject* parent = nullptr);

public slots:
  virtual void read(const QByteArray& bytes);
  virtual void socketClosed();

signals:
  /// @brief ������ ������ � �����
  void write(const QByteArray& data);
  /// @brief ������ �� �������� ������
  void closeSocket();
  /// @brief ������ ����� �������� ������
  void disconnected();
  /// @brief ������ ������ ������
  void started();
};

}

}

#endif // ABSTRACTCLIENTHANDLER_H
