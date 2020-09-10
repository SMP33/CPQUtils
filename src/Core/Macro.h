#pragma once

#include <QDebug>
#include <QObject>
#include <iostream>
#include <sstream>

namespace cpq {
class CpqStringStream : public std::stringstream
{
public:
  CpqStringStream(){};
  ~CpqStringStream(){};

  operator QString() const { return QString::fromStdString(str()); }

private:
};
}

#define cpq_start_namespace(ns)                                                \
  namespace cpq {                                                              \
  namespace ns {

#define cpq_end_namespace                                                      \
  }                                                                            \
  }

#define QDEB_PRINT(x) qDebug().noquote().nospace() << #x << ": " << x;

#define COUT_PRINT(x) std::cout << #x << ": " << x << std::endl;

#define COUT_PRINT2(x, name) std::cout << name << ": " << x << std::endl;
