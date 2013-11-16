#include "lfontexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"

#include <QString>
LfontExporter::LfontExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("lfont");
}
static QString charCode(uint code) {
    return QString().append('\"').append(code).append('\"');
}

bool LfontExporter::Export(QByteArray& out) {
    QString name = texFilename();
    name = name.left(name.length()-4);

    QString res = "Font\n";
    res+=QString("  name: ")+name+QString("\n");
    res+=QString("  image: ")+texFilename()+QString("\n");
    res+=QString("  height: ")+QString().number(metrics().height)+QString("\n");
    res+=QString("  family: ")+fontConfig()->family()+QString("\n");
    res+=QString("  style: ")+fontConfig()->style()+QString("\n");
    res+=QString("  size: ")+QString().number(fontConfig()->size())+QString("\n");
    res+=QString("  ascender: ")+QString().number(metrics().ascender)+QString("\n");
    res+=QString("  descender: ")+QString().number(metrics().descender)+QString("\n");
    res+=QString("  height: ")+QString().number(metrics().height)+QString("\n");
    res+=QString("  yoffset: 0\n");
    res+=QString("  spacing: 0 0\n");

    res+=QString("  chars:\n");
    foreach (const Symbol& c , symbols()) {
        QString charDef= "    Char\n";
        charDef+=QString("      char: ")+charCode(c.id)+QString("\n");
        charDef+=QString("      width: ")+QString().number(c.advance)+QString("\n");
        charDef+=QString("      clip: ")+QString().number(c.placeX)+QString(" ")+
                                   QString().number(c.placeY)+QString(" ")+
                                   QString().number(c.placeW)+QString(" ")+
                                   QString().number(c.placeH)+QString("\n");
        charDef+=QString("      offset: ")+QString().number(c.offsetX)+QString(" ")+QString().number(metrics().ascender-c.offsetY)+QString("\n");

        if(c.kerning.size() > 0) {
            charDef+=QString("      kernings:\n");
            typedef QMap<ushort,int>::ConstIterator Kerning;
            for(Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
                charDef+=QString("        Kerning\n");
                charDef+=QString("          to: ") + charCode(k.key()) + QString("\n");
                charDef+=QString("          offset: ")+QString().number(k.value())+QString("\n");
            }
        }

        res += charDef;
    }
    out = res.toLatin1();
    return true;
}


AbstractExporter* LfontExporterFactoryFunc (QObject* parent) {
    return new LfontExporter(parent);
}

