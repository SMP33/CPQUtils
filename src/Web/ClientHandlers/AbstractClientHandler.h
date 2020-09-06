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
  /// @brief Запись данных в сокет
  void write(const QByteArray& data);
  /// @brief Запрос на закрытие сокета
  void closeSocket();
  /// @brief Сигнал после закрытия сокета
  void disconnected();
  /// @brief Сигнал начала работы
  void started();
};

}

}

#endif // ABSTRACTCLIENTHANDLER_H
