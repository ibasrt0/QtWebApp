#include "httpserverconfig.h"

using namespace qtwebapp;

void HttpServerConfig::initdefaults()
{
	host = QHostAddress::Any;
	port = 0;
	maxRequestSize = 16e3;
	maxMultipartSize = 1e6;
	readTimeout = 1e4;
	cleanupInterval = 1e3;
	minThreads = 1;
	maxThreads = 100;
}

HttpServerConfig::HttpServerConfig()
{
	initdefaults();
}

HttpServerConfig::HttpServerConfig(const QSettings &settings)
{
	initdefaults();
	parseSettings(settings);
}

HttpServerConfig::HttpServerConfig(QSettings *settings)
{
	initdefaults();
	parseSettings(*settings);
}

void HttpServerConfig::parseSettings(const QSettings &settings)
{
#ifdef Q_OS_WIN
	if (settings.format() != QSettings::NativeFormat)
#endif
	fileName = settings.fileName();
	
	QString hoststr = settings.value("host").toString();
	host = hoststr.isEmpty() ? QHostAddress::Any : QHostAddress(hoststr);
	port = settings.value("port", port).toUInt();
	
	maxRequestSize = parseNum(settings.value("maxRequestSize", maxRequestSize), 1024);
	maxMultipartSize = parseNum(settings.value("maxMultipartSize", maxMultipartSize), 1024);
	
	cleanupInterval = parseNum(settings.value("cleanupInterval", cleanupInterval));
	
	minThreads = parseNum(settings.value("minThreads", minThreads));
	maxThreads = parseNum(settings.value("maxThreads", maxThreads));
	
	sslKeyFile = settings.value("sslKeyFile").toString();
	sslCertFile = settings.value("sslCertFile").toString();
}

// ###########################################################################################

void HttpSessionStoreConfig::initdefaults()
{
	expirationTime = 3600e3;
	cookieName = "sessionid";
	cookiePath = "/";
}

HttpSessionStoreConfig::HttpSessionStoreConfig()
{
	initdefaults();
}

HttpSessionStoreConfig::HttpSessionStoreConfig(const QSettings &settings)
{
	initdefaults();
	parseSettings(settings);
}

HttpSessionStoreConfig::HttpSessionStoreConfig(QSettings *settings)
{
	initdefaults();
	parseSettings(*settings);
}

void HttpSessionStoreConfig::parseSettings(const QSettings &settings)
{
	expirationTime = parseNum(settings.value("expirationTime", (qulonglong)expirationTime), 1000);
	cookieName = settings.value("cookieName", cookieName).toByteArray();
	
	cookiePath = settings.value("cookiePath", cookiePath).toByteArray();
	cookieComment = settings.value("cookieComment", cookieComment).toByteArray();
	cookieDomain = settings.value("cookieDomain", cookieDomain).toByteArray();
}

// ###########################################################################################

void StaticFileControllerConfig::initdefaults()
{
	path = ".";
	encoding = "UTF-8";
	maxAge = 6e4;
	maxCachedFileSize = 2<<15;
	cacheSize = 1e6;
	cacheTime = 6e4;
}

StaticFileControllerConfig::StaticFileControllerConfig()
{
	initdefaults();
}

StaticFileControllerConfig::StaticFileControllerConfig(const QSettings &settings)
{
	initdefaults();
	parseSettings(settings);
}

StaticFileControllerConfig::StaticFileControllerConfig(QSettings *settings)
{
	initdefaults();
	parseSettings(*settings);
}

void StaticFileControllerConfig::parseSettings(const QSettings &settings)
{
#ifdef Q_OS_WIN
	if (settings.format() != QSettings::NativeFormat)
#endif
	fileName = settings.fileName();
	
	path = settings.value("path", path).toString();
	encoding = settings.value("encoding", encoding).toString();
	
	maxAge = parseNum(settings.value("maxAge", maxAge));
	maxCachedFileSize = parseNum(settings.value("maxCachedFileSize", maxCachedFileSize), 1024);
	
	cacheSize = parseNum(settings.value("cacheSize", cacheSize), 1024);
	cacheTime = parseNum(settings.value("cacheTime", cacheTime));
}
