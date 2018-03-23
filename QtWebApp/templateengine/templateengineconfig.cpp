#include "templateengineconfig.h"

using namespace qtwebapp;

void TemplateEngineConfig::initdefaults()
{
	path = ".";
	suffix = ".tpl";
	cacheSize = 1e6;
	cacheTime = 6e4;
}

TemplateEngineConfig::TemplateEngineConfig()
{
	initdefaults();
}

TemplateEngineConfig::TemplateEngineConfig(const QSettings &settings)
{
	initdefaults();
	parseSettings(settings);
}

TemplateEngineConfig::TemplateEngineConfig(QSettings *settings)
{
	initdefaults();
	parseSettings(*settings);
}

void TemplateEngineConfig::parseSettings(const QSettings &settings)
{
#ifdef Q_OS_WIN
	if (settings.format() != QSettings::NativeFormat)
#endif
	fileName = settings.fileName();
	
	path = settings.value("path", path).toString();
	suffix = settings.value("suffix", suffix).toString();
	encoding = settings.value("encoding", encoding).toString();
	
	cacheSize = parseNum(settings.value("cacheSize", cacheSize), 1024);
	cacheTime = parseNum(settings.value("cacheTime", cacheTime));
}
