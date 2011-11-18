#include "pluginspec.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QXmlStreamReader>
#include <QtDebug>

using namespace ExtensionSystem;

bool PluginDependency::operator==(const PluginDependency &other) const
{
    return name == other.name && version == other.version && type == other.type;
}

PluginSpec::PluginSpec(const QString &fileName)
{
    read(fileName);
}

PluginSpec::~PluginSpec()
{
}

QString PluginSpec::name() const
{
    return this->name();
}

QString PluginSpec::version() const
{
    return this->version;
}

QString PluginSpec::compatVersion() const
{
    return this->compatVersion;
}

QString PluginSpec::vendor() const
{
    return this->vendor;
}

QString PluginSpec::copyright() const
{
    return this->copyright;
}

QString PluginSpec::license() const
{
    return this->license;
}

QString PluginSpec::description() const
{
    return this->description;
}

QString PluginSpec::url() const
{
    return this->url;
}

QString PluginSpec::category() const
{
    return this->category;
}

QList<PluginDependency> PluginSpec::dependencies() const
{
    return this->dependencies;
}

PluginSpec::State PluginSpec::state() const
{
    return this->state;
}

bool PluginSpec::read(const QString &fileName)
{
    name
        = version
        = compatVersion
        = vendor
        = copyright
        = license
        = description
        = url
        = category
        = location
        = "";
    state = PluginSpec::Invalid;
    dependencies.clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return reportError(tr("Cannot open file %1 for reading: %2")
                           .arg(QDir::toNativeSeparators(file.fileName()), file.errorString()));
    QFileInfo fileInfo(file);
    QXmlStreamReader reader(&file);
    while (!reader.atEnd()) {
        reader.readNext();
        switch (reader.tokenType()) {
        case QXmlStreamReader::StartElement:
            readPluginSpec(reader);
            break;
        default:
            break;
        }
    }
    if (reader.hasError())
        return reportError(tr("Error parsing file %1: %2, at line %3, column %4")
                .arg(file.fileName())
                .arg(reader.errorString())
                .arg(reader.lineNumber())
                .arg(reader.columnNumber()));
    state = PluginSpec::Read;
    return true;
}

void PluginSpecPrivate::readPluginSpec(QXmlStreamReader &reader)
{
    QString element = reader.name().toString();
    if (element != QString(PLUGIN)) {
        reader.raiseError(QCoreApplication::translate("PluginSpec", "Expected element '%1' as top level element").arg(PLUGIN));
        return;
    }
    name = reader.attributes().value(PLUGIN_NAME).toString();
    if (name.isEmpty()) {
        reader.raiseError(msgAttributeMissing(PLUGIN, PLUGIN_NAME));
        return;
    }
    version = reader.attributes().value(PLUGIN_VERSION).toString();
    if (version.isEmpty()) {
        reader.raiseError(msgAttributeMissing(PLUGIN, PLUGIN_VERSION));
        return;
    }
    if (!isValidVersion(version)) {
        reader.raiseError(msgInvalidFormat(PLUGIN_VERSION));
        return;
    }
    compatVersion = reader.attributes().value(PLUGIN_COMPATVERSION).toString();
    if (!compatVersion.isEmpty() && !isValidVersion(compatVersion)) {
        reader.raiseError(msgInvalidFormat(PLUGIN_COMPATVERSION));
        return;
    } else if (compatVersion.isEmpty()) {
        compatVersion = version;
    }
    QString experimentalString = reader.attributes().value(PLUGIN_EXPERIMENTAL).toString();
    experimental = (experimentalString.compare(QLatin1String("true"), Qt::CaseInsensitive) == 0);
    if (!experimentalString.isEmpty() && !experimental
            && experimentalString.compare(QLatin1String("false"), Qt::CaseInsensitive) != 0) {
        reader.raiseError(msgInvalidFormat(PLUGIN_EXPERIMENTAL));
        return;
    }
    disabledByDefault = experimental;
    enabled = !experimental;
    while (!reader.atEnd()) {
        reader.readNext();
        switch (reader.tokenType()) {
        case QXmlStreamReader::StartElement:
            element = reader.name().toString();
            if (element == VENDOR)
                vendor = reader.readElementText().trimmed();
            else if (element == COPYRIGHT)
                copyright = reader.readElementText().trimmed();
            else if (element == LICENSE)
                license = reader.readElementText().trimmed();
            else if (element == DESCRIPTION)
                description = reader.readElementText().trimmed();
            else if (element == URL)
                url = reader.readElementText().trimmed();
            else if (element == CATEGORY)
                category = reader.readElementText().trimmed();
            else if (element == DEPENDENCYLIST)
                readDependencies(reader);
            else if (element == ARGUMENTLIST)
                readArgumentDescriptions(reader);
            else
                reader.raiseError(msgInvalidElement(name));
            break;
        case QXmlStreamReader::EndDocument:
        case QXmlStreamReader::Comment:
        case QXmlStreamReader::EndElement:
        case QXmlStreamReader::Characters:
            break;
        default:
            reader.raiseError(msgUnexpectedToken());
            break;
        }
    }
}

void PluginSpecPrivate::readDependencies(QXmlStreamReader &reader)
{
    QString element;
    while (!reader.atEnd()) {
        reader.readNext();
        switch (reader.tokenType()) {
        case QXmlStreamReader::StartElement:
            element = reader.name().toString();
            if (element == DEPENDENCY) {
                readDependencyEntry(reader);
            } else {
                reader.raiseError(msgInvalidElement(name));
            }
            break;
        case QXmlStreamReader::Comment:
        case QXmlStreamReader::Characters:
            break;
        case QXmlStreamReader::EndElement:
            element = reader.name().toString();
            if (element == DEPENDENCYLIST)
                return;
            reader.raiseError(msgUnexpectedClosing(element));
            break;
        default:
            reader.raiseError(msgUnexpectedToken());
            break;
        }
    }
}

void PluginSpecPrivate::readArgumentDescriptions(QXmlStreamReader &reader)
{
    QString element;
    while (!reader.atEnd()) {
        reader.readNext();
        switch (reader.tokenType()) {
        case QXmlStreamReader::StartElement:
            element = reader.name().toString();
            if (element == ARGUMENT) {
                readArgumentDescription(reader);
            } else {
                reader.raiseError(msgInvalidElement(name));
            }
            break;
        case QXmlStreamReader::Comment:
        case QXmlStreamReader::Characters:
            break;
        case QXmlStreamReader::EndElement:
            element = reader.name().toString();
            if (element == ARGUMENTLIST)
                return;
            reader.raiseError(msgUnexpectedClosing(element));
            break;
        default:
            reader.raiseError(msgUnexpectedToken());
            break;
        }
    }
}

void PluginSpecPrivate::readArgumentDescription(QXmlStreamReader &reader)
{
    PluginArgumentDescription arg;
    arg.name = reader.attributes().value(ARGUMENT_NAME).toString();
    if (arg.name.isEmpty()) {
        reader.raiseError(msgAttributeMissing(ARGUMENT, ARGUMENT_NAME));
        return;
    }
    arg.parameter = reader.attributes().value(ARGUMENT_PARAMETER).toString();
    arg.description = reader.readElementText();
    if (reader.tokenType() != QXmlStreamReader::EndElement)
        reader.raiseError(msgUnexpectedToken());
    argumentDescriptions.push_back(arg);
}