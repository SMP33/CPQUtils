#include "AbstractClientHandler.h"

using namespace cpq::web;

AbstractClientHandler::AbstractClientHandler(QObject* parent)
  : QObject(parent)
{}

void
AbstractClientHandler::read(const QByteArray& bytes)
{}

void
AbstractClientHandler::socketClosed()
{}
