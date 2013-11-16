#ifndef LFONTEXPORTER_H
#define LFONTEXPORTER_H

#include "../abstractexporter.h"

class LfontExporter : public AbstractExporter
{
Q_OBJECT
public:
    explicit LfontExporter(QObject *parent = 0);
protected:
    virtual bool Export(QByteArray& out);
signals:

public slots:

};

#endif // LFONTEXPORTER_H
