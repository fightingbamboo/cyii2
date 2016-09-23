
extern zend_class_entry *yii_baseyii_ce;

ZEPHIR_INIT_CLASS(yii_BaseYii);

PHP_METHOD(yii_BaseYii, getVersion);
PHP_METHOD(yii_BaseYii, getAlias);
PHP_METHOD(yii_BaseYii, getRootAlias);
PHP_METHOD(yii_BaseYii, setAlias);
PHP_METHOD(yii_BaseYii, autoload);
PHP_METHOD(yii_BaseYii, createObject);
PHP_METHOD(yii_BaseYii, getLogger);
PHP_METHOD(yii_BaseYii, setLogger);
PHP_METHOD(yii_BaseYii, trace);
PHP_METHOD(yii_BaseYii, error);
PHP_METHOD(yii_BaseYii, warning);
PHP_METHOD(yii_BaseYii, info);
PHP_METHOD(yii_BaseYii, beginProfile);
PHP_METHOD(yii_BaseYii, endProfile);
PHP_METHOD(yii_BaseYii, powered);
PHP_METHOD(yii_BaseYii, t);
PHP_METHOD(yii_BaseYii, configure);
PHP_METHOD(yii_BaseYii, getObjectVars);
void zephir_init_static_properties_yii_BaseYii(TSRMLS_D);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_getalias, 0, 0, 1)
	ZEND_ARG_INFO(0, alias)
	ZEND_ARG_INFO(0, throwException)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_getrootalias, 0, 0, 1)
	ZEND_ARG_INFO(0, alias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_setalias, 0, 0, 2)
	ZEND_ARG_INFO(0, alias)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_autoload, 0, 0, 1)
	ZEND_ARG_INFO(0, className)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_createobject, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
	ZEND_ARG_ARRAY_INFO(0, params, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_setlogger, 0, 0, 1)
	ZEND_ARG_INFO(0, logger)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_trace, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_error, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_warning, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_info, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_beginprofile, 0, 0, 1)
	ZEND_ARG_INFO(0, token)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_endprofile, 0, 0, 1)
	ZEND_ARG_INFO(0, token)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_t, 0, 0, 2)
	ZEND_ARG_INFO(0, category)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, params)
	ZEND_ARG_INFO(0, language)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_configure, 0, 0, 2)
	ZEND_ARG_INFO(0, object)
	ZEND_ARG_INFO(0, properties)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_baseyii_getobjectvars, 0, 0, 1)
	ZEND_ARG_INFO(0, object)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_baseyii_method_entry) {
	PHP_ME(yii_BaseYii, getVersion, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, getAlias, arginfo_yii_baseyii_getalias, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, getRootAlias, arginfo_yii_baseyii_getrootalias, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, setAlias, arginfo_yii_baseyii_setalias, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, autoload, arginfo_yii_baseyii_autoload, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, createObject, arginfo_yii_baseyii_createobject, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, getLogger, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, setLogger, arginfo_yii_baseyii_setlogger, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, trace, arginfo_yii_baseyii_trace, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, error, arginfo_yii_baseyii_error, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, warning, arginfo_yii_baseyii_warning, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, info, arginfo_yii_baseyii_info, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, beginProfile, arginfo_yii_baseyii_beginprofile, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, endProfile, arginfo_yii_baseyii_endprofile, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, powered, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, t, arginfo_yii_baseyii_t, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, configure, arginfo_yii_baseyii_configure, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_BaseYii, getObjectVars, arginfo_yii_baseyii_getobjectvars, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
